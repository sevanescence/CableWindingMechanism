#pragma config(Sensor, dgtl1,  retLever,    sensorTouch);
#pragma config(Sensor, dgtl2,  outLever,    sensorTouch);
#pragma config(Sensor, dgtl3,  resetButton,  sensorTouch);
#pragma config(Sensor, dgtl4,  killSwitch,   sensorTouch);
#pragma config(Sensor, dgtl11, motorEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,  spoolMotor,   tmotorVex269_MC29, openLoop);

// global variables used for machine status display
int position = 0; // position of the motor, recorded by an encoder
string status = "uncontrolled"; // which lever is currently being pressed to turn the motor
bool resetting = false; // whether or not the machine is currently executing the reset() operation

void reset(); // method used to retract the motor to zero
void update(); // method used to update the position display
task main() {

	update();

	while (!SensorValue(killSwitch)) { // will run cable winding program until the kill switch is pressed

		stopMotor(spoolMotor); // stops the motor at the beginning of the while loop to avoid machine lag

		if (SensorValue(resetButton)) { // checks if the reset button is pressed before lever operations
			reset();
			startTask(main); // restarts the program by reinstantiating the main method
			return; // stops the current main method instance to avoid bugs where the program would
			        // check for a reset call twice
		} // the reset block above allows the reset button and kill switch to be mashed as many times as
		  // the user desires without breaking the program
		
		// unravel and retration levers are written in loops rather than loop statements in order to avoid
		// further machine lag

		while (SensorValue(retLever) && SensorValue(motorEncoder) < 0) { // retraction lever will only work if the spool is out
			if (SensorValue(killSwitch)) break; // checks if the kill switch is pressed
			status = "retracting...";
			if (SensorValue(motorEncoder) > -50) {
				startMotor(spoolMotor, 24); // the motor will slow down if the encoder approaches zero, to avoid bugs
				                            // in which the stopping motor won't go to a complete halt before the
				                            // encoder reads a value far above zero
			} else {
				startMotor(spoolMotor, 40); // as long as the encoder is not approaching zero, the motor will retract
				                            // consistently
			}
			update();
		}

		while (SensorValue(outLever)) {
			if (SensorValue(killSwitch)) break; // checks if the kill switch is pressed
			status = "releasing...";
			startMotor(spoolMotor, -40);
			update();
		}
		
		status = "uncontrolled";

	} stopMotor(spoolMotor); // stops the motor at the end of the loop to avoid bugs in case the kill switch is pressed
		// if this function were written at the end of the loop block, the motor would lag

	untilBump(resetButton); // waits for the reset button to be pressed after the kill switch has been pressed

	reset(); // reset method

	startTask(main); // restarts the main program

	// a return is not needed, as the startTask() function is the very end of the main method

}

void reset() {

	resetting = true;

	while (SensorValue(motorEncoder) < 0) { // reset operation will run until the spool has completely retracted
		if (SensorValue(killSwitch)) return; // will instantly stop the operation if the kill switch is pressed
		if (SensorValue(motorEncoder) > -100) { // as seen in the retLever loop, this slowing down of the motor
			startMotor(spoolMotor, 24);     // is to avoid inaccurate record bugs
		} else {
			startMotor(spoolMotor, 40);
		}
		update();
	}

	stopMotor(spoolMotor);

	resetting = false;

}

// because the startTask() function is written after both reset() methods, it is impossible for the
// program to bug out if the kill switch is pressed during the reset operation

void update() {

	position = (SensorValue(motorEncoder) / 10) * -1; // encoder to measurement formula
							  // would realistically be more sophisticated and
							  // involve variables like gear ratio and imperial
							  // measurement conversions

}
