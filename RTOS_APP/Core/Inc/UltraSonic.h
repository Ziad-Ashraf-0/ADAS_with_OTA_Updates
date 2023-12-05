#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "stm32f4xx_hal.h"

#define ULTRA_SONIC1_TRIG  GPIO_PIN_8
#define ULTRA_SONIC2_TRIG  GPIO_PIN_10
#define ULTRA_SONIC3_TRIG  GPIO_PIN_12
#define ULTRA_SONIC4_TRIG  GPIO_PIN_15


#define ULTRA_SONIC1_TRIG_PORT  GPIOE
#define ULTRA_SONIC2_TRIG_PORT  GPIOE
#define ULTRA_SONIC3_TRIG_PORT  GPIOE
#define ULTRA_SONIC4_TRIG_PORT  GPIOE


#define MIN_PULSE_TIME_INMICRO         10
#define TIME_BETWEEN_READINGS_INMILI   10
#define TIME_OUT_INMICRO               6000
#define TIME_TOGET_ONE_CM              58
#define Timer_Pre_Scaler               8
#define CPU_FREQ                       8


#define OVF_VALUE_T1 65535


//This Enum for Choosing Which UltraSonic To work at.
typedef enum
{
	ULTRASONIC1=0,
	ULTRASONIC2=1,
	ULTRASONIC3=2,
	ULTRASONIC4=3,
	ULTRASONIC1_4=4,
	TOTAL_ULTRA_SONIC
	
}Ultra_Sonic_Type;


//This Enum for Reading Exists or Not Checking.
typedef enum
{
	NO_READ=0,
	READ_EXIST=1
	
}Read_Status;

typedef enum
{
	COUNTING_EVENT_UNDONE=0,
	COUNTING_EVENT_DONE=1

}Counting_Event_Status;

typedef enum{
	RISING=TIM_INPUTCHANNELPOLARITY_RISING,
	FALLING=TIM_INPUTCHANNELPOLARITY_FALLING
}ICU_Edge_type;



Read_Status UltraSonic_ReadStatusENUM_GetRead(Ultra_Sonic_Type Ultra_Sonic, uint16_t distances[], size_t numDistances);




#endif
