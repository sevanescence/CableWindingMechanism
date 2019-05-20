#pragma config(Sensor, dgtl1,  retLever,    sensorTouch);
#pragma config(Sensor, dgtl2,  outLever,    sensorTouch);
#pragma config(Sensor, dgtl3,  resetButton,  sensorTouch);
#pragma config(Sensor, dgtl4,  killSwitch,   sensorTouch);
#pragma config(Sensor, dgtl11, motorEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,  spoolMotor,   tmotorVex269_MC29, openLoop);

task main() {

  while (!SensorValue(killSwitch) {
  
    if (SensorValue(retLever)) {
    
      startMotor(spoolMotor, 40);
    
    }
    
    if (SensorValue(outLever)) {
    
      startMotor(spoolMotor, -40);
    
    }
    
    stopMotor(spoolMotor);
  
  } // end of killSwitch while loop

} // end of main task
