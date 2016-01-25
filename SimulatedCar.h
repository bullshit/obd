#ifndef __ODBSIMULATEDCAR_H__
#define __ODBSIMULATEDCAR_H__

#include <Arduino.h>

#include "Car.h"

class SimulatedCar : public Car {
public:
	SimulatedCar(MCP_CAN* CAN) : Car(CAN) {}
	bool shouldRun(unsigned long time);
	void run();

	void setRPM(int rpm);
	void setFuelLevel(int fuelLevel);
	void setSpeed(int speed);
	void setTemp(int temp);
	void setManuel(bool manuel);
protected:
	void _sendMessage(INT32U pid,int value);
	bool _manuel = false;
};

#endif
