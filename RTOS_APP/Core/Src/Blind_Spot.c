
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
   Obstacle_Status_Type Obstacle_Status_Var = OBSTABCLE_NOT_EXIST ; // Enum obj  to check obstacle exists in it.

   uint16_t Distance_Measured1 ;     // Local Variable to Get Distance using ULTRASONIC in it .
   uint16_t Distance_Measured2 ;     // Local Variable to Get Distance using ULTRASONIC in it .

    switch (side)  // Switching if i will work on Right or Left side this time or this check.
    {

    case RIGHT_SIDE :

    	if( UltraSonic_ReadStatusENUM_GetRead( ULTRASONIC1 , & Distance_Measured1, &Distance_Measured2) == READ_EXIST ) // Low el Ultra Sonic ba3at 2eraya s3etha htcheck 3leha , L3 stands for choosing Ultrasonic 3 .
        {
        	//printf("Distance : %d \r\n",Distance_Measured);
           if ( Distance_Measured1 <= NEAREST_UNSEEN_DISTANCE_OF_BLIND_SPOT_REGION )  // check distance
            {
        	   HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PIN , GPIO_PIN_SET ); // Turn on Indication Right LED.
               Obstacle_Status_Var = OBSTACLE_EXIST ; // keda fe obstacle right side , fa b3dl el obj eli h3mlo return.
            }
            else
            {
            	HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PIN , GPIO_PIN_RESET );  // Turn off Indication Right LED.
            }
        }
        else
        {

        	//HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PIN , GPIO_PIN_RESET ) ;  // Turn off Indication Right LED.
            // in this case , no read exist , therefore there is no obstacle in this way , neither in blind spot region or not.
        }

        break;

    case LEFT_SIDE :

    	if( UltraSonic_ReadStatusENUM_GetRead( ULTRASONIC2 , & Distance_Measured1, &Distance_Measured2) == READ_EXIST ) // Low el Ultra Sonic ba3at 2eraya s3etha htcheck 3leha , L4 stands for choosing Ultrasonic 4 .
        {
            if ( Distance_Measured1 <= NEAREST_UNSEEN_DISTANCE_OF_BLIND_SPOT_REGION )
            {
            	HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PIN , GPIO_PIN_SET ); // Turn on Indication LEFT LED.
                Obstacle_Status_Var = OBSTACLE_EXIST ; // keda fe obstacle right side , fa b3dl el obj eli h3mlo return.
            }
            else
            {
            	HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PIN , GPIO_PIN_RESET ); // Turn off Indication LEFT LED.
            }
        }

          else

        {
        	// HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PIN , GPIO_PIN_RESET ) ; // Turn off Indication LEFT LED.

            // in this case , no read exist , therefore there is no obstacle in this way , neither in blind spot region or not.
        }

        break;

    case BOTH_SIDES:

         if( UltraSonic_ReadStatusENUM_GetRead( ULTRASONIC1_2 , & Distance_Measured1, &Distance_Measured2) == READ_EXIST ) // Low el Ultra Sonic ba3at 2eraya s3etha htcheck 3leha , L4 stands for choosing Ultrasonic 4 .
        {
            if ( Distance_Measured1 <= NEAREST_UNSEEN_DISTANCE_OF_BLIND_SPOT_REGION )
            {
            	HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PIN , GPIO_PIN_SET ); // Turn on Indication LEFT LED.
                Obstacle_Status_Var = OBSTACLE_EXIST ; // keda fe obstacle right side , fa b3dl el obj eli h3mlo return.
            }
            else
            {
            	HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PIN , GPIO_PIN_RESET ); // Turn off Indication LEFT LED.
            }

            if ( Distance_Measured2 <= NEAREST_UNSEEN_DISTANCE_OF_BLIND_SPOT_REGION )
            {
            	HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PIN , GPIO_PIN_SET ); // Turn on Indication LEFT LED.
                Obstacle_Status_Var = OBSTACLE_EXIST ; // keda fe obstacle right side , fa b3dl el obj eli h3mlo return.
            }
            else
            {
            	HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PIN , GPIO_PIN_RESET ); // Turn off Indication LEFT LED.
            }
        }

          else

        {
        	//  HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PIN , GPIO_PIN_RESET ) ; // Turn off Indication LEFT LED.
        	//  HAL_GPIO_WritePin(LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PORT, LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PIN , GPIO_PIN_RESET ) ; // Turn off Indication LEFT LED.

            // in this case , no read exist , therefore there is no obstacle in this way , neither in blind spot region or not.
        }

        break;

    default :

    	break;


    }

    return Obstacle_Status_Var ;
}
