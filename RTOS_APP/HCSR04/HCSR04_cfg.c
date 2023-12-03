/*
 * HCSR04_cfg.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Ziad
 */

#include "HCSR04.h"

const HCSR04_CfgType HCSR04_CfgParam[HCSR04_UNITS] = {
// HC-SR04 Sensor Unit 1 Configurations
		{
		GPIOE,
		GPIO_PIN_8,
		TIM1,
		TIM_CHANNEL_1, 1 },
		// HC-SR04 Sensor Unit 2 Configurations
		{
		GPIOE,
		GPIO_PIN_10,
		TIM1,
		TIM_CHANNEL_2, 1 },
		// HC-SR04 Sensor Unit 3 Configurations
		{
		GPIOE,
		GPIO_PIN_12,
		TIM1,
		TIM_CHANNEL_3, 1 },
		// HC-SR04 Sensor Unit 4 Configurations
		{
		GPIOE,
		GPIO_PIN_15,
		TIM1,
		TIM_CHANNEL_4, 1 } };
