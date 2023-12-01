
/*********************************************************************************************/
/*  Edited_by :-  Omar Khaled Ahmed                                                          */
/*  date      :-  20/11/2023                                                                 */
/*  Version   :-  Blind_Sport.h  - Version 1                                                 */
/*  Project   :-  Graduation Project (Group 7)                                               */
/*********************************************************************************************/


#ifndef   _BLIND_SPOT_H_
#define   _BLIND_SPOT_H_

#define NEAREST_UNSEEN_DISTANCE_OF_BLIND_SPOT_REGION            15     // This value is in cm and we can change it when we know our car size .
#define LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PORT  GPIOG
#define LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PORT   GPIOG
#define LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_RIGHT_PIN   GPIO_PIN_13  // This is the Value of the pin used to illuminate the Detection Led when obstacle exists in blind spot RIGHT side .
#define LED_INDICATOR_OF_BLINDSPOT_OBSTACLE_EXISTS_LEFT_PIN    GPIO_PIN_14  // This is the Value of the pin used to illuminate the Detection Led when obstacle exists in blind spot LEFT side  .


typedef enum
{
    OBSTABCLE_NOT_EXIST = 0,

    OBSTACLE_EXIST      = 1

}Obstacle_Status_Type;

typedef enum
{
    RIGHT_SIDE = 0 ,
    LEFT_SIDE  = 1,
	BOTH_SIDES = 2

}BlindSpot_Side_Type;


Obstacle_Status_Type BlindSpot_Enum_Check (BlindSpot_Side_Type side);



#endif
