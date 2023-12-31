
/*********************************************************************************************/
/*  Edited_by :-  Omar Khaled Ahmed                                                          */
/*  date      :-  20/11/2023                                                                 */
/*  Version   :-  Blind_Sport.c  - Version 1                                                 */
/*  Project   :-  Graduation Project (Group 7)                                               */
/*********************************************************************************************/

#include "UltraSonic.h"
#include "Blind_Spot.h"


Obstacle_Status_Type BlindSpot_Enum_Check ( BlindSpot_Side_Type side )
{
	Obstacle_Status_Type Obstacle_Status_Var = OBSTABCLE_NOT_EXIST; // Enum obj to check if an obstacle exists.

	uint16_t Distances[4] = {0}; // Array to store distances from the ultrasonic sensors.

	switch (side) // Switching if I will work on the Right or Left side this time or this check.
	{
	case RIGHT_SIDE:

	    while (UltraSonic_ReadStatusENUM_GetRead(ULTRASONIC1, Distances, 1) != READ_EXIST)  // Read from Ultrasonic1
	    {
	        // Continue looping until a valid reading is obtained.
	    }

	    if (Distances[0] <= NEAREST_UNSEEN_DISTANCE_OF_BLIND_SPOT_REGION)
	    {
	        HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PIN, GPIO_PIN_SET); // Turn on Indication Right LED.
	        Obstacle_Status_Var = OBSTACLE_EXIST;                                                           // There is an obstacle on the right side.
	    }
	    else
	    {
	        HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PIN, GPIO_PIN_RESET); // Turn off Indication Right LED.
	    }

	    break;

	case LEFT_SIDE:

	    while (UltraSonic_ReadStatusENUM_GetRead(ULTRASONIC2, Distances, 1) != READ_EXIST)  // Read from Ultrasonic2
	    {
	        // Continue looping until a valid reading is obtained.
	    }

	    if (Distances[0] <= NEAREST_UNSEEN_DISTANCE_OF_BLIND_SPOT_REGION)
	    {
	        HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PIN, GPIO_PIN_SET); // Turn on Indication Left LED.
	        Obstacle_Status_Var = OBSTACLE_EXIST;                                                          // There is an obstacle on the left side.
	    }
	    else
	    {
	        HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PIN, GPIO_PIN_RESET); // Turn off Indication Left LED.
	    }

	    break;

	case BOTH_SIDES:

	    while (UltraSonic_ReadStatusENUM_GetRead(ULTRASONIC1_4, Distances, 2) != READ_EXIST)  // Read from Ultrasonic1 and Ultrasonic2
	    {
	        // Continue looping until a valid reading is obtained.
	    }

	    if (Distances[0] <= NEAREST_UNSEEN_DISTANCE_OF_BLIND_SPOT_REGION)
	    {
	        HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PIN, GPIO_PIN_SET); // Turn on Indication Left LED.
	        Obstacle_Status_Var = OBSTACLE_EXIST;                                                          // There is an obstacle on the left side.
	    }
	    else
	    {
	        HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PIN, GPIO_PIN_RESET); // Turn off Indication Left LED.
	    }

	    if (Distances[1] <= NEAREST_UNSEEN_DISTANCE_OF_BLIND_SPOT_REGION)
	    {
	        HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PIN, GPIO_PIN_SET); // Turn on Indication Right LED.
	        Obstacle_Status_Var = OBSTACLE_EXIST;                                                           // There is an obstacle on the right side.
	    }
	    else
	    {
	        HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PIN, GPIO_PIN_RESET); // Turn off Indication Right LED.
	    }

	    break;

	default:
	    break;
	}

	return Obstacle_Status_Var;

}
