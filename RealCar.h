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

};

#endif
