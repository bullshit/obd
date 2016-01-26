#ifndef __ODBCAR_H__
#define __ODBCAR_H__

#include <Arduino.h>

#include "config.h"
#include <Thread.h>
#include <mcp_can.h>


#define PID_RPM 0x0C
#define PID_SPEED 0x0D

#define PID_FUEL_LEVEL 0x2F
#define PID_SHORT_TERM_FUEL_TRIM_1 0x06
#define PID_LONG_TERM_FUEL_TRIM_1 0x07
#define PID_SHORT_TERM_FUEL_TRIM_2 0x08
#define PID_LONG_TERM_FUEL_TRIM_2 0x09

#define PID_COOLANT_TEMP 0x05
#define PID_INTAKE_TEMP 0x0F
#define PID_AMBIENT_TEMP 0x46
#define PID_ENGINE_OIL_TEMP 0x5C


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
	int _rpm = 0;
	int _fuelLevel = 100;
	int _speed = 0;
	int _temp = 0;
	MCP_CAN *_can;
};

#endif
