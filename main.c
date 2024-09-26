#include "ECU_Layer/Ecu_Init/ecu_init.h"
#include "MCAL_Layer/Timer1/timer1.h"
#include "MCAL_Layer/Timer0/timer0.h"
#include "ECU_Layer/US_Sensor/US.h"


uint16_t volatile  duration;
void icu_isr() {
	uint16_t capture_time = MCAL_Timer1_Get_ICU();  // Read the captured value
	static uint8_t current_edge = TIMER1_MODE_ICU_RISING_EDGE_CFG;
	
	if (current_edge == TIMER1_MODE_ICU_RISING_EDGE_CFG) {  // Rising edge detected
		rising_edge_time = capture_time;  // Store the rising edge time
		MCAL_Timer1_ICU_Switch_Edge(TIMER1_MODE_ICU_FALLING_EDGE_CFG);  // Switch to falling edge capture
		current_edge = TIMER1_MODE_ICU_FALLING_EDGE_CFG;
		} else {  // Falling edge detected
		falling_edge_time = capture_time;  // Store the falling edge time
	    duration = falling_edge_time - rising_edge_time;
		capture_done = 1;  // Set capture_done flag to indicate measurement is complete
		MCAL_Timer1_ICU_Switch_Edge(TIMER1_MODE_ICU_RISING_EDGE_CFG);  // Switch back to rising edge
		current_edge = TIMER1_MODE_ICU_RISING_EDGE_CFG;
	}
}
Timer0_Config_t pwm_module={.mode=TIMER0_MODE_Fast_PWM,.clock_source=TIMER0_PRESCALER_DIVIDED_BY_1};
Timer1_Config_t t1_obj = {
	.edge = TIMER1_MODE_ICU_RISING_EDGE_CFG,
	.Timer1_InterruptHandler = icu_isr,
	.mode = TIMER1_MODE_ICU,
	.prescaler = TIMER1_PRESCALER_DIVIDED_BY_8  
};

US_Sensor_t us1;
uint16_t distance;
uint8_t speed;

int main() {
	// Initialize Timer1 for Input Capture
	MCAL_Timer1_Init(&t1_obj);
	MCAL_Timer0_Init(&pwm_module);
	HAL_US_Sensor_Init(&us1);
	lcd_4bit_initialize(&lcd1);
	dc_motor_initialize(&CAR_M1);
	dc_motor_initialize(&CAR_M2);
	char lcd_distance[33];
	GPIO_Pin_Config x={.direction=GPIO_DIRECTION_OUTPUT,.pin=PIN3,.port=PORTB};
		GPIO_Pin_Init(&x);
	while(1)
	{
		for (int i=0;i<=100;++i)
		{
			MCAL_Timer0_Set_PWM_Duty_Cycle(0);
			if(i==0) _delay_ms(2000);
			_delay_ms(200);
		}
	}
	while (1) {
		HAL_US_Sensor_Trigger(&us1);  // Send a trigger pulse to the ultrasonic sensor
		_delay_ms(50);
		if (capture_done) {
			// Once capture is complete, calculate the pulse width
			distance = HAL_US_Sensor_Meaure_Distance(&us1,duration);  // Get the distance in cm
			if (distance<20)
			{
				speed=0;
			}
			else if(distance>20&&distance<30)
			{
				speed=50;
			}
			else
			{
				speed=100;
			}
			lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
			MCAL_Timer0_Set_PWM_Duty_Cycle(speed);
			sprintf(lcd_distance, "Distance: %u cm ||Speed: %u ", distance,speed);
			lcd_4bit_send_string(&lcd1, lcd_distance);
			_delay_ms(100);
			capture_done = 0;  // Reset capture_done flag for the next measurement
		}
	}
}
