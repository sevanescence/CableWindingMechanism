#pragma config(Sensor, dgtl1,  backLever,    sensorTouch);
#pragma config(Sensor, dgtl2,  turnLever,    sensorTouch);
#pragma config(Sensor, dgtl3,  resetButton,  sensorTouch);
#pragma config(Sensor, dgtl4,  killSwitch,   sensorTouch);
#pragma config(Sensor, dgtl11, motorEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,  spoolMotor,   tmotorVex269_MC29, openLoop);

void reset();
task main() {

	while (!SensorValue(killSwitch)) {

		stopMotor(spoolMotor);

		if (SensorValue(resetButton)) {
			reset();
			startTask(main);
			return;
		}

		while (SensorValue(backLever)) {
			if (SensorValue(killSwitch)) break;
			startMotor(spoolMotor, 40);
		}

		while (SensorValue(turnLever)) {
			if (SensorValue(killSwitch)) break;
			startMotor(spoolMotor, -40);
		}

	} stopMotor(spoolMotor);

	untilBump(resetButton);

	reset();

	startTask(main);

}

void reset() {

	while (SensorValue(motorEncoder) < 0) {
		if (SensorValue(killSwitch)) return;
		startMotor(spoolMotor, 40);
	}

	stopMotor(spoolMotor);

}
