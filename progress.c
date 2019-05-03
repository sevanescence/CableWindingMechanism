#pragma config(Sensor, dgtl1,  wireLever,    sensorTouch);
#pragma config(Sensor, dgtl2,  resetButton,  sensorTouch);
#pragma config(Sensor, dgtl3,  killSwitch,   sensorTouch);
#pragma config(Motor,  port1,  spoolMotor,   tmotorVex269_MC29, openLoop);
#pragma config(Motor,  port2,  displayMotor, tmotorVex269_MC29, openLoop);

const int MotorSpeed = 1;

bool running = true;
int position = 0;

void turnSpool(int motorSpeed);
void reset(int motorSpeed);

task main() {

	while (running) {
		
		if (SensorValue(killSwitch)) {
			
			running = false;
			
			break;
		
		}
		
		turnSpool(MotorSpeed);
	
	}

}

void turnSpool(int motorSpeed) {
	
	if (SensorValue(killSwitch)) {
		
		running = false;
		
		return;
	
	}
	
	if (SensorValue(wireLever)) {
		
		position += motorSpeed;
		
		setMotorTarget(spoolMotor, position);
	
	}

}

void reset(int motorSpeed) {
	
	return;

}
