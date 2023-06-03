/*
 * sbus.h
 *
 *  Created on: Jun 2, 2023
 *      Author: vagrant
 */

#ifndef INC_SBUS_H_
#define INC_SBUS_H_

namespace def {

	namespace def{
		class Channel {
		public:
			Channel() = default;


			const unsigned int operator() ()
			{
				return value;
			}

			void operator=( const unsigned int& val )
			{
				value = val;
			}

		private:
			unsigned int value{1500};
		};
	}

	class Sbus {


	public:
		Sbus();
		virtual ~Sbus();

		void findSync( const unsigned char& byte );

		void readSbusFrame();

		const bool isSynced();

		void decodeChannels();

	private:

		const unsigned int sbus2pwm( const unsigned int& sbus );

		// Constants
		static const unsigned char START_BYTE{0x0F};
		static const unsigned char END_BYTE{0x00};
		//static const unsigned char OUT_OF_SYNC_THD{10};
		//static const unsigned char SBUS_SIGNAL_OK{0};
		//static const unsigned char SBUS_SIGNAL_LOST{1};
		//static const unsigned char SBUS_SIGNAL_FAILSAFE{2};


		// Variables
		unsigned char i_buf{0};

		bool reading{false};
		bool synced{false};
		bool failsafe{true};

		unsigned int lost{0};


	public:

		static const unsigned char SBUS_FRAME_LEN{25};
		static const unsigned char SBUS_NUM_CHAN{16};

		unsigned char buffer[SBUS_FRAME_LEN]={0};
		unsigned int packet{0};


		def::Channel Channel[SBUS_NUM_CHAN];

	};

}

#endif /* INC_SBUS_H_ */
