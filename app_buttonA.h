/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef APP_BUTTON_A_H
#define	APP_BUTTON_A_H

// Include Files
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