#include <stdio.h>
#include <AFMotor.h> 

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

unsigned long time;
int forwardSpeed = 0;

int x=0;
int y=0;
int z=0;

void setup() {
	Serial.begin(115200);
	Serial.println("OK");
}

char command[1024];
char commandBuffer[128];
int commandBufferSize = 0;

void readCommandBuffer(int bytesToRead) {
	int i = 0;
	char c = 0;
	while (i < 128 && (i < bytesToRead || bytesToRead <= 0)) {
		while (!Serial.available());
		c = Serial.read();
		if (c == '\r' || c == '\n') {
			break;
		}
		commandBuffer[i] = c;
		i++;
	}
	commandBufferSize = i;
}

void readCommand() {
	command[0] = '\0';
	readCommandBuffer(0);
	if (strncmp(commandBuffer, "RCV", 3) == 0) {
		commandBuffer[commandBufferSize] = '\0';
		int expectedSize = atoi(commandBuffer + 4);
		if (expectedSize <= 0 || expectedSize > 1024) {
			return;
		}
		Serial.println("RDY");
		int bytesRead = 0;
		while (bytesRead < expectedSize) {
			readCommandBuffer(expectedSize - bytesRead);
			memcpy(command + bytesRead, commandBuffer, commandBufferSize);
			bytesRead += commandBufferSize;
			Serial.print("ACK ");
			Serial.println(commandBufferSize);
		}
		command[bytesRead] = '\0';
	} else {
		memcpy(command, commandBuffer, commandBufferSize);
		command[commandBufferSize] = '\0';
	}
}

 String getValue(String data, char separator, int index) 
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void cmdCVRT(String input){
  String split = input;
  String val1 = getValue(split, ',', 0);
  String val2 = getValue(split, ',', 1);
  String val3 = getValue(split, ',', 2);
  x = val1.toInt();
  y = val2.toInt();
  z = val3.toInt();
}

void loop() {
    int fieldIndex = 0;            // the current field being received

	if (Serial.available()) {
		readCommand();
                cmdCVRT(command);
//                String split = command;
//                String word3 = getValue(split, ',', 0);
                Serial.println(command);
//                Serial.println(x);
//                Serial.println(y);
//                Serial.println(z);
   dirX(255,x);
   dirY(255,y);
   dirZ(255,z);   
//   stopAll(x,y,z);
//if (z == 1){
//  Serial.
//}
	}
}

void dirX(int Speed, int dir){
    if (dir == 1){
    MSpeedAll(Speed);
    Right();
    Serial.print("  RIGHT ENGAGED");
  }
    if (dir == -1){
    MSpeedAll(Speed);
    Left();
    Serial.print("  LEFT ENGAGED");
  }
    if (dir == 0){
  }
}

void dirY(int Speed, int dir){
   if (dir == 1){
    MSpeedAll(Speed);
    Forward();
    Serial.print("  FORWARD ENGAGED");
  }
    if (dir == -1){
    MSpeedAll(Speed);
    Backward();
    Serial.print("  BACKWARD ENGAGED");
  }
    if (dir == 0){
  }
}

void dirZ(int Speed, int dir){ 
     if (dir == 1){
    MSpeedAll(Speed);
    RotRight();
    Serial.print("  ROT-RIGHT ENGAGED");
  }
    if (dir == -1){
    MSpeedAll(Speed);
    RotLeft();
    Serial.print("  ROT-LEFT ENGAGED");
  }
    if (dir == 0){
  }
}

void stopAll(int dirX, int dirY, int dirZ){
  if (dirX == 0){
    if (dirY == 0){
      if (dirZ == 0){
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
}
    }
  }
}
int MSpeedAll(int x){
  motor1.setSpeed(x);
  motor2.setSpeed(x);
  motor3.setSpeed(x);
  motor4.setSpeed(x);
}
int Forward(){
  motor1.run(FORWARD);
//  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
//  motor4.run(FORWARD);
}
int Backward(){
  motor1.run(BACKWARD);
//  motor2.run(FORWARD);
  motor3.run(FORWARD);
//  motor4.run(BACKWARD);
}
int Right(){
  motor1.run(FORWARD);
//  motor2.run(FORWARD);
  motor3.run(BACKWARD);
//  motor4.run(BACKWARD);
}
int Left(){
  motor1.run(BACKWARD);
//  motor2.run(BACKWARD);
  motor3.run(FORWARD);
//  motor4.run(FORWARD);
}
int RotRight(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
int RotLeft(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

