#pragma config(Sensor, dgtl1,  turnLever,    sensorTouch);
#pragma config(Sensor, dgtl2,  backLever,    sensorTouch);
#pragma config(Sensor, dgtl3,  resetButton,  sensorTouch);
#pragma config(Sensor, dgtl4,  killSwitch,   sensorTouch);
#pragma config(Motor,  port1,  spoolMotor,   tmotorVex269_MC29, openLoop);

int position = 0; // current documented position of the motor
int maxPos = 500; // the maximum distance the spool can unravel
int spoolSpeed = 13; // the speed at which the spool unravels

bool checkKillSwitch();
void reset();
void turnSpool();

task main() {
	
	reset(); // ensures that the spool position is reset before startup.

	while (!checkKillSwitch()) { // this will loop as long as the kill switch is not pressed.
		
		turnSpool(); // refer to turnSpool() method
	
	}
	
	untilBump(resetButton); // reset button must be pressed after kill switch is executed.
	
	main(); // reboots program.

}

bool checkKillSwitch() {

	if (SensorValue(killSwitch)) return true;
	
	return false;

}

void turnSpool() {

	if (checkKillSwitch() || (SensorValue(turnLever) && SensorValue(backLever))) return;
	// will not run if either the kill switch is pressed or if both levers are
	// being pressed at the same time (to avoid bugs).
	
	if (SensorValue(resetButton)) { // checks if the reset button is pressed during execution.
	
		reset(); // refer to reset() method
		
		return;
	
	}
	
	if (SensorValue(turnLever) && position <= maxPos) {
	
		position++;
		
		setMotorTarget(spoolMotor, position, spoolSpeed);
	
	} // this will run as long as the position has not reached its maximum.
	
	if (SensorValue(backLever) && position > 0) {
	
		position--;
		
		setMotorTarget(spoolMotor, (position * -1), (spoolSpeed) * -1);
	
	} // the spool will never reach below 0.

}

void reset() {

	position = 0;
	
	while (SensorValue(spoolMotor) > position) {
		
		if (SensorValue(resetButton)) break;
		
		setMotorTarget(spoolMotor, SensorValue(spoolMotor) - 1, spoolSpeed);
		
	} // the reset mechanism will stop the instant the kill switch is pressed.
	// although this method of resetting is highly inefficient, the efficiency
	// was a neccesary sacrifice to ensure safety.

}
