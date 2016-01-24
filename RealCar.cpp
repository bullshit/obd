#include "RealCar.h"


bool RealCar::shouldRun(unsigned long time) {
	Serial.println("RealCar::shouldRun");
	if(CAN_MSGAVAIL == _can->checkReceive()) {
		return true;
	} 
	return false;
}

void RealCar::run(){
	unsigned char len = 0;
	unsigned char buf[8];
	Serial.println("RealCar::run");
	if(CAN_MSGAVAIL == _can->checkReceive())            // check if data coming
	{
		_can->readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

		unsigned long canId = _can->getCanId();

		// @TODO parse canId
	}
	Thread::run();
}

