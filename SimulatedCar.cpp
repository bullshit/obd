#include "SimulatedCar.h"



bool SimulatedCar::shouldRun(unsigned long time) {
	// @IDEA maybe random should run
	return Thread::shouldRun(time);
}

void SimulatedCar::run(){
	Serial.println("SimulatedCar::run");
	Thread::run();
}
