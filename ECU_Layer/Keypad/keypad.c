/* 
 * File:   keypad.c
 * Author: hesham
 *
 */
#include <util/delay.h>

#include"keypad.h"
uint8_t keypad_values[KEYPAD_ROWS][KEYPAD_COLUMNS]={
                                    {'7','8','9','/'},
                                    {'4','5','6','*'},
                                    {'1','2','3','-'},
                                    {'#','0','=','+'}
                                              };
Return_Status keypad_initialize(Keypad_t* keypad)
{
    Return_Status ret = R_NOK;
    if(keypad!=NULL)
    {
        for(int i=0;i<KEYPAD_ROWS;i++)
        {
            GPIO_Pin_Init(&(keypad->keypad_row[i]));
        }
        for(int i=0;i<KEYPAD_COLUMNS;i++)
        {
            GPIO_Pin_Init(&(keypad->keypad_column[i]));
        }
    }
    return ret;
}
Return_Status keypad_get_value(Keypad_t *keypad,uint8_t *value)
{
    Return_Status ret = R_NOK;
    if(keypad!=NULL)
    {
        for(int row_counter=0;row_counter<KEYPAD_ROWS;row_counter++)
        {
            for(int j=0;j<KEYPAD_ROWS;++j)
            {
                GPIO_Set_Pin_Logic(&(keypad->keypad_row[j]),GPIO_LOGIC_LOW);
            }
            GPIO_Set_Pin_Logic(&(keypad->keypad_row[row_counter]),GPIO_LOGIC_HIGH);
            _delay_ms(30);
            for(int col_counter=0;col_counter<KEYPAD_COLUMNS;++col_counter)
            {
            uint8_t column_value;
            GPIO_Get_Pin_Logic(&(keypad->keypad_column[col_counter]),&column_value);
            if(GPIO_LOGIC_HIGH==column_value)
            {
                *value=keypad_values[row_counter][col_counter]; 
                break;
            }
            }
        }
    }
    return ret;
}

