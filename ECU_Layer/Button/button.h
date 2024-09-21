/* 
 * File:   button.h
 * Author: hesham
 *
 * Created on October 16, 2023, 5:40 AM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include"../../MCAL_Layer/GPIO/GPIO.h"

typedef enum{
    BTN_ACTIVE_HIGH,
    BTN_ACTIVE_LOW        
}ACTIVE_STATE;

typedef enum{
    BTN_NOT_PRESSESD,
    BTN_PRESSESD
}BTN_STATUS;

typedef struct{
    GPIO_Pin_Config pin_config; 
    BTN_STATUS   status ;
    ACTIVE_STATE active ;
}BTN;

Return_Status btn_init(BTN* btn);
Return_Status btn_read_state(BTN* btn,BTN_STATUS* read_state);

#endif	/* BUTTON_H */

