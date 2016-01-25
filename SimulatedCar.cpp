#include "SimulatedCar.h"

void SimulatedCar::setRPM(int rpm) {
	if (_manuel) {
		_rpm = rpm;
		// _sendMessage(PID_RPM,_rpm);
	}
}
void SimulatedCar::setFuelLevel(int fuelLevel) {
	if (_manuel) {
		_fuelLevel = fuelLevel;
		// _sendMessage(PID_FUEL_LEVEL,_fuelLevel);
	}
}
void SimulatedCar::setSpeed(int speed) {
	if (_manuel) {
		_speed = speed;
		// _sendMessage(PID_SPEED,_speed);
	}
}
void SimulatedCar::setTemp(int temp) {
	if (_manuel) {
		_temp = temp;
		// _sendMessage(PID_COOLANT_TEMP,_temp);
	}
}

void SimulatedCar::setManuel(bool manuel){
	_manuel = manuel;
}

bool SimulatedCar::shouldRun(unsigned long time) {
	// @IDEA maybe random should run
	return Thread::shouldRun(time);
}

void SimulatedCar::run(){
	if (!_manuel) {
		_speed = random(0,255);
		_rpm = random(0,16384);
		_fuelLevel = random(0,100);
		_temp = random(-40,215);
	}
	_sendMessage(PID_SPEED,_speed);
	_sendMessage(PID_RPM,_rpm);
	_sendMessage(PID_FUEL_LEVEL,_fuelLevel);
	_sendMessage(PID_COOLANT_TEMP,_temp);
	Thread::run();
}

void SimulatedCar::_sendMessage(INT32U pid,int value) {
/*	unsigned int len = 0;
	char *buf;
	sprintf(buf, "%d", value);
	// @TODO send */
}
