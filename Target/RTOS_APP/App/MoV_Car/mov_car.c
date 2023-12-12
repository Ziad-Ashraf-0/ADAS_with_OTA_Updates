/*
 * mov_car.c
 *
 *  Created on: Dec 9, 2023
 *      Author: Ziad
 */
#include "Motor_Interfce.h"
#include "mov_car.h"


extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;


/**
 * @brief To make Car Move Forward
 *
 * This Function give two sides same directions and same speeds
 *
 * @param PWM_Sig PWM signal for both sides
 * @return return void.
 * */
void Car_Void_GoForward(uint8_t PWM_Sig) {
	Motor_Void_Move(GPIOG, GPIO_PIN_10, GPIOG, GPIO_PIN_11, PWM_Sig, htim3,
			MOTOR_CCW_DIRECTION); // right motors
	Motor_Void_Move(GPIOG, GPIO_PIN_8, GPIOG, GPIO_PIN_9, PWM_Sig, htim4,
			MOTOR_CCW_DIRECTION);  // left motors
}

/**
 * @brief To make Car Move Backward
 *
 * This Function give two sides same directions and same speeds
 *
 * @param PWM_Sig PWM signal for both sides
 * @return return void.
 * */
void Car_Void_GoBackward(uint8_t PWM_Sig) {
	Motor_Void_Move(GPIOG, GPIO_PIN_10, GPIOG, GPIO_PIN_11, PWM_Sig, htim3,
			MOTOR_CW_DIRECTION); // right motors
	Motor_Void_Move(GPIOG, GPIO_PIN_8, GPIOG, GPIO_PIN_9, PWM_Sig, htim4,
			MOTOR_CW_DIRECTION);   // left motors
}

/**
 * @brief To Stop Car
 *
 * This Function give two sides same Signal To Stop
 *
 * @return return void.
 * */
void Car_Void_Stop(void) {
	Motor_Void_Stop(GPIOG, GPIO_PIN_10, GPIOG, GPIO_PIN_11); // right motors
	Motor_Void_Stop(GPIOG, GPIO_PIN_8, GPIOG, GPIO_PIN_9);   // left motors
}

/**
 * @brief To make Car Turn Right
 *
 * This Function give two sides Same directions but different speeds
 *
 * @param PWM_Sig_right PWM signal for Right side
 * @param PWM_Sig_left  PWM signal for Left side
 * @return return void.
 * */
void Car_Void_TurnRight(uint8_t PWM_Sig_right, uint8_t PWM_Sig_left) {
	if (PWM_Sig_left > PWM_Sig_right) {
		Motor_Void_Move(GPIOG, GPIO_PIN_10, GPIOG, GPIO_PIN_11, PWM_Sig_right,
				htim3, MOTOR_CCW_DIRECTION); 	// right motors
		Motor_Void_Move(GPIOG, GPIO_PIN_8, GPIOG, GPIO_PIN_9, PWM_Sig_left,
				htim4, MOTOR_CCW_DIRECTION);    // left motors
	} else {/* Nothing */
	}

}

/**
 * @brief To make Car Turn Left
 *
 * This Function give two sides Same directions but different speeds
 *
 * @param PWM_Sig_right PWM signal for Right side
 * @param PWM_Sig_left  PWM signal for Left side
 * @return return void.
 * */
void Car_Void_TurnLeft(uint8_t PWM_Sig_right, uint8_t PWM_Sig_left) {
	if (1) {
		Motor_Void_Move(GPIOG, GPIO_PIN_10, GPIOG, GPIO_PIN_11, PWM_Sig_right,
				htim3, MOTOR_CCW_DIRECTION); 	// right motors
		Motor_Void_Move(GPIOG, GPIO_PIN_8, GPIOG, GPIO_PIN_9, PWM_Sig_left,
				htim4, MOTOR_CW_DIRECTION);    // left motors
	} else {/* Nothing */
	}
}
