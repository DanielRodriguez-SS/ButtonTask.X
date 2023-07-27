/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F18446
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set ButtonA aliases
#define ButtonA_TRIS                 TRISCbits.TRISC4
#define ButtonA_LAT                  LATCbits.LATC4
#define ButtonA_PORT                 PORTCbits.RC4
#define ButtonA_WPU                  WPUCbits.WPUC4
#define ButtonA_OD                   ODCONCbits.ODCC4
#define ButtonA_ANS                  ANSELCbits.ANSC4
#define ButtonA_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define ButtonA_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define ButtonA_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define ButtonA_GetValue()           PORTCbits.RC4
#define ButtonA_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define ButtonA_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define ButtonA_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define ButtonA_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define ButtonA_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define ButtonA_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define ButtonA_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define ButtonA_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set LedA aliases
#define LedA_TRIS                 TRISCbits.TRISC5
#define LedA_LAT                  LATCbits.LATC5
#define LedA_PORT                 PORTCbits.RC5
#define LedA_WPU                  WPUCbits.WPUC5
#define LedA_OD                   ODCONCbits.ODCC5
#define LedA_ANS                  ANSELCbits.ANSC5
#define LedA_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define LedA_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define LedA_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define LedA_GetValue()           PORTCbits.RC5
#define LedA_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define LedA_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define LedA_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define LedA_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define LedA_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define LedA_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define LedA_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define LedA_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/