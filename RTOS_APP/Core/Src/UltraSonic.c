#include "UltraSonic.h"

extern TIM_HandleTypeDef htim1;

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

// Callback function for handling timer input capture events
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) // if the interrupt source is channel1
			{
		if (Is_First_Captured_CH1 == 0) // if the first value is not captured
				{
			IC_Val1_CH1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read the first value
			Is_First_Captured_CH1 = 1;  // set the first captured as true
			// Now change the polarity to falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1,
					TIM_INPUTCHANNELPOLARITY_FALLING);
		}

		else if (Is_First_Captured_CH1 == 1) // if the first is already captured
				{
			Is_First_Captured_CH1 = 2;
			IC_Val2_CH1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read second value

			if (IC_Val2_CH1 > IC_Val1_CH1) {
				Difference_CH1 = IC_Val2_CH1 - IC_Val1_CH1;
			}

			else if (IC_Val1_CH1 > IC_Val2_CH1) {
				Difference_CH1 = (0xffff - IC_Val1_CH1) + IC_Val2_CH1;
			}

			Distance_CH1 = Difference_CH1 * .034 / 2;
			//Is_First_Captured = 0; // set it back to false

			// set polarity to rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1,
					TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC1);
		}
	} else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
		if (Is_First_Captured_CH2 == 0) // if the first value is not captured
				{
			IC_Val1_CH2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2); // read the first value
			Is_First_Captured_CH2 = 1;  // set the first captured as true
			// Now change the polarity to falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2,
					TIM_INPUTCHANNELPOLARITY_FALLING);
		}

		else if (Is_First_Captured_CH2 == 1) // if the first is already captured
				{
			Is_First_Captured_CH2 = 2;
			IC_Val2_CH2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2); // read second value

			if (IC_Val2_CH2 > IC_Val1_CH2) {
				Difference_CH2 = IC_Val2_CH2 - IC_Val1_CH2;
			}

			else if (IC_Val1_CH2 > IC_Val2_CH2) {
				Difference_CH2 = (0xffff - IC_Val1_CH2) + IC_Val2_CH2;
			}

			Distance_CH2 = Difference_CH2 * .034 / 2;
			//Is_First_Captured = 0; // set it back to false

			// set polarity to rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2,
					TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC2);

		}
	} else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) {
		if (Is_First_Captured_CH3 == 0) // if the first value is not captured
				{
			IC_Val1_CH3 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3); // read the first value
			Is_First_Captured_CH3 = 1;  // set the first captured as true
			// Now change the polarity to falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3,
					TIM_INPUTCHANNELPOLARITY_FALLING);
		}

		else if (Is_First_Captured_CH3 == 1) // if the first is already captured
				{
			Is_First_Captured_CH3 = 2;
			IC_Val2_CH3 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3); // read second value

			if (IC_Val2_CH3 > IC_Val1_CH3) {
				Difference_CH3 = IC_Val2_CH3 - IC_Val1_CH3;
			}

			else if (IC_Val1_CH3 > IC_Val2_CH3) {
				Difference_CH3 = (0xffff - IC_Val1_CH3) + IC_Val2_CH3;
			}

			Distance_CH3 = Difference_CH3 * .034 / 2;
			//Is_First_Captured = 0; // set it back to false

			// set polarity to rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3,
					TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC3);
		}
	}

}

static void UltraSonic_void_Init(Ultra_Sonic_Type Ultra_Sonic) {
	//This Function Just for Initiate the Trigger

	//The Trigger is High pusle , 10 ms delay  , then Low Pulse to the Trigger Pin in UltraSonic from our MC.

	switch (Ultra_Sonic) {
	case ULTRASONIC1:
		HAL_GPIO_WritePin(GPIOE, ULTRA_SONIC1_TRIG, GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOE, ULTRA_SONIC1_TRIG, GPIO_PIN_RESET);
		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
		break;

	case ULTRASONIC2:
		HAL_GPIO_WritePin(GPIOE, ULTRA_SONIC2_TRIG, GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOE, ULTRA_SONIC2_TRIG, GPIO_PIN_RESET);
		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC2);
		break;

	case ULTRASONIC3:
		HAL_GPIO_WritePin(GPIOE, ULTRA_SONIC3_TRIG, GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOE, ULTRA_SONIC3_TRIG, GPIO_PIN_RESET);
		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC3);
		break;

	case ULTRASONIC4:
		HAL_GPIO_WritePin(GPIOA, ULTRA_SONIC4_TRIG, GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOA, ULTRA_SONIC4_TRIG, GPIO_PIN_RESET);
		break;

	case ULTRASONIC1_2:
		HAL_GPIO_WritePin(GPIOE, ULTRA_SONIC1_TRIG, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, ULTRA_SONIC2_TRIG, GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOE, ULTRA_SONIC1_TRIG, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, ULTRA_SONIC2_TRIG, GPIO_PIN_RESET);
		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC2);
		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
		break;

	case TOTAL_ULTRA_SONIC:

		break;
	}

	// no need
	//__HAL_TIM_SET_COUNTER(&htim1, 0);  // reset the counter

}

Read_Status UltraSonic_ReadStatusENUM_GetRead(Ultra_Sonic_Type Ultra_Sonic,
		uint16_t *distance1, uint16_t *distance2) {

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

		if (Is_First_Captured_CH1 == 2) {
			*distance1 = Distance_CH1;
			status = READ_EXIST;
			Is_First_Captured_CH1 = 0; // set it back to false
		}

		break;

	case ULTRASONIC2:

		//This Function Just for Initiate the Trigger

		UltraSonic_void_Init(ULTRASONIC2);

		//This Function is to Count the Time Between Rising and Failling Edges in 1 Cycle using ICU.

		if (Is_First_Captured_CH2 == 2) {
			*distance1 = Distance_CH2;
			status = READ_EXIST;
			Is_First_Captured_CH2 = 0; // set it back to false
		}

		break;

	case ULTRASONIC3:

		//This Function Just for Initiate the Trigger

		UltraSonic_void_Init(ULTRASONIC3);

		//This Function is to Count the Time Between Rising and Failling Edges in 1 Cycle using ICU.

		if (Is_First_Captured_CH3 == 2) {
			*distance1 = Distance_CH3;
			status = READ_EXIST;
			Is_First_Captured_CH3 = 0; // set it back to false
		}

		break;

	case ULTRASONIC4:

		//This Function Just for Initiate the Trigger

		UltraSonic_void_Init(ULTRASONIC4);

		//This Function is to Count the Time Between Rising and Failling Edges in 1 Cycle using ICU.

		if (Is_First_Captured_CH1 == 1) {
			*distance1 = Distance_CH1;
			status = READ_EXIST;
		}
		break;

	case ULTRASONIC1_2:

		//This Function Just for Initiate the Trigger

		UltraSonic_void_Init(ULTRASONIC1_2);

		//This Function is to Count the Time Between Rising and Failling Edges in 1 Cycle using ICU.

		if (Is_First_Captured_CH1 == 2 && Is_First_Captured_CH2 == 2) {
			*distance1 = Distance_CH1;
			*distance2 = Distance_CH2;
			status = READ_EXIST;
			Is_First_Captured_CH1 = 0;
			Is_First_Captured_CH2 = 0;
		}
		break;

	case TOTAL_ULTRA_SONIC:

		break;
	}

	//Time Between Taking 2 Readings Wra Ba3d.

	//HAL_Delay(TIME_BETWEEN_READINGS_INMILI);

	return status;

}