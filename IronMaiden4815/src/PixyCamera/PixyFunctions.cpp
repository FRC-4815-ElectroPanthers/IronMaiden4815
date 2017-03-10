#include "PixyFunctions.h"

int getLiftPos(PixyI2C *pixy){
	int pos = 0,
		blocks;

	blocks = pixy->GetBlocks(2);

	if(blocks == 2){
		pos = (pixy->blocks[0].x + pixy->blocks[1].x)/2;
	}else{
		pos = -1;
	}

	return pos;
}

double getAlignmentAngle(PixyI2C *pixy){
	double angle = 0;
	int liftPos = getLiftPos(pixy);

	if(liftPos != -1){
		double angleA = -atan(2*liftPos*tan(PIXY_FOV)/PIXY_CENTER_POS) * 180/M_PI;
		double angleB = -atan(2*DESIRED_POS*tan(PIXY_FOV)/PIXY_CENTER_POS) * 180/M_PI;
		angle = angleA + angleB;
	}else{
		std::cout << "Cannot Find Peg! Tape not Found!" << std::endl;
	}

	return angle;
}
