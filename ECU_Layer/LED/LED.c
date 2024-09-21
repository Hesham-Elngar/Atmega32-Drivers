#include"LED.h"

Return_Status LED_init(LED *led){
    Return_Status ret=R_NOK;
    if(led!=NULL){
        ret=R_OK;
        GPIO_Pin_Config led_obj={
            .direction=GPIO_DIRECTION_OUTPUT,
            .logic=GPIO_LOGIC_LOW,
            .pin=led->pin,
            .port=led->port
        };
        GPIO_Set_Pin_Direction(&led_obj,GPIO_DIRECTION_OUTPUT);
    }
    return ret;
}
Return_Status LED_on(LED *led){
    Return_Status ret=R_NOK;
    if(led!=NULL){
        ret=R_OK;
          GPIO_Pin_Config led_obj={
            .direction=GPIO_DIRECTION_OUTPUT,
            .logic=GPIO_LOGIC_HIGH,
            .pin=led->pin,
            .port=led->port
        };
          GPIO_Set_Pin_Logic(&led_obj,led_obj.logic);
        
    }
    return ret;
}
Return_Status LED_off(LED *led){
     Return_Status ret=R_NOK;
    if(led!=NULL){
        ret=R_OK;
          GPIO_Pin_Config led_obj={
            .direction=GPIO_DIRECTION_OUTPUT,
            .logic=GPIO_LOGIC_LOW,
            .pin=led->pin,
            .port=led->port
        };
            GPIO_Set_Pin_Logic(&led_obj,led_obj.logic);
    }
    return ret;
}
Return_Status LED_toggle(LED *led){
    Return_Status ret=R_NOK;
    if(led!=NULL){
        ret=R_OK;
          GPIO_Pin_Config led_obj={
            .direction=GPIO_DIRECTION_OUTPUT,
            .logic=GPIO_LOGIC_LOW,
            .pin=led->pin,
            .port=led->port
        };
          GPIO_Toggle_Pin(&led_obj);
    }
    return ret;
}