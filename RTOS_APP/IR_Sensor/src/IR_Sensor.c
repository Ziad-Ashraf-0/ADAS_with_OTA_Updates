/*
 * IR_Sensor.c
 *
 *  Created on: Nov 23, 2023
 *      Author: muhammed
 */

#include "IR_Sensor_Interface.h"


/**
 * @brief This function to read the color of IR sensor.
 *
 * This function return the zero or one based on the color reading of sensor.
 * it return the reading to this pointer (uint8_t *Color).
 *
 * @param IR_PORT      IR Pin PORT Example: GPIOG, GPIOE, ..etc..
 * @param IR_PIN_NUM   IR Pin number Example: GPIO_PIN_14, GPIO_PIN_13, ..etc.
 * @param Color        pointer to uint8_t it can be IR_READ_WHITE or IR_READ_BLACK
 * @return (void).
 *
 */
void IR_Void_ReadColor(GPIO_TypeDef* IR_PORT, uint16_t IR_PIN_NUM, uint8_t *Color)
{
	*Color = HAL_GPIO_ReadPin(IR_PORT, IR_PIN_NUM);
}

