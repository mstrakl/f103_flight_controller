/*
 * globals.h
 *
 *  Created on: Jun 2, 2023
 *      Author: vagrant
 */

#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

#include "sbus.h"

class Globals {
public:


	uint16_t i{0};
	uint32_t millis{0};

	def::Sbus Sbus;



};


inline Globals G;

#endif /* SRC_GLOBALS_H_ */
