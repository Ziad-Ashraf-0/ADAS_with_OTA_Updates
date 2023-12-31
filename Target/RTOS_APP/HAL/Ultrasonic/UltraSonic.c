#include "UltraSonic.h"
#include "DWT_Delay.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim9;

// Variables for Ultrasonic sensor 1
uint32_t IC_Val1_CH1 = 0;
uint32_t IC_Val2_CH1 = 0;
uint32_t Difference_CH1 = 0;
uint8_t Is_First_Captured_CH1 = 0; // Flag to check if the first value is captured
uint8_t Distance_CH1 = 0;

// Variables for Ultrasonic sensor 2
uint32_t IC_Val1_CH2 = 0;
uint32_t IC_Val2_CH2 = 0;
uint32_t Difference_CH2 = 0;
uint8_t Is_First_Captured_CH2 = 0;
uint8_t Distance_CH2 = 0;

// Variables for Ultrasonic sensor 3
uint32_t IC_Val1_CH3 = 0;
uint32_t IC_Val2_CH3 = 0;
uint32_t Difference_CH3 = 0;
uint8_t Is_First_Captured_CH3 = 0;
uint8_t Distance_CH3 = 0;

// Variables for Ultrasonic sensor 4
uint32_t IC_Val1_CH4 = 0;
uint32_t IC_Val2_CH4 = 0;
uint32_t Difference_CH4 = 0;
uint8_t Is_First_Captured_CH4 = 0;
uint8_t Distance_CH4 = 0;

static void UltraSonic_void_Init(Ultra_Sonic_Type Ultra_Sonic) {
	//This Function Just for Initiate the Trigger

	//The Trigger is High pusle , 10 ms delay  , then Low Pulse to the Trigger Pin in UltraSonic from our MC.

	switch (Ultra_Sonic) {
	case ULTRASONIC1:

		HAL_GPIO_WritePin(ULTRA_SONIC1_TRIG_PORT, ULTRA_SONIC1_TRIG,
				GPIO_PIN_SET);

		DWT_Delay_us(2);

		HAL_GPIO_WritePin(ULTRA_SONIC1_TRIG_PORT, ULTRA_SONIC1_TRIG,
				GPIO_PIN_RESET);

		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
		break;

	case ULTRASONIC2:

		HAL_GPIO_WritePin(ULTRA_SONIC2_TRIG_PORT, ULTRA_SONIC2_TRIG,
				GPIO_PIN_SET);

		DWT_Delay_us(15);

		HAL_GPIO_WritePin(ULTRA_SONIC2_TRIG_PORT, ULTRA_SONIC2_TRIG,
				GPIO_PIN_RESET);

		__HAL_TIM_ENABLE_IT(&htim9, TIM_IT_CC2);
		break;

	case ULTRASONIC3:
		HAL_GPIO_WritePin(ULTRA_SONIC3_TRIG_PORT, ULTRA_SONIC3_TRIG,
				GPIO_PIN_SET);

		DWT_Delay_us(2);

		HAL_GPIO_WritePin(ULTRA_SONIC3_TRIG_PORT, ULTRA_SONIC3_TRIG,
				GPIO_PIN_RESET);

		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC3);
		break;

	case ULTRASONIC4:
		HAL_GPIO_WritePin(ULTRA_SONIC4_TRIG_PORT, ULTRA_SONIC4_TRIG,
				GPIO_PIN_SET);

		DWT_Delay_us(2);

		HAL_GPIO_WritePin(ULTRA_SONIC4_TRIG_PORT, ULTRA_SONIC4_TRIG,
				GPIO_PIN_RESET);

		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC4);
		break;

	case ULTRASONIC1_4:
		HAL_GPIO_WritePin(ULTRA_SONIC1_TRIG_PORT, ULTRA_SONIC1_TRIG,
				GPIO_PIN_SET);

		HAL_GPIO_WritePin(ULTRA_SONIC4_TRIG_PORT, ULTRA_SONIC4_TRIG,
				GPIO_PIN_SET);

		DWT_Delay_us(15);

		HAL_GPIO_WritePin(ULTRA_SONIC1_TRIG_PORT, ULTRA_SONIC1_TRIG,
				GPIO_PIN_RESET);

		HAL_GPIO_WritePin(ULTRA_SONIC4_TRIG_PORT, ULTRA_SONIC4_TRIG,
				GPIO_PIN_RESET);

		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC4);
		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
		break;

	case TOTAL_ULTRA_SONIC:

		HAL_GPIO_WritePin(ULTRA_SONIC1_TRIG_PORT, ULTRA_SONIC1_TRIG,
				GPIO_PIN_SET);
		HAL_GPIO_WritePin(ULTRA_SONIC2_TRIG_PORT, ULTRA_SONIC2_TRIG,
				GPIO_PIN_SET);
		HAL_GPIO_WritePin(ULTRA_SONIC3_TRIG_PORT, ULTRA_SONIC3_TRIG,
				GPIO_PIN_SET);
		HAL_GPIO_WritePin(ULTRA_SONIC4_TRIG_PORT, ULTRA_SONIC4_TRIG,
				GPIO_PIN_SET);

		DWT_Delay_us(2);

		HAL_GPIO_WritePin(ULTRA_SONIC1_TRIG_PORT, ULTRA_SONIC1_TRIG,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ULTRA_SONIC2_TRIG_PORT, ULTRA_SONIC2_TRIG,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ULTRA_SONIC3_TRIG_PORT, ULTRA_SONIC3_TRIG,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(ULTRA_SONIC4_TRIG_PORT, ULTRA_SONIC4_TRIG,
				GPIO_PIN_RESET);

		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
		__HAL_TIM_ENABLE_IT(&htim9, TIM_IT_CC2);
		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC3);
		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC4);
		break;
	}

	// no need
	//__HAL_TIM_SET_COUNTER(&htim1, 0);  // reset the counter

}

Read_Status UltraSonic_ReadStatusENUM_GetRead(Ultra_Sonic_Type Ultra_Sonic,
		uint16_t distances[], size_t numDistances) {

	//Creating ENUM Obj 3lshan nshuf fe READ gat wla la2.
	Read_Status status = NO_READ;

	//Creating u16 Variable 3lshan n5zn feh el time eli rg3 beh el ecko bta3 el ultrasonic.
	//To Calculate the Distance .
	//u32 time_calculated ;

	//3aml Enum 3lshan low 3andy aktr mn UltraSonic Wa7da we a22dr aswitch ana hshtghl 3al eh ka INPUT lel Function.
	//Ultra_Sonic_Type Enum in H file .

	switch (Ultra_Sonic) {
	case ULTRASONIC1:

		//This Function Just for Initiate the Trigger

		UltraSonic_void_Init(ULTRASONIC1);

		//This Function is to Count the Time Between Rising and Failling Edges in 1 Cycle using ICU.

		while (Is_First_Captured_CH1 != 2) {
		}
		;
		distances[0] = Distance_CH1;
		status = READ_EXIST;
		Is_First_Captured_CH1 = 0; // set it back to false

		break;

	case ULTRASONIC2:

		//This Function Just for Initiate the Trigger

		UltraSonic_void_Init(ULTRASONIC2);

		//This Function is to Count the Time Between Rising and Failling Edges in 1 Cycle using ICU.

		if (Is_First_Captured_CH2 == 2) {
			distances[0] = Distance_CH2;
			status = READ_EXIST;
			Is_First_Captured_CH2 = 0; // set it back to false
		}

		break;

	case ULTRASONIC3:

		//This Function Just for Initiate the Trigger

		UltraSonic_void_Init(ULTRASONIC3);

		//This Function is to Count the Time Between Rising and Failling Edges in 1 Cycle using ICU.

		if (Is_First_Captured_CH3 == 2) {

			distances[0] = Distance_CH3;
			status = READ_EXIST;
			Is_First_Captured_CH3 = 0; // set it back to false
		}

		break;

	case ULTRASONIC4:

		//This Function Just for Initiate the Trigger

		UltraSonic_void_Init(ULTRASONIC4);

		//This Function is to Count the Time Between Rising and Failling Edges in 1 Cycle using ICU.

		if (Is_First_Captured_CH4 == 2) {
			distances[0] = Distance_CH4;
			status = READ_EXIST;
			Is_First_Captured_CH4 = 0;
		}

		break;

	case ULTRASONIC1_4:

		//This Function Just for Initiate the Trigger

		UltraSonic_void_Init(ULTRASONIC1_4);

		//This Function is to Count the Time Between Rising and Failling Edges in 1 Cycle using ICU.

		if (Is_First_Captured_CH1 == 2 && Is_First_Captured_CH4 == 2) {

			distances[0] = Distance_CH1;
			distances[1] = Distance_CH4;
			status = READ_EXIST;
			Is_First_Captured_CH1 = 0;
			Is_First_Captured_CH4 = 0;
		}
		break;

	case TOTAL_ULTRA_SONIC:

		//This Function Just for Initiate the Trigger

		UltraSonic_void_Init(TOTAL_ULTRA_SONIC);

		while (Is_First_Captured_CH1 != 2 && Is_First_Captured_CH2 != 2
				&& Is_First_Captured_CH3 != 2 && Is_First_Captured_CH4 != 2) {
		}
		distances[0] = Distance_CH1;
		distances[1] = Distance_CH2;
		distances[2] = Distance_CH3;
		distances[3] = Distance_CH4;
		status = READ_EXIST;
		Is_First_Captured_CH1 = 0;
		Is_First_Captured_CH2 = 0;
		Is_First_Captured_CH3 = 0;
		Is_First_Captured_CH4 = 0;

		break;
	}

	// If the array size is greater than 1 set the rest to zero.
	if (numDistances > 1) {
		for (size_t i = numDistances; i < 4; ++i) {
			distances[i] = 0;  // Set other values to zero.
		}
	}

	//Time Between Taking 2 Readings Wra Ba3d.

	HAL_Delay(TIME_BETWEEN_READINGS_INMILI);

	return status;

}

// Callback function for handling timer input capture events
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {

	switch (htim->Channel) {

	case HAL_TIM_ACTIVE_CHANNEL_1:
		switch (Is_First_Captured_CH1) {
		case 0:
			IC_Val1_CH1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			Is_First_Captured_CH1 = 1;
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1,
					TIM_INPUTCHANNELPOLARITY_FALLING);
			break;

		case 1:
			Is_First_Captured_CH1 = 2;
			IC_Val2_CH1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

			if (IC_Val2_CH1 > IC_Val1_CH1) {
				Difference_CH1 = IC_Val2_CH1 - IC_Val1_CH1;
			} else if (IC_Val1_CH1 > IC_Val2_CH1) {
				Difference_CH1 = (0xffff - IC_Val1_CH1) + IC_Val2_CH1;
			}

			Distance_CH1 = Difference_CH1 * 0.034 / 2;
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1,
					TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC1);
			break;
		}
		break;

	case HAL_TIM_ACTIVE_CHANNEL_2:
		switch (Is_First_Captured_CH2) {
		case 0:
			IC_Val1_CH2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			Is_First_Captured_CH2 = 1;
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2,
					TIM_INPUTCHANNELPOLARITY_FALLING);
			break;

		case 1:
			Is_First_Captured_CH2 = 2;
			IC_Val2_CH2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);

			if (IC_Val2_CH2 > IC_Val1_CH2) {
				Difference_CH2 = IC_Val2_CH2 - IC_Val1_CH2;
			} else if (IC_Val1_CH2 > IC_Val2_CH2) {
				Difference_CH2 = (0xffff - IC_Val1_CH2) + IC_Val2_CH2;
			}

			Distance_CH2 = Difference_CH2 * 0.034 / 2;
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2,
					TIM_INPUTCHANNELPOLARITY_RISING);
			//__HAL_TIM_DISABLE_IT(&htim9, TIM_IT_CC2);
			break;
		}
		break;

	case HAL_TIM_ACTIVE_CHANNEL_3:
		switch (Is_First_Captured_CH3) {
		case 0:
			IC_Val1_CH3 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
			Is_First_Captured_CH3 = 1;
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3,
					TIM_INPUTCHANNELPOLARITY_FALLING);
			break;

		case 1:
			Is_First_Captured_CH3 = 2;
			IC_Val2_CH3 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);

			if (IC_Val2_CH3 > IC_Val1_CH3) {
				Difference_CH3 = IC_Val2_CH3 - IC_Val1_CH3;
			} else if (IC_Val1_CH3 > IC_Val2_CH3) {
				Difference_CH3 = (0xffff - IC_Val1_CH3) + IC_Val2_CH3;
			}

			Distance_CH3 = Difference_CH3 * 0.034 / 2;
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3,
					TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC3);
			break;
		}
		break;

	case HAL_TIM_ACTIVE_CHANNEL_4:
		switch (Is_First_Captured_CH4) {
		case 0:
			IC_Val1_CH4 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
			Is_First_Captured_CH4 = 1;
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_4,
					TIM_INPUTCHANNELPOLARITY_FALLING);
			break;

		case 1:
			Is_First_Captured_CH4 = 2;
			IC_Val2_CH4 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);

			if (IC_Val2_CH4 > IC_Val1_CH4) {
				Difference_CH4 = IC_Val2_CH4 - IC_Val1_CH4;
			} else if (IC_Val1_CH4 > IC_Val2_CH4) {
				Difference_CH4 = (0xffff - IC_Val1_CH4) + IC_Val2_CH4;
			}

			Distance_CH4 = Difference_CH4 * 0.034 / 2;
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_4,
					TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC4);
			break;
		}
		break;

	default:
		break;
	}

}
