#include "SimulatedCar.h"



bool SimulatedCar::shouldRun(unsigned long time) {
	// @IDEA maybe random should run
	return Thread::shouldRun(time);
}

void SimulatedCar::run(){
	_speed = random(0,255);
	_sendMessage(PID_SPEED,_speed);

	_rpm = random(0,16384);
	_sendMessage(PID_RPM,_rpm);

	_fuelLevel = random(0,100);
	_sendMessage(PID_FUEL_LEVEL,_fuelLevel);

	_temp = random(-40,215);
	_sendMessage(PID_COOLANT_TEMP,_temp);
	
	Thread::run();
}

void SimulatedCar::_sendMessage(INT32U pid,int value) {
/*	unsigned int len = 0;
	char *buf;
	sprintf(buf, "%d", value);
	// @TODO send */
}
