/*
 * globals.h
 *
 *  Created on: Jun 2, 2023
 *      Author: vagrant
 */

#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

#include "sbus.h"

namespace events {

	class Event8 {
	public:
		Event8( const unsigned char& t )
		: target(t-1){}

		void tick(){
			if ( cnt < target ){
				cnt++;
			} else {
				trigger=true;
			}
		}

		void clear() {
			trigger=false;
			cnt=0;
		}

		const bool flag(){
			return trigger;
		}


	private:
		unsigned char cnt{0};
		const unsigned char target{0};
		bool trigger{false};
	};



	class Event16 {
	public:
		Event16( const unsigned int& t )
		: target(t-1){}

		void tick(){
			if ( cnt < target ){
				cnt++;
			} else {
				trigger=true;
			}
		}

		void clear() {
			trigger=false;
			cnt=0;
		}

		const bool flag(){
			return trigger;
		}

	private:
		unsigned int cnt{0};
		const unsigned int target{0};
		bool trigger{false};
	};


}


class Globals {
public:


	uint16_t i{0};
	uint32_t millis{0};

	events::Event8  time10{10};
	events::Event8  time100{100};
	events::Event16 time1000{1000};

	def::Sbus Sbus;



};


inline Globals G;

#endif /* SRC_GLOBALS_H_ */
