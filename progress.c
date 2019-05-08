#pragma config(Sensor, dgtl1,  turnLever,    sensorTouch);
#pragma config(Sensor, dgtl2,  backLever,    sensorTouch);
#pragma config(Sensor, dgtl3,  resetButton,  sensorTouch);
#pragma config(Sensor, dgtl4,  killSwitch,   sensorTouch);
#pragma config(Motor,  port1,  spoolMotor,   tmotorVex269_MC29, openLoop);

int position = 0;

bool checkKillSwitch();
//void reset();
void turnSpool();

task main() {
	
	setMotorTarget(spoolMotor, 0);

	while (true) {
	
		if (checkKillSwitch()) break;
		
		turnSpool();
	
	}

}

bool checkKillSwitch() {

	if (SensorValue(killSwitch)) return true;
	
	return false;

}

void turnSpool() {

	if (checkKillSwitch()) return;
	
	setMotorTarget(spoolMotor, position);
	
	position++;

}
