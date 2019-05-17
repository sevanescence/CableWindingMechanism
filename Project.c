#pragma config(Sensor, dgtl1,  retLever,    sensorTouch);
#pragma config(Sensor, dgtl2,  outLever,    sensorTouch);
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

		while (SensorValue(retLever)) {
			if (SensorValue(killSwitch)) break;
			startMotor(spoolMotor, 40);
		}

		while (SensorValue(outLever)) {
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
		if (SensorValue(motorEncoder) < -100) {
			startMotor(spoolMotor, 40);
		} else {
			startMotor(spoolMotor, 24);
		}
	}

	stopMotor(spoolMotor);

}
