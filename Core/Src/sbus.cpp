/*
 * sbus.cpp
 *
 *  Created on: Jun 2, 2023
 *      Author: vagrant
 */

#include <sbus.h>

using namespace def;

Sbus::Sbus() {

	// TODO Auto-generated constructor stub

}

Sbus::~Sbus() {
	// TODO Auto-generated destructor stub
}


const unsigned int Sbus::sbus2pwm( const unsigned int& sbus )
{
	const float a = 894.384;
	const float b = 0.610501;

	// extra term is for proper rounding
	// otherwise it gets rounded down always
	return static_cast<unsigned int>( a + b*sbus + (0.5-(sbus<0)) );

}

void Sbus::decodeChannels(){

	//if ((buffer[23] >> 2) & 0x0001) {
	//	lost++;
	//	return false;
	//}

	Channel[0]  = sbus2pwm((buffer[1]    |buffer[2]<<8)                 & 0x07FF);
	Channel[1]  = sbus2pwm((buffer[2]>>3 |buffer[3]<<5)                 & 0x07FF);
	Channel[2]  = sbus2pwm((buffer[3]>>6 |buffer[4]<<2 |buffer[5]<<10)  & 0x07FF);
	Channel[3]  = sbus2pwm((buffer[5]>>1 |buffer[6]<<7)                 & 0x07FF);
	Channel[4]  = sbus2pwm((buffer[6]>>4 |buffer[7]<<4)                 & 0x07FF);
	Channel[5]  = sbus2pwm((buffer[7]>>7 |buffer[8]<<1 |buffer[9]<<9)   & 0x07FF);
	Channel[6]  = sbus2pwm((buffer[9]>>2 |buffer[10]<<6)                & 0x07FF);
	Channel[7]  = sbus2pwm((buffer[10]>>5|buffer[11]<<3)                & 0x07FF);
	Channel[8]  = sbus2pwm((buffer[12]   |buffer[13]<<8)                & 0x07FF);
	Channel[9]  = sbus2pwm((buffer[13]>>3|buffer[14]<<5)                & 0x07FF);
	Channel[10] = sbus2pwm((buffer[14]>>6|buffer[15]<<2|buffer[16]<<10) & 0x07FF);
	Channel[11] = sbus2pwm((buffer[16]>>1|buffer[17]<<7)                & 0x07FF);
	Channel[12] = sbus2pwm((buffer[17]>>4|buffer[18]<<4)                & 0x07FF);
	Channel[13] = sbus2pwm((buffer[18]>>7|buffer[19]<<1|buffer[20]<<9)  & 0x07FF);
	Channel[14] = sbus2pwm((buffer[20]>>2|buffer[21]<<6)                & 0x07FF);
	Channel[15] = sbus2pwm((buffer[21]>>5|buffer[22]<<3)                & 0x07FF);

	( (buffer[23])      & 0x0001) ? Channel[16] = 2047: Channel[16] = 0;
	( (buffer[23] >> 1) & 0x0001) ? Channel[17] = 2047: Channel[17] = 0;

	if ((buffer[23] >> 3) & 0x0001) {
		failsafe = true;
	} else {
		failsafe = false;
	}

}

void Sbus::readSbusFrame()
{
	if ( buffer[0] == START_BYTE && buffer[SBUS_FRAME_LEN-1] == END_BYTE ) {
		decodeChannels();
		synced=true;
	} else {
		synced=false;
		lost++;
	}

}

void Sbus::findSync( const unsigned char& byte )
{
	if ( !reading && byte == START_BYTE ) {
		reading=true;
		i_buf=0;
	}

	if ( reading ){


		if ( byte == END_BYTE && i_buf == SBUS_FRAME_LEN - 1 ) {
			synced=true;
			reading=false;
		}

		i_buf++;
	}
}


const bool Sbus::isSynced()
{
	return synced;
}


