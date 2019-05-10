#pragma config(Sensor, dgtl1,  turnLever,    sensorTouch);
#pragma config(Sensor, dgtl2,  backLever,    sensorTouch);
#pragma config(Sensor, dgtl3,  resetButton,  sensorTouch);
#pragma config(Sensor, dgtl4,  killSwitch,   sensorTouch);
#pragma config(Motor,  port1,  spoolMotor,   tmotorVex269_MC29, openLoop);

int position = 0;
int spoolSpeed = 13;

bool checkKillSwitch();
//void reset();
void turnSpool();

task main() {

	while (!checkKillSwitch()) {
		
		turnSpool();
	
	}
	
	untilBump(resetButton);

}

bool checkKillSwitch() {

	if (SensorValue(killSwitch)) return true;
	
	return false;

}

void turnSpool() {

	if (checkKillSwitch() || (SensorValue(turnLever) && SensorValue(backLever))) return;
	
	if (SensorValue(turnLever)) {
	
		position++;
		
		setMotorTarget(spoolMotor, position, spoolSpeed);
	
	}
	
	if (SensorValue(backLever)) {
	
		position--;
		
		setMotorTarget(spoolMotor, (position * -1), (spoolSpeed) * -1);
	
	}

}
