#include "RealCar.h"


bool RealCar::shouldRun(unsigned long time) {
	if(CAN_MSGAVAIL == _can->checkReceive()) {
		return true;
	} 
	return false;
}

void RealCar::run(){
	unsigned char len = 0;
	unsigned char buf[29];
	Serial.println("RealCar::run");
	_can->readMsgBuf(&len, buf);

	unsigned long canId = _can->getCanId();

	switch(canId) {
		case PID_SPEED:
			_speed = _parseSpeedMessage(buf);
			break;
		case PID_RPM:
			_rpm = _parseRPMMessage(buf);
			break;
		case PID_FUEL_LEVEL:
			_fuelLevel = _parseFuelLevelMessage(buf);
			break;
		case PID_COOLANT_TEMP:
			_temp = _parseTempMessage(buf);
			break;
	}

	Thread::run();
}

int RealCar::_parseRPMMessage(unsigned char* rpm) {
	// @TODO
	return 0;
}
int RealCar::_parseFuelLevelMessage(unsigned char* fuelLevel) {
	// @TODO
	return 0;
}
int RealCar::_parseSpeedMessage(unsigned char* speed) {
	// @TODO
	return 0;
}
int RealCar::_parseTempMessage(unsigned char* temp) {
	// @TODO
	return 0;
}
