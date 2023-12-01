#ifndef _MOTOR_INTERFACE_H
#define _MOTOR_INTERFACE_H

/* ---------------------------- Includes ------------------------ */
#include "stm32f4xx_hal.h"
#include "IR_Sensor_Interface.h"

/* ---------------------------- Macros Objects ------------------ */

/* ---------------------------- Macros Functions ---------------- */

/* ---------------------------- User Data Types ----------------- */
typedef enum {
	MOTOR_CW_DIRECTION,
	MOTOR_CCW_DIRECTION
}Direction_t;


/* ---------------------------- APIs ---------------------------- */

/**
 * @brief This function to Move Motor with specific direction.
 *
 * on this functions we have two Pins input to this function
 * to move motor on two directions CW and CCW and we can input
 * These directions by using this type (Direction_t)
 *
 * @param Motor_P1_Port Motor Pin1 PORT Example: GPIOG, GPIOE, ..etc.
 * @param Motor_P1_Pin  Motor Pin1 number Example: GPIO_PIN_14, GPIO_PIN_13, ..etc.
 * @param Motor_P2_Port Motor Pin2 PORT Example: GPIOG, GPIOE, ..etc
 * @param Motor_P2_Pin  Motor Pin2 number Example: GPIO_PIN_14, GPIO_PIN_13, ..etc.
 * @param PWM_Signal    PWM signal takes from 0 to 100
 * @param PWM_Source    PWM timer source select
 * @param Direction     Motor Direction it can be MOTOR_CW_DIRECTION or MOTOR_CCW_DIRECTION @ref Direction_t
 * @return return void.
 *
 */
void Motor_Void_Move(GPIO_TypeDef* Motor_P1_Port, uint16_t Motor_P1_Pin, GPIO_TypeDef* Motor_P2_Port, uint16_t Motor_P2_Pin, uint8_t PWM_Signal, TIM_HandleTypeDef PWM_Source, Direction_t Direction);

/**
 * @brief This function to Stop Motor.
 *
 * on this functions we have two Pins input to this function
 * to move motor on two directions CW and CCW and we can input
 * These directions by using this type (Direction_t)
 *
 * @param Motor_P1_Port Motor Pin1 PORT Example: GPIOG, GPIOE, ..etc.
 * @param Motor_P1_Pin  Motor Pin1 number Example: GPIO_PIN_14, GPIO_PIN_13, ..etc.
 * @param Motor_P2_Port Motor Pin2 PORT Example: GPIOG, GPIOE, ..etc
 * @param Motor_P2_Pin  Motor Pin2 number Example: GPIO_PIN_14, GPIO_PIN_13, ..etc.
 * @return return void.
 *
 */
void Motor_Void_Stop(GPIO_TypeDef* Motor_P1_Port, uint16_t Motor_P1_Pin, GPIO_TypeDef* Motor_P2_Port, uint16_t Motor_P2_Pin);


#endif
