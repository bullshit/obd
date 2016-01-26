#define SKETCH_VERSION "v0.0.2"

#include "config.h"

#include <SPI.h>	
#include <mcp_can.h>

#include <MemoryFree.h>
#include <ThreadController.h>
#include "SimulatedCar.h"
#include "RealCar.h"


#include <Nextion.h>


ThreadController control = ThreadController();

MCP_CAN CAN(CAN_SPI_CS_PIN);
//RealCar realCar = RealCar(&CAN);
SimulatedCar realCar = SimulatedCar(&CAN);
SimulatedCar simulatedCar = SimulatedCar(&CAN);



bool REALCAR_VISUAL = false;
bool SIMULATION_VISUAL = false;

/*****************************************************
 *
 * Nextion objects
 *****************************************************/

/*
 * Init page
 */
NexPage n_initPage = NexPage(0,0,"initPage");
NexText n_initMessage = NexText(0,1,"initMessage");

/*
 * Menu page
 */
NexPage n_menuPage = NexPage(1,0,"menuPage");
NexButton n_resetButton = NexButton(1, 1, "resetBtn");
NexButton n_realCarButton = NexButton(1, 2, "realCarBtn");
NexButton n_simulationButton = NexButton(1, 3, "simulationBtn");
NexButton n_aboutButton = NexButton(1, 4, "aboutBtn");
NexButton n_realCarVisualButton = NexButton(1, 5, "realCarVisBtn");
NexButton n_simulationVisualButton = NexButton(1, 6, "simVisBtn");

/*
 * Realcar page
 */
NexPage n_realCarPage = NexPage(2,0,"realCarPage");
NexButton n_realCarBackButton = NexButton(2, 1, "rlBackBtn");

NexText n_realCarSpeedText = NexText(3,7,"realSpeedTxt");
NexText n_realCarRPMText = NexText(3,8,"realRPMTxt");
NexText n_realCarFuelLevelText = NexText(3,9,"realFuelTxt");
NexText n_realCarTempText = NexText(3,10,"realTempTxt");

/*
 * Simulation page
 */
NexPage n_simulationPage = NexPage(3,0,"simulationPage");
NexButton n_simulationBackButton = NexButton(3, 1, "simBackBtn");

NexText n_simulationSpeedText = NexText(3,7,"simSpeedTxt");
NexText n_simulationRPMText = NexText(3,8,"simRPMTxt");
NexText n_simulationFuelLevelText = NexText(3,9,"simFuelTxt");
NexText n_simulationTempText = NexText(3,10,"simTempTxt");


/*
 * About page
 */
NexPage n_aboutPage = NexPage(4,0,"aboutPage");
NexText n_aboutVersionText = NexText(4,4,"aboutVTxt");
NexText n_aboutFreeMemoryText = NexText(4,6,"aboutMemTxt");

/*
 * Real Car with nice visualisation
 */
NexPage n_visualRealCarPage = NexPage(5,0,"visRlPage");
NexButton n_visualRealCarBackButton = NexButton(5, 5, "visRlBackBtn");
NexGauge n_visualRealCarSpeedGauge = NexGauge(5,2,"visRlSpeedG");
NexGauge n_visualRealCarRPMGauge = NexGauge(5,3,"visRlRPMG");
NexProgressBar n_visualRealCarFuelPb = NexProgressBar(5,4,"visRlFuel");
NexProgressBar n_visualRealCarTempPb = NexProgressBar(5,6,"visRlTemp");


/*
 * Simulated Car with nice visualisation
 */
NexPage n_visualSimulationPage = NexPage(6,0,"visSimPage");
NexButton n_visualSimulationBackButton = NexButton(6, 5, "visSimBackBtn");
NexGauge n_visualSimulationSpeedGauge = NexGauge(6,2,"visSimSpeedG");
NexGauge n_visualSimulationRPMGauge = NexGauge(6,3,"visSimRPMG");
NexProgressBar n_visualSimulationFuelPb = NexProgressBar(6,4,"visSimFuel");
NexProgressBar n_visualSimulationTempPb = NexProgressBar(6,6,"visSimTemp");
NexText n_visualSimulationModeTxt = NexText(6,7,"visSimMode");
NexHotspot n_visualSimulationSwitchMode    = NexHotspot(6, 8, "visSwitchMode");

NexButton n_visualSimulationSpeedPlusButton = NexButton(6, 10, "visSimSpPBtn");
NexButton n_visualSimulationSpeedMinusButton = NexButton(6, 11, "visSimSpMBtn");

NexButton n_visualSimulationRPMPlusButton = NexButton(6, 12, "visSimRPBtn");
NexButton n_visualSimulationRPMMinusButton = NexButton(6, 13, "visSimRMBtn");

NexButton n_visualSimulationFuelLevelPlusButton = NexButton(6, 14, "visSimFPBtn");
NexButton n_visualSimulationFuelLevelMinusButton = NexButton(6, 15, "visSimFMBtn");

NexButton n_visualSimulationTempPlusButton = NexButton(6, 16, "visSimTPBtn");
NexButton n_visualSimulationTempMinusButton = NexButton(6, 17, "visSimTMBtn");

NexTouch *n_nex_listen_list[] = {
	&n_resetButton,
	&n_realCarButton,
	&n_simulationButton,
	&n_aboutButton,
	&n_realCarVisualButton,
	&n_simulationVisualButton,


	&n_visualSimulationSwitchMode,
	&n_visualSimulationSpeedPlusButton,
	&n_visualSimulationSpeedMinusButton,
	&n_visualSimulationRPMPlusButton,
	&n_visualSimulationRPMMinusButton,
	&n_visualSimulationFuelLevelPlusButton,
	&n_visualSimulationFuelLevelMinusButton,
	&n_visualSimulationTempPlusButton,
	&n_visualSimulationTempMinusButton,





	&n_realCarBackButton,
	&n_simulationBackButton,
	&n_visualRealCarBackButton,
	&n_visualSimulationBackButton,

	NULL
};

/**********************************
 *
 * Helper functions
 *
 **********************************/
void(* resetFunc) (void) = 0;//declare reset function at address 0

char* int2charA(int value) {
	char buffer[100] = {0};
	memset(buffer, 0, sizeof(buffer));
	itoa(value, buffer, 10);
	return buffer;
}


char* int2charA(int value,String unit) {

	String s = "";
	s = String(value);
	String combined = s+" "+unit;

	unsigned int len = combined.length()+1;
	char buffer[len];
	
	combined.toCharArray(buffer,len);
	return buffer;
}

int calcRPMGauge(int rpm) {
	if (rpm > MAX_RPM)
		rpm = MAX_RPM;
	if (rpm < 0)
		rpm = 0;
// @TODO @WARNING FIX THIS
	return rpm;
}

int calcSpeedGauge(int speed) {
	if (speed > MAX_SPEED)
		speed = MAX_SPEED;
	if (speed < 0)
		speed = 0;
	float factor = (360 - GAUGE_MIN_SPEED_DEGREE + GAUGE_MAX_SPEED_DEGREE) / (float)MAX_SPEED;
	int degree = ((int)(GAUGE_MIN_SPEED_DEGREE + factor * speed)) % 360;
	return degree;
}

int calcFuelProgressBar(int fuelLevel) {
	return fuelLevel;
}

// @TODO @WARNING FIX THIS
int calcTemperatureProgressBar(int temp) {
	if (temp > 215)
		return 100;
	if (temp < -40)
		return 0;
	int tmp = (temp+40) * 100 / (215 + 40);
	return tmp;
}

void attachManuelSimulationCallbacks() {
	n_visualSimulationSpeedPlusButton.attachPop(cb_visualSimulationSpeedPlus,&n_visualSimulationSpeedPlusButton);
	n_visualSimulationSpeedMinusButton.attachPop(cb_visualSimulationSpeedMinus,&n_visualSimulationSpeedMinusButton);

	n_visualSimulationRPMPlusButton.attachPop(cb_visualSimulationRPMPlus,&n_visualSimulationRPMPlusButton);
	n_visualSimulationRPMMinusButton.attachPop(cb_visualSimulationRPMMinus,&n_visualSimulationRPMMinusButton);

	n_visualSimulationFuelLevelPlusButton.attachPop(cb_visualSimulationFuelLevelPlus,&n_visualSimulationFuelLevelPlusButton);
	n_visualSimulationFuelLevelMinusButton.attachPop(cb_visualSimulationFuelLevelMinus,&n_visualSimulationFuelLevelMinusButton);

	n_visualSimulationTempPlusButton.attachPop(cb_visualSimulationTempPlus,&n_visualSimulationTempPlusButton);
	n_visualSimulationTempMinusButton.attachPop(cb_visualSimulationTempMinus,&n_visualSimulationTempMinusButton);
}

void detachManuelSimulationCallbacks() {
	n_visualSimulationSpeedPlusButton.detachPop();
	n_visualSimulationSpeedMinusButton.detachPop();

	n_visualSimulationRPMPlusButton.detachPop();
	n_visualSimulationRPMMinusButton.detachPop();

	n_visualSimulationFuelLevelPlusButton.detachPop();
	n_visualSimulationFuelLevelMinusButton.detachPop();

	n_visualSimulationTempPlusButton.detachPop();
	n_visualSimulationTempMinusButton.detachPop();
}

/**********************************
 *
 * Nextion callbacks
 *
 **********************************/
void cb_resetButtonPressed(void *ptr) {
	resetFunc();
}

void cb_realCarButtonPressed(void *ptr) {
	realCar.enabled = true;
	simulatedCar.enabled = false;
	REALCAR_VISUAL = false;
	n_realCarPage.show();
}

void cb_realCarVisualButtonPressed(void *ptr) {
	realCar.enabled = true;
	simulatedCar.enabled = false;
	REALCAR_VISUAL = true;
	n_visualRealCarPage.show();
}

void cb_simulationVisualButtonPressed(void *ptr) {
	realCar.enabled = false;
	simulatedCar.enabled = true;
	SIMULATION_VISUAL = true;
	if (simulatedCar.isManuel()) {
		attachManuelSimulationCallbacks();
	}
	else {
		detachManuelSimulationCallbacks();
	}
	n_visualSimulationPage.show();
}


void cb_simulationButtonPressed(void *ptr) {
	realCar.enabled = false;
	simulatedCar.enabled = true;
	SIMULATION_VISUAL = false;
	simulatedCar.setManuel(false);
	n_simulationPage.show();
}

void cb_aboutButtonPressed(void *ptr) {
	realCar.enabled = false;
	simulatedCar.enabled = false;

	n_aboutPage.show();

	n_aboutVersionText.setText(SKETCH_VERSION);
	n_aboutFreeMemoryText.setText(int2charA(freeMemory()));
}


void cb_globalBackToMenu(void *ptr) {
	realCar.enabled = false;
	simulatedCar.enabled = false;
	n_menuPage.show();
}


void cb_switchSimulationMode(void *ptr) {
	if (simulatedCar.isManuel()) {
		n_visualSimulationModeTxt.setText("auto");
		detachManuelSimulationCallbacks();
		simulatedCar.enabled = true;
	}
	else {
		n_visualSimulationModeTxt.setText("manual");
		attachManuelSimulationCallbacks();
		simulatedCar.enabled = false;
	}
	simulatedCar.setManuel(!simulatedCar.isManuel());
}


void cb_visualSimulationSpeedPlus(void *ptr) {
	simulatedCar.incSpeed();
	simulatedCar.run();
}
void cb_visualSimulationSpeedMinus(void *ptr) {
	simulatedCar.decSpeed();
	simulatedCar.run();
}


void cb_visualSimulationRPMPlus(void *ptr) {
	simulatedCar.incRPM();
	simulatedCar.run();
}
void cb_visualSimulationRPMMinus(void *ptr) {
	simulatedCar.decRPM();
	simulatedCar.run();
}

void cb_visualSimulationFuelLevelPlus(void *ptr) {
	simulatedCar.incFuelLevel();
	simulatedCar.run();
}
void cb_visualSimulationFuelLevelMinus(void *ptr) {
	simulatedCar.decFuelLevel();
	simulatedCar.run();
}


void cb_visualSimulationTempPlus(void *ptr) {
	simulatedCar.incTemp();
	simulatedCar.run();
}
void cb_visualSimulationTempMinus(void *ptr) {
	simulatedCar.decTemp();
	simulatedCar.run();
}
/**********************************
 *
 * Thread callbacks
 *
 **********************************/
void realdataCallback(){
	if (REALCAR_VISUAL) {
		n_visualRealCarSpeedGauge.setValue(calcSpeedGauge(realCar.getSpeed()));
		n_visualRealCarRPMGauge.setValue(calcRPMGauge(realCar.getRPM()));
		n_visualRealCarFuelPb.setValue(calcFuelProgressBar(realCar.getFuelLevel()));
		n_visualRealCarTempPb.setValue(calcTemperatureProgressBar(realCar.getTemp()));
	}
	else {
		n_realCarSpeedText.setText(int2charA(realCar.getSpeed(),F("km/h")));
		n_realCarRPMText.setText(int2charA(realCar.getRPM(),F("rpm")));
		n_realCarFuelLevelText.setText(int2charA(realCar.getFuelLevel(),F("%")));
		n_realCarTempText.setText(int2charA(realCar.getTemp(),F("C")));
	}
}

void simulationCallback() {
	if (SIMULATION_VISUAL) {
		n_visualSimulationSpeedGauge.setValue(calcSpeedGauge(simulatedCar.getSpeed()));
		n_visualSimulationRPMGauge.setValue(calcRPMGauge(simulatedCar.getRPM()));
		n_visualSimulationFuelPb.setValue(calcFuelProgressBar(simulatedCar.getFuelLevel()));
		n_visualSimulationTempPb.setValue(calcTemperatureProgressBar(simulatedCar.getTemp()));
	}
	else {
		n_simulationSpeedText.setText(int2charA(simulatedCar.getSpeed(),F("km/h")));
		n_simulationRPMText.setText(int2charA(simulatedCar.getRPM(),F("rpm")));
		n_simulationFuelLevelText.setText(int2charA(simulatedCar.getFuelLevel(),F("%")));
		n_simulationTempText.setText(int2charA(simulatedCar.getTemp(),F("C")));
	}
}

void setup() {
/*
	Display INIT
*/
DISPLAY_INIT:
	if (!nexInit()) {
	/*		nexSerial.println("\nDisplay init fail");
			nexSerial.println("\nInit Display again");*/
		delay(2000);
		//goto DISPLAY_INIT;
	}

/*
	Touch Event Init
*/
n_resetButton.attachPop(cb_resetButtonPressed, &n_resetButton);
n_realCarButton.attachPop(cb_realCarButtonPressed, &n_realCarButton);
n_simulationButton.attachPop(cb_simulationButtonPressed, &n_simulationButton);
n_aboutButton.attachPop(cb_aboutButtonPressed,&n_aboutButton);
n_realCarVisualButton.attachPop(cb_realCarVisualButtonPressed,&n_realCarVisualButton);
n_simulationVisualButton.attachPop(cb_simulationVisualButtonPressed,&n_simulationVisualButton);

n_realCarBackButton.attachPop(cb_globalBackToMenu,&n_realCarBackButton);
n_simulationBackButton.attachPop(cb_globalBackToMenu,&n_simulationBackButton);
n_visualRealCarBackButton.attachPop(cb_globalBackToMenu,&n_visualRealCarBackButton);
n_visualSimulationBackButton.attachPop(cb_globalBackToMenu,&n_visualSimulationBackButton);

n_visualSimulationSwitchMode.attachPop(cb_switchSimulationMode,&n_visualSimulationSwitchMode);


/*
	Can Bus INIT
*/
CAN_INIT:
	n_initMessage.setText("init CAN BUS Shield");
	delay(1000);
	if (CAN_OK != CAN.begin(CAN_500KBPS)) {
		n_initMessage.setText("CAN BUS Shield init fail!restarting...");
		delay(2000);
		goto CAN_INIT;
	}
n_initMessage.setText("CAN BUS Shield initialized!");
delay(1000);


/*
 Threads INIT
 */
	// Configure canbus thread
	realCar.onRun(realdataCallback);
	realCar.setInterval(REALDATA_TIMEFRAME);
	realCar.enabled = false;

	// Configure simulation thread
	simulatedCar.onRun(simulationCallback);
	simulatedCar.setInterval(SIMULATION_TIMEFRAME);
	simulatedCar.enabled = false;

	// Adds both threads to the controller
	control.add(&realCar);
	control.add(&simulatedCar);

	// show start page
	n_menuPage.show();
	n_aboutVersionText.setText(SKETCH_VERSION);
}

void loop() {
	control.run();
	nexLoop(n_nex_listen_list); 
}
