/*
 * File:   app_buttonA.c
 * Author: cool1
 *
 * Created on July 27, 2023, 1:08 PM
 */
#include "app_buttonA.h"
#include "mcc_generated_files/mcc.h"

//App ButtonA Data Declaration
APP_BUTTON_A_DATA app_button_a_data;

// Init App
void APP_BUTTON_A_Init(void){
    app_button_a_data.state = APP_BUTTON_A_STATE_INIT;
    app_button_a_data.debounce_count = 0;
}

// Function to run when Button A is Pushed
void when_button_a_pushed(void){
    LedA_Toggle();
}

// State Machine Description and Behaviour App 
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
