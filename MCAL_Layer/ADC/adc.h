/*
 * adc.h
 *
 * Created: 9/1/2024 4:53:54 AM
 *  Author: Hesham
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

#define ADMUX	(*(volatile uint8_t*)0x27)
#define ADCSRA	(*(volatile uint8_t*)0x26)
#define ADCH	(*(volatile uint8_t*)0x25)
#define ADCL	(*(volatile uint8_t*)0x24)
#define SFIOR	(*(volatile uint8_t*)0x50)

// SFIOR START
//@trigger_soruce
#define ADC_Trigger_Source_Free_Running    (0<<5)
#define ADC_Trigger_Source_Free_EXTI0	   (2<<5)
#define ADC_Trigger_Source_T0_CompareMatch (3<<5)
#define ADC_Trigger_Source_T0_OVF		   (4<<5)
#define ADC_Trigger_Source_T1_OVF		   (6<<5)
// SFIOR END

//ADMUX START
//@VRFF
#define VRFF_Internal_Vref_turnedOff			 	   (0<<6)
#define VRFF_AVCC_with_EXT_Cap	 				       (1<<6)
#define VRFF_Internal_2_56V_VoltageReference_Ext_Cap   (3<<6)

//@ADC Left Adjust Result
#define ADC_Left_Adjust_Result  (1<<5)
#define ADC_Right_Adjust_Result (0<<5)

// Bits 4:0 – MUX4:0: Analog Channel and Gain Selection Bits 
#define ADC_AN0_SingleEnded 0<<0
#define ADC_AN1_SingleEnded 1<<0
#define ADC_AN2_SingleEnded 2<<0
#define ADC_AN3_SingleEnded 3<<0
#define ADC_AN4_SingleEnded 4<<0
#define ADC_AN5_SingleEnded 5<<0
#define ADC_AN6_SingleEnded 6<<0
#define ADC_AN7_SingleEnded 7<<0



//ADMUX END
//ADCSRA START
//@ADEN
#define ADC_ENABLE	(1<<7)
#define ADC_DISABLE	(0<<7)
//ADSC: ADC Start Conversion
#define ADC_Start_Conversion (1<<6)
//@ ADATE: ADC Auto Trigger Enable
#define ADC_AutoTrigger_Enable (1<<5)
//Bit 4 – ADIF: ADC Interrupt Flag
#define ADC_Interrupt_Flag (1<<4)
//@ADIE: ADC Interrupt Enable
#define ADC_Interrupt_Enable (1<<3)

//@prescaler
#define ADC_Prescaler_Divided_By_1	  (0<<0)
#define ADC_Prescaler_Divided_By_2	  (1<<0)
#define ADC_Prescaler_Divided_By_4	  (2<<0)
#define ADC_Prescaler_Divided_By_8	  (3<<0)
#define ADC_Prescaler_Divided_By_16	  (4<<0)
#define ADC_Prescaler_Divided_By_32	  (5<<0)
#define ADC_Prescaler_Divided_By_64	  (6<<0)
#define ADC_Prescaler_Divided_By_128  (7<<0)
//ADCSRA END

//@MECHANISM
typedef enum
{
	POLLING_MECHANISM,
	INTERRUPT_MECHANISM
}MECHANISM;

typedef struct
{
	uint8_t analog_channel:4;
	uint8_t trigger_soruce:3; //@trigger_soruce
	uint8_t Adjust_Result:1; ////@ADC Left Adjust Result + Recommeded->Right-Justified Mode
	uint8_t voltage_reference:2;  //@VRFF
	uint8_t prescaler:2;//@prescaler
	MECHANISM mechanism; //@MECHANISM
	void (*ADC_InterruptHandler)(void);
}ADC_Config_t;


void MCAL_ADC_Init(ADC_Config_t* adc_obj);
void MCAL_ADC_Start_Conversion(void);
uint16_t MCAL_ADC_Get_Conversion_Result_Polling(void);


#endif /* ADC_H_ */


//differential Wire for AN Channel Not used in this Driver
/*
// ADC0 and ADC1 differential with gain
#define ADC0_ADC0_10x 0x08  // ADC0 positive, ADC0 negative, gain 10x
#define ADC1_ADC0_10x 0x09  // ADC1 positive, ADC0 negative, gain 10x
#define ADC0_ADC0_200x 0x0A // ADC0 positive, ADC0 negative, gain 200x
#define ADC1_ADC0_200x 0x0B // ADC1 positive, ADC0 negative, gain 200x

// ADC2 and ADC2 differential with gain
#define ADC2_ADC2_10x 0x0C  // ADC2 positive, ADC2 negative, gain 10x
#define ADC3_ADC2_10x 0x0D  // ADC3 positive, ADC2 negative, gain 10x
#define ADC2_ADC2_200x 0x0E // ADC2 positive, ADC2 negative, gain 200x
#define ADC3_ADC2_200x 0x0F // ADC3 positive, ADC2 negative, gain 200x

// ADC0 and ADC1 differential with gain 1x
#define ADC0_ADC1_1x 0x10  // ADC0 positive, ADC1 negative, gain 1x
#define ADC1_ADC1_1x 0x11  // ADC1 positive, ADC1 negative, gain 1x
#define ADC2_ADC1_1x 0x12  // ADC2 positive, ADC1 negative, gain 1x
#define ADC3_ADC1_1x 0x13  // ADC3 positive, ADC1 negative, gain 1x
#define ADC4_ADC1_1x 0x14  // ADC4 positive, ADC1 negative, gain 1x
#define ADC5_ADC1_1x 0x15  // ADC5 positive, ADC1 negative, gain 1x
#define ADC6_ADC1_1x 0x16  // ADC6 positive, ADC1 negative, gain 1x
#define ADC7_ADC1_1x 0x17  // ADC7 positive, ADC1 negative, gain 1x

// ADC0 and ADC2 differential
#define ADC0_ADC2_1x 0x18  // ADC0 positive, ADC2 negative, gain 1x
#define ADC1_ADC2_1x 0x19  // ADC1 positive, ADC2 negative, gain 1x
#define ADC2_ADC2_1x 0x1A  // ADC2 positive, ADC2 negative, gain 1x
#define ADC3_ADC2_1x 0x1B  // ADC3 positive, ADC2 negative, gain 1x
#define ADC4_ADC2_1x 0x1C  // ADC4 positive, ADC2 negative, gain 1x





*/