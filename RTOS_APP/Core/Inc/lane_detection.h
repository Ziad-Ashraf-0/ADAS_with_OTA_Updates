/*
 * lane_detection.h
 *
 *  Created on: Dec 1, 2023
 *      Author: Ziad
 */

#ifndef INC_LANE_DETECTION_H_
#define INC_LANE_DETECTION_H_

#define LANE_BLACK_GROUND_WHITE_LINE     0
#define LANE_WHITE_GROUND_BLACK_LINE     1

#define LANE_ASSIST_SETUP              LANE_BLACK_GROUND_WHITE_LINE

void Lane_Runnable(void);

#endif /* INC_LANE_DETECTION_H_ */
