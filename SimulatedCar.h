#ifndef __ODBSIMULATEDCAR_H__
#define __ODBSIMULATEDCAR_H__

#include <Arduino.h>

#include "Car.h"

class SimulatedCar : public Car {
public:
	SimulatedCar(MCP_CAN* CAN) : Car(CAN) {
		randomSeed(analogRead(0));
	}
	bool shouldRun(unsigned long time);
	void run();

	void setRPM(int rpm);
	void incRPM(void);
	void decRPM(void);

	void setFuelLevel(int fuelLevel);
	void incFuelLevel(void);
	void decFuelLevel(void);

	void setSpeed(int speed);
	void incSpeed(void);
	void decSpeed(void);


	void setTemp(int temp);
	void incTemp(void);
	void decTemp(void);

	void setManuel(bool manuel);
	bool isManuel(void);
protected:
	bool _manuel = false;

	void _sendMessage(INT32U pid,int value);
	byte* _createRPMMessage(int rpm);
	byte* _createFuelLevelMessage(int fuelLevel);
	byte* _createSpeedMessage(int speed);
	byte* _createTempMessage(int temp);
};

#endif
