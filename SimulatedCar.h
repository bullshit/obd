#ifndef __ODBSIMULATEDCAR_H__
#define __ODBSIMULATEDCAR_H__

#include <Arduino.h>

#include "Car.h"

class SimulatedCar : public Car {
public:
	SimulatedCar(MCP_CAN* CAN) : Car(CAN) {}
	bool shouldRun(unsigned long time);
	void run();
protected:

};

#endif
