#include "SimulatedCar.h"

void SimulatedCar::setRPM(int rpm) {
	if (_manuel) {
		if (rpm > MAX_RPM) {
			rpm = MAX_RPM;
		}
		else if (rpm < MIN_RPM) {
			rpm = MIN_RPM;
		}
		_rpm = rpm;
	}
}
void SimulatedCar::incRPM(void) {
	setRPM(getRPM()+SIMULATION_RPM_STEP);
}
void SimulatedCar::decRPM(void) {
	setRPM(getRPM()-SIMULATION_RPM_STEP);
}


void SimulatedCar::setFuelLevel(int fuelLevel) {
	if (_manuel) {
		if (fuelLevel > MAX_FUELLEVEL) {
			fuelLevel = MAX_FUELLEVEL;
		}
		else if (fuelLevel < MIN_FUELLEVEL) {
			fuelLevel = MIN_FUELLEVEL;
		}
		_fuelLevel = fuelLevel;
	}
}

void SimulatedCar::incFuelLevel(void) {
	setFuelLevel(getFuelLevel()+SIMULATION_FUELLEVEL_STEP);
}
void SimulatedCar::decFuelLevel(void) {
	setFuelLevel(getFuelLevel()-SIMULATION_FUELLEVEL_STEP);
}
	


void SimulatedCar::setSpeed(int speed) {
	if (_manuel) {
		if (speed > MAX_SPEED) {
			speed = MAX_SPEED;
		}
		else if (speed < MIN_SPEED) {
			speed = MIN_SPEED;
		}
		_speed = speed;
	}
}
void SimulatedCar::incSpeed(void) {
	setSpeed(getSpeed()+SIMULATION_SPEED_STEP);
}
void SimulatedCar::decSpeed(void) {
	setSpeed(getSpeed()-SIMULATION_SPEED_STEP);
}



void SimulatedCar::setTemp(int temp) {
	if (_manuel) {
		if (temp > MAX_TEMP) {
			_temp = MAX_TEMP;
		}
		else if (temp < MIN_TEMP) {
			temp = MIN_TEMP;
		}
		_temp = temp;
	}
}

void SimulatedCar::incTemp(void) {
	setTemp(getTemp()+SIMULATION_TEMP_STEP);
}
void SimulatedCar::decTemp(void) {
	setTemp(getTemp()-SIMULATION_TEMP_STEP);
}




void SimulatedCar::setManuel(bool manuel){
	_manuel = manuel;
}

bool SimulatedCar::isManuel(void) {
	return _manuel;
}

bool SimulatedCar::shouldRun(unsigned long time) {
	// @IDEA maybe random should run
	return Thread::shouldRun(time);
}

void SimulatedCar::run(){
	if (!_manuel) {
		//_speed = random(0,200);
		_speed += SIMULATION_SPEED_STEP;
		if (_speed > MAX_SPEED)
			_speed = MIN_SPEED;

		//_rpm = random(0,16384);
		// @TODO @WARNING FIX THIS
		_rpm = random(50,310);

		//_fuelLevel = random(0,100);
		_fuelLevel -= SIMULATION_FUELLEVEL_STEP;
		if (_fuelLevel < MIN_TEMP)
			_fuelLevel = MAX_TEMP;

		//_temp = random(-40,215);
		_temp += SIMULATION_TEMP_STEP;
		if (_temp > MAX_TEMP)
			_temp = MIN_TEMP;		
		
	}
	_sendMessage(PID_SPEED,_speed);
	_sendMessage(PID_RPM,_rpm);
	_sendMessage(PID_FUEL_LEVEL,_fuelLevel);
	_sendMessage(PID_COOLANT_TEMP,_temp);
	Thread::run();
}

void SimulatedCar::_sendMessage(INT32U pid,int value) {
	byte *buf;
	switch(pid) {
		case PID_SPEED:
			buf = _createSpeedMessage(value);
			break;
		case PID_RPM:
			buf = _createRPMMessage(value);
			break;
		case PID_FUEL_LEVEL:
			buf = _createFuelLevelMessage(value);
			break;
		case PID_COOLANT_TEMP:
			buf = _createTempMessage(value);
			break;
	}

	_can->sendMsgBuf(pid,0, 8, buf);
}

byte* SimulatedCar::_createRPMMessage(int rpm) {
	byte *buf;
	// @TODO
	return buf;
}
byte* SimulatedCar::_createFuelLevelMessage(int fuelLevel) {
	byte *buf;
	// @TODO
	return buf;
}
byte* SimulatedCar::_createSpeedMessage(int speed) {
	byte *buf;
	// @TODO
	return buf;
}
byte* SimulatedCar::_createTempMessage(int temp) {
	byte *buf;
	// @TODO
	return buf;
}
