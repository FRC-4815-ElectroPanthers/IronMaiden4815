/*
 * PixyI2C.cpp
 *
 *  Created on: Feb 14, 2018
 *      Author: 4815
 */
#include "PixyI2C.h"
#include "Timer.h"

PixyI2C::PixyI2C(uint8_t address, I2C::Port port): Wire(address, port){
	skipStart = false;
	blockType = NORMAL_BLOCK;
	blockCount = 0;
	blockArraySize = PIXY_INITIAL_ARRAYSIZE;
	blocks = (Block *)malloc(sizeof(Block)*blockArraySize);
}

PixyI2C::~PixyI2C(){
	free(blocks);
}

uint16_t PixyI2C::getWord(){
	uint8_t c[2];
	Wire.ReadOnly(2, c);
	uint16_t w = (c[1] << 8) + c[0];

	return w;
}

uint8_t PixyI2C::getByte(){
	uint8_t *c;
	Wire.ReadOnly(1, c);

	return *c;
}

int8_t PixyI2C::send(uint8_t *data, uint8_t len){
	Wire.WriteBulk(data, len);

	return len;
}

bool PixyI2C::GetStart(){
	uint16_t w, lastw;

	lastw = 0xffff;

	while(true){
		w = getWord();

		if (w==0 && lastw==0){
			Timer* delay = new Timer();
			delay->Start();

			while (!delay->HasPeriodPassed(0.00005)) {
				// Wait 50 microseconds
			}

			return false;

		}else if (w==PIXY_START_WORD && lastw==PIXY_START_WORD){
			blockType = NORMAL_BLOCK;
			return true;

		}else if (w==PIXY_START_WORD_CC && lastw==PIXY_START_WORD){
			blockType = CC_BLOCK;
			return true;

		}else if (w==PIXY_START_WORDX){
			printf("reorder");
			getByte(); // resync
		}

		lastw = w;
	}

}

void PixyI2C::Resize(){
	blockArraySize += PIXY_INITIAL_ARRAYSIZE;
	blocks = (Block *)realloc(blocks, sizeof(Block)*blockArraySize);
}

uint16_t PixyI2C::GetBlocks(uint16_t maxBlocks){
	uint8_t i;
	uint16_t w, checksum, sum;
	Block *block;

	if (!skipStart){
		if (GetStart()==false)
			return 0;
	}else{
		skipStart = false;
	}

	for(blockCount=0; blockCount<maxBlocks && blockCount<PIXY_MAXIMUM_ARRAYSIZE;){

		checksum = getWord();
		if (checksum==PIXY_START_WORD){ // we've reached the beginning of the next frame
			skipStart = true;
			blockType = NORMAL_BLOCK;
			//Serial.println("skip");
			return blockCount;
		}else if (checksum==PIXY_START_WORD_CC){
			skipStart = true;
			blockType = CC_BLOCK;
			return blockCount;
		}else if (checksum==0){
			return blockCount;
		}

		if (blockCount>blockArraySize){
			Resize();
		}

		block = blocks + blockCount;

		for (i=0, sum=0; i<sizeof(Block)/sizeof(uint16_t); i++){
			if (blockType==NORMAL_BLOCK && i>=5){ //skip
				block->angle = 0;
				break;
			}

			w = getWord();
			sum += w;
			*((uint16_t *)block + i) = w;
		}

		if (checksum==sum){
			blockCount++;
		}else{
			printf("cs error");
		}

		w = getWord();
		if (w==PIXY_START_WORD){
			blockType = NORMAL_BLOCK;
		}else if (w==PIXY_START_WORD_CC){
			blockType = CC_BLOCK;
		}else{
			return blockCount;
		}
	}
}

int8_t PixyI2C::SetServos(uint16_t s0, uint16_t s1){
	uint8_t outBuf[6];

	outBuf[0] = 0x00;
	outBuf[1] = 0xff;
	*(uint16_t *)(outBuf + 2) = s0;
	*(uint16_t *)(outBuf + 4) = s1;

	return send(outBuf, 6);
}

int8_t PixyI2C::SetBrightness(uint8_t brightness){
	uint8_t outBuf[3];

	outBuf[0] = 0x00;
	outBuf[1] = 0xfe;
	outBuf[2] = brightness;

	return send(outBuf, 3);
}

int8_t PixyI2C::SetLED(uint8_t r, uint8_t g, uint8_t b){
	uint8_t outBuf[5];

	outBuf[0] = 0x00;
	outBuf[1] = 0xfd;
	outBuf[2] = r;
	outBuf[3] = g;
	outBuf[4] = b;

	return send(outBuf, 5);
}




