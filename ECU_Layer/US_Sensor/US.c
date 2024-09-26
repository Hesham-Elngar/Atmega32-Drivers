#include "US.h"

volatile uint8_t capture_done = 0;  // Flag to indicate when measurement is complete
volatile uint16_t rising_edge_time = 0;
volatile uint16_t falling_edge_time = 0;

void HAL_US_Sensor_Init(US_Sensor_t* US_Sensor_obj) {
	// Initialize Trigger pin
	US_Sensor_obj->Trigger_pin.direction = GPIO_DIRECTION_OUTPUT;
	US_Sensor_obj->Trigger_pin.logic = GPIO_LOGIC_LOW;
	US_Sensor_obj->Trigger_pin.pin = PIN5;
	US_Sensor_obj->Trigger_pin.port = PORTD;

	// Initialize Echo pin
	US_Sensor_obj->Echo_pin.direction = GPIO_DIRECTION_INPUT;
	US_Sensor_obj->Echo_pin.logic = GPIO_LOGIC_LOW;
	US_Sensor_obj->Echo_pin.pin = PIN6;
	US_Sensor_obj->Echo_pin.port = PORTD;

	GPIO_Pin_Init(&(US_Sensor_obj->Trigger_pin));
	GPIO_Pin_Init(&(US_Sensor_obj->Echo_pin));
}

void HAL_US_Sensor_Trigger(US_Sensor_t* US_Sensor_obj) {
	// Send trigger pulse to the ultrasonic sensor
	GPIO_Set_Pin_Logic(&(US_Sensor_obj->Trigger_pin), GPIO_LOGIC_LOW);  // Low for 2us
	_delay_us(2);
	GPIO_Set_Pin_Logic(&(US_Sensor_obj->Trigger_pin), GPIO_LOGIC_HIGH);  // High for 10us
	_delay_us(10);
	GPIO_Set_Pin_Logic(&(US_Sensor_obj->Trigger_pin), GPIO_LOGIC_LOW);  // Back to low
}

uint16_t HAL_US_Sensor_get_pulse_width() {
	// Calculate the pulse width by subtracting the rising edge time from the falling edge time
	return falling_edge_time - rising_edge_time;
}

uint16_t HAL_US_Sensor_Meaure_Distance(US_Sensor_t* US_Sensor_obj,uint16_t duration) {
	float distance = 0;
		distance = (duration * 0.034) / 2;
		capture_done = 0;  // Reset the capture_done flag
		return distance;  // Return the distance as an integer
}
