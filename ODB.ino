#include "config.h"

#include <SPI.h>	
#include <mcp_can.h>


#include <ThreadController.h>
#include "SimulatedCar.h"
#include "RealCar.h"
//include "Display.h"


ThreadController control = ThreadController();

MCP_CAN CAN(CAN_SPI_CS_PIN);
RealCar realCar = RealCar(&CAN);
SimulatedCar simulatedCar = SimulatedCar(&CAN);

//Display display;


void realdataCallback(){
	Serial.print("RPM:");
	Serial.println(realCar.getRPM());
	Serial.print("Fuel:");
	Serial.println(realCar.getFuelLevel());
	Serial.print("Speed:");
	Serial.println(realCar.getSpeed());
	Serial.print("Temp:");
	Serial.println(realCar.getTemp());
}

void simulationCallback() {
	Serial.print("S_RPM:");
	Serial.println(simulatedCar.getRPM());
	Serial.print("S_Fuel:");
	Serial.println(simulatedCar.getFuelLevel());
	Serial.print("S_Speed:");
	Serial.println(simulatedCar.getSpeed());
	Serial.print("S_Temp:");
	Serial.println(simulatedCar.getTemp());
}
/*
void enableCanBus() {
	realCar.enabled = true;
}

void disableCanBus() {
	realCar.enabled = false;
}

void enableSimulation() {
	simulatedCar.enabled = true;
}

void disableSimulation() {
	simulatedCar.enabled = false;
}

void disableAll() {
	realCar.enabled = false;
	simulatedCar.enabled = false;
}

void enableAll() {
	realCar.enabled = true;
	simulatedCar.enabled = true;
}*/

/*
 * internal function to reset arduino
 */
//void(* resetFunc) (void) = 0; //declare reset function @ address 0

void setup() {
	Serial.begin(9600);
	randomSeed(analogRead(0));
/*
	Display INIT
*/
/*DISPLAY_INIT:
	if (!display.init()) {
		// @TODO message if fail
		//nexSerial.println("Display init fail");
		//nexSerial.println("Init Display again");
		delay(100);
		goto DISPLAY_INIT;
	}*/
/*
	Can Bus INIT
*/
CAN_INIT:
	// @TODO display message
	//n_initmessage.setText("init CAN BUS Shield");
	if (CAN_OK != CAN.begin(CAN_500KBPS)) {
		//n_initmessage.setText("CAN BUS Shield init fail!");
		delay(2000);
		goto CAN_INIT;
	}

/*
 Threads INIT
 */
	// Configure realCar
	realCar.onRun(realdataCallback);
	realCar.setInterval(REALDATA_TIMEFRAME);
	realCar.enabled = false;

	// Configure simulation
	simulatedCar.onRun(simulationCallback);
	simulatedCar.setInterval(SIMULATION_TIMEFRAME);
	simulatedCar.enabled = false;

	// Adds both threads to the controller
	control.add(&realCar);
	control.add(&simulatedCar);
	Serial.println("begin");
}

void loop() {
	control.run();
	//display.nextLoop();
}
