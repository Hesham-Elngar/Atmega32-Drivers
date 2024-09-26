/*
 * motor.c
 *
 * Created: 9/25/2024 1:46:25 AM
 *  Author: HESHAM
 */ 
#include"motor.h"

void dc_motor_initialize(const dc_motor_t *_dc_motor){
    
    if(NULL == _dc_motor){
        return;
    }
    else{    
        GPIO_Pin_Init(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
        GPIO_Pin_Init(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));
    }
}

void dc_motor_move_right(const dc_motor_t *_dc_motor){
    
    if(NULL == _dc_motor){
        return;
    }
    else{
        GPIO_Set_Pin_Logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOGIC_HIGH);
        GPIO_Set_Pin_Logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOGIC_LOW);
    }
}

void dc_motor_move_left(const dc_motor_t *_dc_motor){
    
    if(NULL == _dc_motor){
        return;
    }
    else{
        GPIO_Set_Pin_Logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOGIC_LOW);
        GPIO_Set_Pin_Logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOGIC_HIGH);
    }
}

/**
 * @brief stop the motor movement
 * @param _dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
void dc_motor_stop(const dc_motor_t *_dc_motor){
    
    if(NULL == _dc_motor){
        return;
    }
    else{
        GPIO_Set_Pin_Logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOGIC_LOW);
        GPIO_Set_Pin_Logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOGIC_LOW);
    }
}

