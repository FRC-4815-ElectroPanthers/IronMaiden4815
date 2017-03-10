/*
 * PixyFunctions.h
 *
 *  Created on: Mar 10, 2017
 *      Author: Phia
 */

#ifndef SRC_PIXYCAMERA_PIXYFUNCTIONS_H_
#define SRC_PIXYCAMERA_PIXYFUNCTIONS_H_

#include "WPIlib.h"
#include "PixyCamera/PixyI2C.h"
#include <cmath>

#define PIXY_CENTER_POS PIXY_MAX_X/2
#define DESIRED_POS PIXY_CENTER_POS

int getLiftPos(PixyI2C*);
double getAlignmentAngle(PixyI2C*);

#endif /* SRC_PIXYCAMERA_PIXYFUNCTIONS_H_ */
