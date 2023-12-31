/*
 * lane_detection.c
 *
 *  Created on: Dec 1, 2023
 *      Author: Ziad
 */

#include "Motor_Interfce.h"
#include "IR_Sensor_Interface.h"
#include "lane_detection.h"

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

uint8_t IR_Sensors_Values[5];
int32_t Motor_Speed;
int32_t Motor_Base_Speed = 100;
int32_t RightMotorSpeed, LeftMotorSpeed;
int32_t MotorMaxSpeed =100;
int32_t SumError;

// PID Parameters
int32_t Error = 0;
int32_t PreError = 0;
int32_t Kp = 25;
int32_t Kd = 3;
int32_t Ki = 0;

/**
 * @brief To make Car Interact with us with lane assist.
 *
 * This Function give two sides same directions with different speeds
 *
 * @param PWM_Sig_right PWM signal for Right side
 * @param PWM_Sig_left  PWM signal for Left side
 * @return return void.
 * */
void Car_Void_Go_Lane(uint8_t PWM_Sig_right, uint8_t PWM_Sig_left)
{
	Motor_Void_Move(GPIOG, GPIO_PIN_10, GPIOG, GPIO_PIN_11, PWM_Sig_right, htim3, MOTOR_CCW_DIRECTION); 	// right motors
	Motor_Void_Move(GPIOG, GPIO_PIN_8, GPIOG, GPIO_PIN_9, PWM_Sig_left, htim4, MOTOR_CCW_DIRECTION);    // left motors
}

void Lane_Runnable(void)
{

	/* Read Sensors Values */
	IR_Void_ReadColor(GPIOD, GPIO_PIN_0, &IR_Sensors_Values[0]);
	IR_Void_ReadColor(GPIOD, GPIO_PIN_1, &IR_Sensors_Values[1]);
	IR_Void_ReadColor(GPIOD, GPIO_PIN_3, &IR_Sensors_Values[2]);
	IR_Void_ReadColor(GPIOD, GPIO_PIN_4, &IR_Sensors_Values[3]);
	IR_Void_ReadColor(GPIOD, GPIO_PIN_5, &IR_Sensors_Values[4]);

#if LANE_ASSIST_SETUP == LANE_BLACK_GROUND_WHITE_LINE
	/* These Conditions to specify the error and state of Car */
	if((IR_READ_BLACK == IR_Sensors_Values[0]) && (IR_READ_BLACK == IR_Sensors_Values[1]) && (IR_READ_BLACK == IR_Sensors_Values[2]) && (IR_READ_BLACK == IR_Sensors_Values[3]) && (IR_READ_WHITE == IR_Sensors_Values[4]))
	{
		// BBBBW Sate
		Error = 4;
	}
	else if((IR_READ_BLACK == IR_Sensors_Values[0]) && (IR_READ_BLACK == IR_Sensors_Values[1]) && (IR_READ_BLACK == IR_Sensors_Values[2]) && (IR_READ_WHITE == IR_Sensors_Values[3]) && (IR_READ_WHITE == IR_Sensors_Values[4]))
	{
		// BBBWW Sate
		Error = 3;
	}
	else if((IR_READ_BLACK == IR_Sensors_Values[0]) && (IR_READ_BLACK == IR_Sensors_Values[1]) && (IR_READ_BLACK == IR_Sensors_Values[2]) && (IR_READ_WHITE == IR_Sensors_Values[3]) && (IR_READ_BLACK == IR_Sensors_Values[4]))
	{
		// BBBWB Sate
		Error = 2;
	}
	else if((IR_READ_BLACK == IR_Sensors_Values[0]) && (IR_READ_BLACK == IR_Sensors_Values[1]) && (IR_READ_WHITE == IR_Sensors_Values[2]) && (IR_READ_WHITE == IR_Sensors_Values[3]) && (IR_READ_BLACK == IR_Sensors_Values[4]))
	{
		// BBWWB Sate
		Error = 1;
	}
	else if((IR_READ_BLACK == IR_Sensors_Values[0]) && (IR_READ_BLACK == IR_Sensors_Values[1]) && (IR_READ_WHITE == IR_Sensors_Values[2]) && (IR_READ_BLACK == IR_Sensors_Values[3]) && (IR_READ_BLACK == IR_Sensors_Values[4]))
	{
		// BBWBB Sate
		Error = 0;
	}
	else if((IR_READ_BLACK == IR_Sensors_Values[0]) && (IR_READ_WHITE == IR_Sensors_Values[1]) && (IR_READ_WHITE == IR_Sensors_Values[2]) && (IR_READ_BLACK == IR_Sensors_Values[3]) && (IR_READ_BLACK == IR_Sensors_Values[4]))
	{
		// BWWBB Sate
		Error = -1;
	}
	else if((IR_READ_BLACK == IR_Sensors_Values[0]) && (IR_READ_WHITE == IR_Sensors_Values[1]) && (IR_READ_BLACK == IR_Sensors_Values[2]) && (IR_READ_BLACK == IR_Sensors_Values[3]) && (IR_READ_BLACK == IR_Sensors_Values[4]))
	{
		// BWBBB Sate
		Error = -2;
	}
	else if((IR_READ_WHITE == IR_Sensors_Values[0]) && (IR_READ_WHITE == IR_Sensors_Values[1]) && (IR_READ_BLACK == IR_Sensors_Values[2]) && (IR_READ_BLACK == IR_Sensors_Values[3]) && (IR_READ_BLACK == IR_Sensors_Values[4]))
	{
		// WWBBB Sate
		Error = -3;
	}
	else if((IR_READ_WHITE == IR_Sensors_Values[0]) && (IR_READ_BLACK == IR_Sensors_Values[1]) && (IR_READ_BLACK == IR_Sensors_Values[2]) && (IR_READ_BLACK == IR_Sensors_Values[3]) && (IR_READ_BLACK == IR_Sensors_Values[4]))
	{
		// WBBBB Sate
		Error = -4;
	}
	else if((IR_READ_BLACK == IR_Sensors_Values[0]) && (IR_READ_BLACK == IR_Sensors_Values[1]) && (IR_READ_BLACK == IR_Sensors_Values[2]) && (IR_READ_BLACK == IR_Sensors_Values[3]) && (IR_READ_BLACK == IR_Sensors_Values[4]))
	{
		// BBBBB Sate
		Error = PreError;
	}
#elif LANE_ASSIST_SETUP == LANE_WHITE_GROUND_BLACK_LINE
	/* These Conditions to specify the error and state of Car */
	if((IR_READ_WHITE == IR_Sensors_Values[0]) && (IR_READ_WHITE == IR_Sensors_Values[1]) && (IR_READ_WHITE == IR_Sensors_Values[2]) && (IR_READ_WHITE == IR_Sensors_Values[3]) && (IR_READ_BLACK == IR_Sensors_Values[4]))
	{
		// WWWWB Sate
		Error = 4;
	}
	else if((IR_READ_WHITE == IR_Sensors_Values[0]) && (IR_READ_WHITE == IR_Sensors_Values[1]) && (IR_READ_WHITE == IR_Sensors_Values[2]) && (IR_READ_BLACK == IR_Sensors_Values[3]) && (IR_READ_BLACK == IR_Sensors_Values[4]))
	{
		// WWWBB Sate
		Error = 3;
	}
	else if((IR_READ_WHITE == IR_Sensors_Values[0]) && (IR_READ_WHITE == IR_Sensors_Values[1]) && (IR_READ_WHITE == IR_Sensors_Values[2]) && (IR_READ_BLACK == IR_Sensors_Values[3]) && (IR_READ_WHITE == IR_Sensors_Values[4]))
	{
		// WWWBW Sate
		Error = 2;
	}
	else if((IR_READ_WHITE == IR_Sensors_Values[0]) && (IR_READ_WHITE == IR_Sensors_Values[1]) && (IR_READ_BLACK == IR_Sensors_Values[2]) && (IR_READ_BLACK == IR_Sensors_Values[3]) && (IR_READ_WHITE == IR_Sensors_Values[4]))
	{
		// WWBBW Sate
		Error = 1;
	}
	else if((IR_READ_WHITE == IR_Sensors_Values[0]) && (IR_READ_WHITE == IR_Sensors_Values[1]) && (IR_READ_BLACK == IR_Sensors_Values[2]) && (IR_READ_WHITE == IR_Sensors_Values[3]) && (IR_READ_WHITE == IR_Sensors_Values[4]))
	{
		// WWBWW Sate
		Error = 0;
	}
	else if((IR_READ_WHITE == IR_Sensors_Values[0]) && (IR_READ_BLACK == IR_Sensors_Values[1]) && (IR_READ_BLACK == IR_Sensors_Values[2]) && (IR_READ_WHITE == IR_Sensors_Values[3]) && (IR_READ_WHITE == IR_Sensors_Values[4]))
	{
		// WBBWW Sate
		Error = -1;
	}
	else if((IR_READ_WHITE == IR_Sensors_Values[0]) && (IR_READ_BLACK == IR_Sensors_Values[1]) && (IR_READ_WHITE== IR_Sensors_Values[2]) && (IR_READ_WHITE == IR_Sensors_Values[3]) && (IR_READ_WHITE == IR_Sensors_Values[4]))
	{
		// WBWWW Sate
		Error = -2;
	}
	else if((IR_READ_BLACK == IR_Sensors_Values[0]) && (IR_READ_BLACK == IR_Sensors_Values[1]) && (IR_READ_WHITE == IR_Sensors_Values[2]) && (IR_READ_WHITE == IR_Sensors_Values[3]) && (IR_READ_WHITE == IR_Sensors_Values[4]))
	{
		// BBWWW Sate
		Error = -3;
	}
	else if((IR_READ_BLACK == IR_Sensors_Values[0]) && (IR_READ_WHITE == IR_Sensors_Values[1]) && (IR_READ_WHITE == IR_Sensors_Values[2]) && (IR_READ_WHITE == IR_Sensors_Values[3]) && (IR_READ_WHITE == IR_Sensors_Values[4]))
	{
		// BWWWW Sate
		Error = -4;
	}
	else if((IR_READ_WHITE == IR_Sensors_Values[0]) && (IR_READ_WHITE == IR_Sensors_Values[1]) && (IR_READ_WHITE == IR_Sensors_Values[2]) && (IR_READ_WHITE == IR_Sensors_Values[3]) && (IR_READ_WHITE == IR_Sensors_Values[4]))
	{
		// WWWWW Sate
		Error = PreError;
	}
#endif

	/* To calculate the suitable speeds of two side to move in lane in correct way by PID controller algorithm  */
	Motor_Speed = Kp * Error + Kd * (Error - PreError) + Ki * (SumError);
	LeftMotorSpeed = Motor_Base_Speed + Motor_Speed;
	RightMotorSpeed = Motor_Base_Speed - Motor_Speed;

	/* These conditions to Limit the speed if it reached to higher than maximum PWM Signal */
	if(LeftMotorSpeed > MotorMaxSpeed)
	{
		LeftMotorSpeed = MotorMaxSpeed;
	}

	if(RightMotorSpeed > MotorMaxSpeed)
	{
		RightMotorSpeed = MotorMaxSpeed;
	}

	if(LeftMotorSpeed < (-MotorMaxSpeed))
	{
		LeftMotorSpeed = -MotorMaxSpeed;
	}

	if(RightMotorSpeed < -MotorMaxSpeed)
	{
		RightMotorSpeed = -MotorMaxSpeed;
	}

	/* move with certain speed */
	Car_Void_Go_Lane(LeftMotorSpeed, RightMotorSpeed);

	//HAL_Delay(20);

	/* assign Current Error as a previous Error to help us Calculate the differentiation of Error  */
	PreError = Error;
	/* Integrate our error */
	SumError += Error;


}
