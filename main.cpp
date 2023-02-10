/*****************************
	Programmer...: (C) xVjVx
    Date.........: 07/02/2023
    About........: Alarm
******************************/

const int POWER_LED = 3;
const int POWER_BUTTON = 2;
const int BUZZER = 5;
const int PIR_SENSOR = 4;

const int STANDBY = 0;
const int POWER_ON = 1;
const int ALARM_ON = 2;
const int PIR_DETECT = 3;

const bool DEBUG = true;

int alarmState = STANDBY;

void setup(void) {
  pinMode(POWER_LED, OUTPUT);
  pinMode(POWER_BUTTON, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(PIR_SENSOR, INPUT);
  
  digitalWrite(POWER_LED, LOW);
  
  Serial.begin(9600);
}

void loop(void) {
  switch(alarmState) {
    case STANDBY: {
      if(digitalRead(POWER_BUTTON) == false) {
        alarmState = POWER_ON;
      }
      break;
    }
    case POWER_ON: {
      digitalWrite(POWER_LED, HIGH);
      delay(3000);
      alarmState = ALARM_ON;
      break;
    }
    case ALARM_ON: {
      int sensorPir = digitalRead(PIR_SENSOR);
      
      if(sensorPir == 1) {
        alarmState = PIR_DETECT;
      }
      break;
    }
    case PIR_DETECT: {
       for(int i=700;i<800;i++){
        tone(BUZZER,i);
        delay(15);
      }
      for(int i=800;i>700;i--){
        tone(BUZZER,i);
        delay(15);
      }
     
      noTone(BUZZER);
     
      alarmState = ALARM_ON;
      break;
    }
  }
}