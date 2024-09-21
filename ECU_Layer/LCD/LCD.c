/* 
 * File:   LCD.c
 * Author: hesham
 *
 * Created on October 31, 2023, 12:46 AM
 */
#include"LCD.h"


static void lcd_4bit_send_4_bit(Lcd_4bit* lcd,uint8_t command);
static void lcd_4bit_send_enable_signal(Lcd_4bit* lcd);
static void lcd_8bit_send_enable_signal(Lcd_8bit* lcd);
static void lcd_8bit_set_cursor(Lcd_8bit* lcd,uint8_t row,uint8_t column);
static void lcd_4bit_set_cursor(Lcd_4bit* lcd,uint8_t row,uint8_t column);

Return_Status lcd_4bit_initialize(Lcd_4bit* lcd){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        GPIO_Pin_Init(&(lcd->rs));
        GPIO_Pin_Init(&(lcd->en));
        for(int i=0;i<4;i++){
            GPIO_Pin_Init(&lcd->data[i]);
        }
        _delay_ms(20);
        lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        _delay_ms(5); 
        lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        _delay_us(150); 
        lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        lcd_4bit_send_command(lcd,_LCD_CLEAR);
        lcd_4bit_send_command(lcd,_LCD_RETURN_HOME);
        lcd_4bit_send_command(lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
        lcd_4bit_send_command(lcd,_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        lcd_4bit_send_command(lcd,_LCD_4BIT_MODE_2_LINE);
        lcd_4bit_send_command(lcd,0x80);
   }
    return ret;
}

Return_Status lcd_4bit_send_command(Lcd_4bit* lcd,uint8_t command){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        GPIO_Set_Pin_Logic(&lcd->rs,GPIO_LOGIC_LOW);
        lcd_4bit_send_4_bit(lcd,command>>4);
        lcd_4bit_send_enable_signal(lcd);
        lcd_4bit_send_4_bit(lcd,command);
        lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
} 

Return_Status lcd_4bit_send_char_data(Lcd_4bit *lcd,uint8_t data){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        GPIO_Set_Pin_Logic(&lcd->rs,GPIO_LOGIC_HIGH);
        lcd_4bit_send_4_bit(lcd,data>>4);
        lcd_4bit_send_enable_signal(lcd);
        lcd_4bit_send_4_bit(lcd,data);
        lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

Return_Status lcd_4bit_send_char_data_pos(Lcd_4bit* lcd,uint8_t row,uint8_t column,uint8_t data)
{
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        lcd_4bit_set_cursor(lcd,row,column);
        lcd_4bit_send_char_data(lcd,data);
    }
    return ret;
}

Return_Status lcd_4bit_send_custom_chr(Lcd_4bit* lcd,uint8_t row,uint8_t column,uint8_t custom_chr[],uint8_t mem_pos){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        lcd_4bit_send_command(lcd,_LCD_CGRAM_START+(8*mem_pos));
        for(int i=0;i<8;i++){
            lcd_4bit_send_char_data(lcd,custom_chr[i]);
        }
        lcd_4bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    return ret;
}

Return_Status lcd_4bit_send_string(Lcd_4bit* lcd,uint8_t* str)
{
   Return_Status ret=R_NOK;
    if(lcd!=NULL){
       ret=R_OK;
       while(*str!='\0'){
           lcd_4bit_send_char_data(lcd,*str++);
       }
    }
    return ret; 
}

Return_Status lcd_4bit_send_string_pos(Lcd_4bit* lcd,uint8_t row,uint8_t column,uint8_t* str)
{
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
       ret=R_OK;
       lcd_4bit_set_cursor(lcd,row,column);
       while(*str!='\0'){
           lcd_4bit_send_char_data(lcd,*str++);
       }
    }
    return ret;
}


/************************************************************************************************************/
Return_Status lcd_8bit_initialize(Lcd_8bit* lcd){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        GPIO_Pin_Init(&(lcd->rs));
        GPIO_Pin_Init(&(lcd->en));
        for(int i=0;i<8;i++){
            GPIO_Pin_Init(&lcd->data[i]);
        }
        _delay_ms(20);
        lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        _delay_ms(5); 
        lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        _delay_us(150); 
        lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        lcd_8bit_send_command(lcd,_LCD_CLEAR);
        lcd_8bit_send_command(lcd,_LCD_RETURN_HOME);
        lcd_8bit_send_command(lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
        lcd_8bit_send_command(lcd,_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        lcd_8bit_send_command(lcd,0x80);
   }
    return ret;
}
Return_Status lcd_8bit_send_command(Lcd_8bit* lcd,uint8_t command){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        GPIO_Set_Pin_Logic(&lcd->rs,GPIO_LOGIC_LOW);
        for(int i=0;i<8;i++){
            GPIO_Set_Pin_Logic(&(lcd->data[i]),(command>>i)&0x01);
        }
        lcd_8bit_send_enable_signal(lcd);   
    }
    return ret;
}
Return_Status lcd_8bit_send_char_data(Lcd_8bit* lcd,uint8_t data){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        GPIO_Set_Pin_Logic(&lcd->rs,GPIO_LOGIC_HIGH);
        for(int i=0;i<8;i++){
            GPIO_Set_Pin_Logic(&(lcd->data[i]),(data>>i)&0x01);
        }
        lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}
Return_Status lcd_8bit_send_char_data_pos(Lcd_8bit* lcd,uint8_t row,uint8_t column,uint8_t data){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        lcd_8bit_set_cursor(lcd,row,column);
        lcd_8bit_send_char_data(lcd,data);
    }
    return ret;
}
Return_Status lcd_8bit_send_custom_chr(Lcd_8bit* lcd,uint8_t row,uint8_t column,uint8_t custom_chr[],uint8_t mem_pos){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        lcd_8bit_send_command(lcd,_LCD_CGRAM_START+(8*mem_pos));
        for(int i=0;i<8;i++){
            lcd_8bit_send_char_data(lcd,custom_chr[i]);
        }
        lcd_8bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    return ret;
}

Return_Status lcd_8bit_send_string(Lcd_8bit* lcd,uint8_t* str){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
       ret=R_OK;
       while(*str!='\0'){
           lcd_8bit_send_char_data(lcd,*str++);
       }
    }
    return ret;
}

Return_Status lcd_8bit_send_string_pos(Lcd_8bit* lcd,uint8_t row,uint8_t column,uint8_t* str)
{
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
       ret=R_OK;
       lcd_8bit_set_cursor(lcd,row,column);
       while(*str!='\0'){
           lcd_8bit_send_char_data(lcd,*str++);
       }
    }
    return ret;
    
}


void convert_byte_to_string(uint8_t value,uint8_t* str){
    if(str){
        memset(str,'\0',4);
        sprintf(str,"%i",value);
    }
}
void convert_short_to_string(uint16_t value,uint8_t* str){
     if(str){
        memset(str,'\0',6);
        sprintf(str,"%i",value);
    }
}
void convert_int_to_string(uint32_t value,uint8_t* str){
     if(str){
        memset(str,'\0',11);
        sprintf(str,"%i",value);
    }
}


static void lcd_4bit_send_4_bit(Lcd_4bit* lcd,uint8_t command){
    for(int i=0;i<4;i++){
        GPIO_Set_Pin_Logic(&lcd->data[i],(command>>i)&0x01);
    }
}
static void lcd_4bit_send_enable_signal(Lcd_4bit* lcd){
    GPIO_Set_Pin_Logic(&(lcd->en),GPIO_LOGIC_HIGH);
    _delay_us(2);
    GPIO_Set_Pin_Logic(&(lcd->en),GPIO_LOGIC_LOW);
}
static void lcd_8bit_send_enable_signal(Lcd_8bit* lcd){
    GPIO_Set_Pin_Logic(&(lcd->en),GPIO_LOGIC_HIGH);
    _delay_us(2);
    GPIO_Set_Pin_Logic(&(lcd->en),GPIO_LOGIC_LOW);
}
static void lcd_8bit_set_cursor(Lcd_8bit* lcd,uint8_t row,uint8_t column){
    column--;
    switch(row){
        case 1:  lcd_8bit_send_command(lcd,(0x80+column)); break;
        case 2:  lcd_8bit_send_command(lcd,(0xc0+column)); break;
        case 3:  lcd_8bit_send_command(lcd,(0x94+column)); break;
        case 4 : lcd_8bit_send_command(lcd,(0xd4+column)); break;
        default:;
    }   
}
static void lcd_4bit_set_cursor(Lcd_4bit* lcd,uint8_t row,uint8_t column){
    column--;
    switch(row){
        case 1:  lcd_4bit_send_command(lcd,(0x80+column)); break;
        case 2:  lcd_4bit_send_command(lcd,(0xc0+column)); break;
        case 3:  lcd_4bit_send_command(lcd,(0x94+column)); break;
        case 4 : lcd_4bit_send_command(lcd,(0xd4+column)); break;
        default:;
    }   
}