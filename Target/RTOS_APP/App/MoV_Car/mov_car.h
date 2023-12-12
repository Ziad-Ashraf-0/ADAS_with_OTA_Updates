/*
 * mov_car.h
 *
 *  Created on: Dec 9, 2023
 *      Author: Ziad
 */

#ifndef MOV_CAR_MOV_CAR_H_
#define MOV_CAR_MOV_CAR_H_
#include "stm32f4xx_hal.h"

void Car_Void_GoForward(uint8_t PWM_Sig);

void Car_Void_GoBackward(uint8_t PWM_Sig);

void Car_Void_Stop(void);

void Car_Void_TurnRight(uint8_t PWM_Sig_right, uint8_t PWM_Sig_left);

void Car_Void_TurnLeft(uint8_t PWM_Sig_right, uint8_t PWM_Sig_left);

#endif /* MOV_CAR_MOV_CAR_H_ */
