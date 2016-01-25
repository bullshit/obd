#ifndef __ODBREALCAR_H__
#define __ODBREALCAR_H__

#include <Arduino.h>

#include "Car.h"


class RealCar : public Car {
public:
	RealCar(MCP_CAN* CAN) : Car(CAN) {}
	bool shouldRun(unsigned long time);
	void run();
protected:
	int _parseRPMMessage(unsigned char* rpm);
	int _parseFuelLevelMessage(unsigned char* fuelLevel);
	int _parseSpeedMessage(unsigned char* speed);
	int _parseTempMessage(unsigned char* temp);
};

#endif
