#include "RealCar.h"


bool RealCar::shouldRun(unsigned long time) {
	if(CAN_MSGAVAIL == _can->checkReceive()) {
		return true;
	} 
	return false;
}

void RealCar::run(){
	unsigned char len = 0;
	unsigned char buf[21];
	Serial.println("RealCar::run");
	_can->readMsgBuf(&len, buf);

	unsigned long canId = _can->getCanId();

	// @TODO parse canId
	Thread::run();
}

