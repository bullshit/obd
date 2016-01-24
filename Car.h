#ifndef __ODBCAR_H__
#define __ODBCAR_H__

#include <Arduino.h>

#include "config.h"
#include <Thread.h>
#include <mcp_can.h>

class Car : public Thread {
public:
	Car(MCP_CAN* CAN) {
		_can = CAN;
	}
	int getRPM(void);
	int getFuelLevel(void);
	int getSpeed(void);
	int getTemp(void);

	virtual void run();
protected:
	int _rpm;
	int _fuelLevel;
	int _speed;
	int _temp;
	bool _canEnabled;
	MCP_CAN *_can;
};

#endif
