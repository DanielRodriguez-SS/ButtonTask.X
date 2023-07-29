# Embedded C with Microchip MPLABX
## Project Name: ButtonTask.X
On this project we will implement a system using a chip **PIC16F18466** that will be able to get a trigger signal from a *push button* to handle a task, in this case, that task will be *toggling an LED*
### Setting the MPLABX project
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