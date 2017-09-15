/**
 * Automatic waste bin opener.
 *
 * @author Roland Rusch <roland@rusch.lu>
 * @version 0.0.1
 */



#include <Arduino.h>
#include "libraries/Led/Led.h"
#include "libraries/Button/Button.h"


// LED on board
const int pinLed = LED_BUILTIN;
// Arm Potentiometer Input
const int pinArm = A0;
// Arm Move Enable/PWM
const int pinArmEn = 6;
const int pinArm1A = 5;
const int pinArm2A = 4;
// Arm pos0 Input
const int pinArmPos0 = 9;

// Button up Input
const int pinArmUp = 10;
const int pinArmDown = 11;



// Initialize vars
Led led(pinLed);
int armMotorSpeed=0;





//The setup function is called once at startup of the sketch
void setup()
{
	// Add your initialization code here
	led.setup();
	
	
	// Initialize Serial
	Serial.begin(9600);
	Serial.println("GO!");
	
	// Inititalize Arm Motor Pins and Stop Motor
	pinMode(pinArmEn, OUTPUT);
	pinMode(pinArm1A, OUTPUT);
	pinMode(pinArm2A, OUTPUT);
	digitalWrite(pinArmEn, LOW);
	digitalWrite(pinArm1A, LOW);
	digitalWrite(pinArm2A, LOW);
	
	// Initialize Arm Pos0 Pin
	pinMode(pinArmPos0, INPUT);
	
	// Initialize Button Pins
	pinMode(pinArmUp, INPUT);
	pinMode(pinArmDown, INPUT);
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here
	led.update();
	led.setBlinker(200, 200);
	
	int armPotValue=analogRead(pinArm);
	Serial.print("armPotValue=");
	Serial.print(armPotValue);
	
	int armMove=0;
	if(digitalRead(pinArmUp)) armMove++;
	if(digitalRead(pinArmDown)) armMove--;
	
	Serial.print(" | pinArmPos0=");
	Serial.print(digitalRead(pinArmPos0));
	
	Serial.print(" | armMove=");
	Serial.print(armMove);
	
	// Check limits
	if( (armPotValue > 460) && (armMove > 0) ) armMove=0;
	if( (armPotValue < 1) && (armMove < 0) ) armMove=0;
	if( !digitalRead(pinArmPos0) && (armMove < 0) ) armMove=0;
	
	if(armMove == 0)
	{
		armMotorSpeed=0;
		analogWrite(pinArmEn, armMotorSpeed);
		digitalWrite(pinArm1A, LOW);
		digitalWrite(pinArm2A, LOW);
	} else if(armMove > 0) // Arm up
	{
		armMotorSpeed=255; // Full speed
		digitalWrite(pinArm1A, LOW);
		digitalWrite(pinArm2A, HIGH);
		analogWrite(pinArmEn, armMotorSpeed);
	} else if(armMove < 0) // Arm down
	{
		armMotorSpeed=100;
		digitalWrite(pinArm1A, HIGH);
		digitalWrite(pinArm2A, LOW);
		analogWrite(pinArmEn, armMotorSpeed);
	}
	
	
	Serial.print(" | armMotorSpeed=");
	Serial.print(armMotorSpeed);
	
	
	
	Serial.println("");
	delay(200);

}
