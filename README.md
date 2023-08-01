# Embedded C with Microchip MPLABX
## Project Name: ButtonTask.X
On this project we will implement a system using a chip **PIC16F18466** that will be able to get a trigger signal from a *push button* to handle a task, in this case, that task will be *toggling an LED*
### Setting up project on MPLABX
- Create a new project

![new_project](/screenshots/create_new_project.png)
- Select standalone project

![stand_alone](/screenshots/standalone_project.png)
- Select hardware

Choose the microcontroller you want to use and a Debegger Tool if you have one
![pic_tool](/screenshots/choose_pic_and_tool.png)
- Select the C compiler

Depending on what microcontroller you are using, 8 bits, 16 bits or 32 bits, select the right C compiler. In this case we are using an 8 bit microcontroller that will use XC8 compiler.
![C_compiler](/screenshots/choose_C_compiler_suitable_with_pic.png)
- Name your project

Pick a name for your project and choose folder where you want to store it locally on your machine
![name_project](/screenshots/name_prject_select_location.png)

### Peripherals configuration
![Circuit](/screenshots/circuitButtonTask.svg)

Once we have created our project, we need to configure our hardware peripherals, in this case we first will need to configure an input for our push button and an output of the LED.
- Pin configuration

Find the MCC icon
![find_MCC](/screenshots/find_MCC.png)

If options prompt, select the classic version
![MCC_classic](/screenshots/MCC_classic.png)

Click on finish
![MCC_Setup](/screenshots/MCC_setup.png)

Verify that the microntoller packaging is the one you will use on your hardware
![Micro_pakage](/screenshots/select_right_packaging.png)

Using the Pin manager, set RC4 as input (push button) and RC5 as output (LED)
![Pin_conig](/screenshots/pinConfig.png)

On Easy Setup custom the pin names, so they would be more readable in your code
![Pin_names](/screenshots/customPinNames.png)

Generate the code files that will describe pins configuration
![Gen_code_files](/screenshots/generateFiles.png)

Go to **Project** tab and verify that files have been generated
![verify_files](/screenshots/codeGenForPins.png)

- Configure a Timer

For this project we will need to configure a timer TMR1 and use an Interrupt to set up a counter that will measure a 20 ms delay for button debounce

**TMR1 Operation**

![tmr1_op](/screenshots/tmr1Operatio.svg)

In 1ms interrupt, increment count

#### Why Interrups?

* Allows immediate service of peripherals
* Time base events get immediate service
* After interrupt normal CPU functions continue

Find TMR1 on *Device Resources*   
![Setup_timer](/screenshots/findTimer1.png)

Add TMER1 peripheral to the project

![add_timer](/screenshots/addTimer1.png)

Using *Easy Setup* set:
* - [x] Enable Timer Interrupt
* Timer Period: *1.0 ms*
* Clock Source: *FOSC/4*
* Callback Function Rate: *1*

![set_timer](/screenshots/setTimer.png)

Generate Code
![code_timer](/screenshots/genCodeTimer.png)

Verify code has been created for timer1
![verify_timer_code](/screenshots/timer1CodeVerify.png)

### Code Planing
#### Key Press Operation
**Denouncing** is a common issue encountered when working with mechanical buttons or switches, which ccurs due to the inherent nature of the button's physical contacts. When a button is pressed or released, the contacts may not make a clean, immediate transition from one state to another. Instead, they can bounce back and forth for a very short period before finally setting in a stable state. This bouncing action can result in multiple rapid state changes, which can be problematic in electronic circuits that relay in the button's state to trigger actions.

![keyStateOp](/screenshots/KeyStateOp.svg)

#### Software Debouncing Solution
This approach involves implementing debouncing algorithms in software to handle the button input. One of the simplest software techniques is called *delay-based debouncing*, where the code introduces a short delay (usually a few milisecons) after a button press is detected, during which it ignores any further chnages in the button state. This allows the button's bouncing to settle before considering the input again.

#### State Machine Implementation for key debouncing
![KeyPressMachine](/screenshots/KeyStateMachine.svg)

### Start C Coding
#### Creating *app_buttonA.h* file
Go to *Projects* and right click under *Header Files*, select *New* and *header.h*

![New_H_File](/screenshots/addNewHfile.png)

Provide name for your .h file app and click *Finish*, in this case we will use *app_buttonA*

![Name_h_file](/screenshots/buttonA_Hfile.png)

Remove or clean all content on the file just created and lets start!

Include the *header guards*
```c
#ifndef APP_BUTTON_A_H
#define	APP_BUTTON_A_H
```
Include standard libraries
```c
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
```
Define the application states
```c
typedef enum{
    APP_BUTTON_A_STATE_INIT = 0,
    APP_BUTTON_A_STATE_HIGH = 1, 
    APP_BUTTON_A_STATE_DEBOUNCE = 2,
    APP_BUTTON_A_STATE_LOW = 3 
}APP_BUTTON_A_STATES;
```
Define a data structure to be used on your application
```c
typedef struct{
    APP_BUTTON_A_STATES state;
    int debounce_count;
}APP_BUTTON_A_DATA;
extern APP_BUTTON_A_DATA app_button_a_data;
```
Declare app's functions
```c
void APP_BUTTON_A_Init(void);
void APP_BUTTON_A_Tasks(void);
```
End file
```c
#endif
```
Your app_buttonA.h file should look like this:
```c
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// Include Header Guards
#ifndef APP_BUTTON_A_H
#define	APP_BUTTON_A_H

// Include Standard Libraries
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

// Define Application States
typedef enum{
    APP_BUTTON_A_STATE_INIT = 0,
    APP_BUTTON_A_STATE_HIGH = 1, 
    APP_BUTTON_A_STATE_DEBOUNCE = 2,
    APP_BUTTON_A_STATE_LOW = 3 
}APP_BUTTON_A_STATES;

// Define Data for Application
typedef struct{
    APP_BUTTON_A_STATES state;
    int debounce_count;
}APP_BUTTON_A_DATA;
extern APP_BUTTON_A_DATA app_button_a_data;

// Functions Declarations
void APP_BUTTON_A_Init(void);
void APP_BUTTON_A_Tasks(void);

#endif
```
![Hfile](/screenshots/headerFileAppButtonA.png)
#### Creating *app_buttonA.c* file
Go to *Projects* and right click under *Source Files*, select *New* and *main.c*, provide the same name you used for the .h file and click *Finish*
![new_c_file](/screenshots/appButton_Cfile.png)

Remove or clean all content on the file just created and lets start!

Include the header file we created previously as well as the mcc.h file the system created for us when we configured the pheripherals
```c
#include "app_buttonA.h"
#include "mcc_generated_files/mcc.h"
```
Declare app's data
```c
APP_BUTTON_A_DATA app_button_a_data;
```
Write function to initialize the app
```c
void APP_BUTTON_A_Init(void){
    app_button_a_data.state = APP_BUTTON_A_STATE_INIT;
    app_button_a_data.debounce_count = 0;
}
```
Write a function that describes what happens when the push button or KEY is pressed, in this case we want to toggle the *LedA*
```c
void when_button_a_pushed(void){
    LedA_Toggle();
}
```
*LedA_Toggle()* is a existing function that was created by the system when we generated code for our peripherials

Describe the state machine behaviour in C
```c
void APP_BUTTON_A_Tasks(void){
    switch(app_button_a_data.state){
        case APP_BUTTON_A_STATE_INIT:
            if (ButtonA_GetValue() == 1){
                app_button_a_data.state = APP_BUTTON_A_STATE_HIGH;
            }
            else{
                app_button_a_data.state = APP_BUTTON_A_STATE_LOW;
            }
            break;
        
        case APP_BUTTON_A_STATE_HIGH:
            if (ButtonA_GetValue() == 0){
                app_button_a_data.state = APP_BUTTON_A_STATE_DEBOUNCE;
                app_button_a_data.debounce_count = 0;
            }
            break;
        
        case APP_BUTTON_A_STATE_DEBOUNCE:
            if (app_button_a_data.debounce_count >= 20){
                if (ButtonA_GetValue() == 0){
                    app_button_a_data.state = APP_BUTTON_A_STATE_LOW;
                }
                else{
                    // A valid key-press happens here
                    app_button_a_data.state = APP_BUTTON_A_STATE_HIGH;
                    when_button_a_pushed();
                }       
            }
            break;
        
        case APP_BUTTON_A_STATE_LOW:
            if (ButtonA_GetValue() == 1){
                app_button_a_data.state = APP_BUTTON_A_STATE_DEBOUNCE;
                app_button_a_data.debounce_count = 0;
            }
            break;
    }
}
```
Save changes on *app_buttonA.c*

#### Modifing *tmr1.c* file
Now, lets use that Timer interruption we configure previously. Go to *Projects* Tab and find the *tmr1.c* file on *Source Files* folder and include *app_buttonA.h* file
```c
#include "../app_buttonA.h"
```
![tmr1_file](/screenshots/tmr1CfileIncludeFile.png)
Scroll down until you find the *tmr1_callBack* function, and increment our counter everytime the function gets called, in this case this function will get called every 1 ms as that's how we configured in using MCC
```c
// Add one to counter every 1.0 ms
app_button_a_data.debounce_count++;
```
![modify_tmr1File](/screenshots/modifyTmr1CFile.png)
#### Modifing *main.c* file
Lets go to main.c and complement it with the code we have wrote
1. Include *app_buttonA.h*
```c
#include "app_buttonA.h"
```
![app_hFiletoManin](/screenshots/appHFileIntoMain.png)

2. Initialize the app with the function we wrote to do so on *app_buttonA.c* file
```c
APP_BUTTON_A_Init();
```
![init_app](/screenshots/initAppOnMain.png)

3. Enable Interrups 

When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits, to do that just uncomment the functions that enable it.
```c
// Enable the Global Interrupts
INTERRUPT_GlobalInterruptEnable();

// Enable the Peripheral Interrupts
INTERRUPT_PeripheralInterruptEnable();
```
![enabelInterrups](/screenshots/enableInterrupt.png)

4. Add the app function that take cares of our button task
```c
// Add your application code
APP_BUTTON_A_Tasks();
```
![addAppToMain](/screenshots/addAppToMain.png)

5. Build and debug

Click on *Clean and Build* Button
![cleanBuild](/screenshots/cleanBuild.png)

If successful click on *Debug Main Project* to test the program on your debug Tool
![debugProject](/screenshots/DebbugingWithTool.png)
Wnen running, you should be able to tets, pushing a **button** on your DevTool and seeing a **led** going on and off.

