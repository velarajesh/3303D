#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in2,    navPot,         sensorPotentiometer)
#pragma config(Sensor, in3,    mogoPot,        sensorPotentiometer)
#pragma config(Sensor, in4,    baseGyro,       sensorGyro)
#pragma config(Sensor, in5,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, in6,    clawPot,        sensorPotentiometer)
#pragma config(Sensor, in7,    vbPot,          sensorPotentiometer)
#pragma config(Sensor, in8,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  towerPing,      sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl12, button,         sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           intake,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           mobileRight,   tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port3,           rightFrontBase, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           leftFrontBase, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftBackBase,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rightBackBase, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           mobileLeft,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          elevator,      tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
bool LCDState = false;
string mainBattery, backupBattery;


//Default AUTON Number//
// RED  POLE     == 0 //
// RED  RIGHT1   == 1 //
// RED  LEFT1    == 2 //
// Defence     == 3 //
// BLUE RIGHT1   == 4 //
// BLUE LEFT1    == 5 //
// SKILLS        == 6 //
// BLUE RIGHT2   == 7  v         //
// RED  RIGHT2   == 8 //
// Resistance Block    == 9 //
// RED  LEFT2    == 10//
int autonNum = 10;
//Default AUTON Number//

//Variables
int stateCheck = 0;
int soundCheck = 0;



void Kill()//Kills power
{
	motor[intake] = 0;
	motor[mobileRight] = 0;
	motor[rightFrontBase] = 0;
	motor[leftFrontBase] = 0;
	motor[rightLift] = 0;
	motor[leftLift] = 0;
	motor[leftBackBase] = 0;
	motor[rightBackBase] = 0;
	motor[mobileLeft] = 0;
	motor[elevator] = 0;
}

void clearLCD()//Clear both LCD lines
{
	clearLCDLine(0);
	clearLCDLine(1);
}

void clearSound(int time)//Stop playing sounds after (int time) seconds
{
	wait1Msec(time);
	clearSounds();
}

void testSound()//Sound function for determining if blip sound was played while using LCD
{
	if(stateCheck != soundCheck)//If sound was not played then play sound
	{
		playSound(soundShortBlip);
		soundCheck = stateCheck;
	}
	else//No sound if sound was already played
	{
		wait1Msec(100);
		clearSounds();
	}
}

void LCDRun()//Main LCD function
{
	if(nLCDButtons == leftButton)//Turns on the LCD
	{
		LCDState = true;
		playSound(soundUpwardTones);
		bLCDBacklight = true;
		clearSound(500);
	}
	if(LCDState == true)
	{
		if(SensorValue[navPot] <= 500)//RED POLE == 0
		{
			testSound();
			stateCheck = 0;
			displayLCDCenteredString(0,"==              ");
			displayLCDCenteredString(1,"    RED POLE   >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 0;
				displayLCDCenteredString(0,"----RED POLE----");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(1500);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else if(SensorValue[navPot] >= 500 && SensorValue[navPot] <= 1000)//RED RIGHT == 1
		{
			testSound();
			stateCheck = 1;
			displayLCDCenteredString(0,"  ==            ");
			displayLCDCenteredString(1,"<  RED  RIGHT  >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 1;
				displayLCDCenteredString(0,"---RED  RIGHT---");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(1500);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else if(SensorValue[navPot] >= 1000 && SensorValue[navPot] <= 1500)//RED LEFT == 2
		{
			stateCheck = 2;
			testSound();
			displayLCDCenteredString(0,"    ==          ");
			displayLCDCenteredString(1,"<   RED LEFT   >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 2;
				displayLCDCenteredString(0,"----RED LEFT----");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(1500);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else if(SensorValue[navPot] >= 1500 && SensorValue[navPot] <= 2000)//BLUE POLE == 3
		{
			stateCheck = 3;
			testSound();
			displayLCDCenteredString(0,"      ==        ");
			displayLCDCenteredString(1,"<  BLUE  POLE  >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 3;
				displayLCDCenteredString(0,"---BLUE  POLE---");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(1500);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else if(SensorValue[navPot] >= 2000 && SensorValue[navPot] <= 2500)//BLUE RIGHT == 4
		{
			stateCheck = 4;
			testSound();
			displayLCDCenteredString(0,"        ==      ");
			displayLCDCenteredString(1,"<  BLUE RIGHT  >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 4;
				displayLCDCenteredString(0,"---BLUE RIGHT---");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(2000);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else if(SensorValue[navPot] >= 2500 && SensorValue[navPot] <= 3000)//BLUE LEFT == 5
		{
			stateCheck = 5;
			testSound();
			displayLCDCenteredString(0,"          ==    ");
			displayLCDCenteredString(1,"<  BLUE  LEFT  >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 5;
				displayLCDCenteredString(0,"---BLUE  LEFT---");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(2000);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else if(SensorValue[navPot] >= 3000 && SensorValue[navPot] <= 3500)//SKILLS == 6
		{
			stateCheck = 6;
			testSound();
			displayLCDCenteredString(0,"            ==  ");
			displayLCDCenteredString(1,"<    SKILLS    >");
			if(nLCDButtons == centerButton)
			{
				autonNum = 6;
				displayLCDCenteredString(0,"-----SKILLS-----");
				displayLCDCenteredString(1,"   *SELECTED*   ");
				playSound(soundException);
				clearSound(500);
				wait1Msec(2000);
				LCDState = false;
				playSound(soundDownwardTones);
				clearSound(500);
			}
		}
		else//Check Battery Voltage
		{
			stateCheck = 7;
			testSound();
			displayLCDCenteredString(0,"              ==");
			displayLCDCenteredString(1,"<    BATTERY    ");
			while(nLCDButtons == centerButton)
			{
				displayLCDString(0,0,"  Primary: ");
				sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
				displayNextLCDString(mainBattery);
				displayLCDCenteredString(1," ");
			}

		}
		if(nLCDButtons == rightButton)
		{
			LCDState = false;
			playSound(soundDownwardTones);
			wait1Msec(500);
			clearSounds();
		}
	}
	else
	{
		clearLCD();
		bLCDBacklight = false;
	}
}




//-----MOTOR_CONNECTION_FUNCTIONS-----//
void leftBase(int power)//Function used to control all the motors on the left side of the base at once.
{
	motor[leftFrontBase] = power;
	motor[leftBackBase] = power;
}

void rightBase(int power)//Function used to control all the motors on the right side of the base at once.
{
	motor[rightFrontBase] = power;
	motor[rightBackBase] = power;
}

void mobileGoal()//Function used to control all the motors on the lift at once.
{
	if (vexRT[Btn7U] == 1)
	{
		motor[mobileRight] = 127;
		motor[mobileLeft] = 127;
	}
	else if(vexRT[Btn7D] == 1)
	{
		motor[mobileRight] = -127;
		motor[mobileLeft] = -127;
	}
	else
	{
		motor[mobileRight] = 0;
		motor[mobileLeft] = 0;
	}
}

void liftControl(int power)//Function used to control all the motors on the lift at once.
{
	motor[rightLift] = power;
	motor[leftLift] = power;
}

//-----MOTOR_CONNECTION_FUNCTIONS-----//


void baseDriver(int leftSpeed, int rightSpeed)//Function to control base during driver control
{
	leftBase(leftSpeed);
	rightBase(rightSpeed);
}

void clawMove(int openSpeed, int closeSpeed, int hold)//try using sometime
{

	if(vexRT[Btn6U] == vexRT[Btn6D])
	{
		motor[intake] = hold;
	}
	else if(vexRT[Btn6U] == 1 && SensorValue[clawPot] >= 2400)
	{
		motor[intake] = openSpeed;
	}
	else if(vexRT[Btn6D] == 1  && SensorValue[clawPot] <= 3000)
	{
		clearTimer(T3);
		if(time1[T3] < 1000)
		{
			motor[intake] = closeSpeed;
		}
	}
	else
	{
		motor[intake] = (hold - 10);
	}

}

void base(int rSpeed, int lSpeed)
{
	rightBase(rSpeed);
	leftBase(lSpeed);
}

//********************************************************************************************************//
//********************************************AUTON_FUNCTIONS*********************************************//
//********************************************************************************************************//

void clearEncoders()
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
}


void fwds(int distance, int speed, int brake, int wait, int timer)
{
	clearTimer(T2);
	clearEncoders();
	while(abs(SensorValue[rightEncoder]) < distance && time1[T2] < timer)
	{
		base(speed,speed);
	}
	if(brake != 0)
	{
		base(-brake,-brake);
		wait1Msec(100);
	}
	base(0,0);
	wait1Msec(wait);
}

void bwds(int distance, int speed, int brake, int wait, int timer)
{
	fwds(distance, -speed, brake, wait, timer);
}

void bwdsT(int time, int speed, int wait)
{
	base(-speed,-speed);
	wait1Msec(time);
	base(0,0);
	wait1Msec(wait);
}

void fwdsT(int time, int speed, int wait)
{
	bwdsT(time,-speed,wait);
}

void turnRight(int distance, int speed, int brake, int wait)
{
	SensorValue[baseGyro] = 0;
	//RIGHT
	while(abs(SensorValue[baseGyro]) <= distance)
	{
		base((-speed),(speed));
	}
	if(brake != 0)
	{
		base(brake,-brake);
		wait1Msec(100);
	}
	base(0,0);
	wait1Msec(wait);
}

void turnLeft(int distance, int speed, int brake, int wait)
{
	SensorValue[baseGyro] = 0;
	//LEFT
	while(abs(SensorValue[baseGyro]) <= distance)
	{
		base((speed),(-speed));
	}
	if(brake != 0)
	{
		base(-brake,brake);
		wait1Msec(100);
	}
	base(0,0);
	wait1Msec(wait);
}

void clawOpen(int potValue, int speed, int hold)
{
	while(SensorValue[clawPot] >= potValue)
	{
		motor[intake] = speed;
	}
	motor[intake] = hold;
}

void clawClose(int potValue, int speed, int hold)
{
	while(SensorValue[clawPot] <= potValue)
	{
		motor[intake] = -speed;
	}
	motor[intake] = -hold;
}

void liftUp(int potValue, int speed, int hold, int wait, int timer)
{
	clearTimer(T2);
	while(SensorValue[liftPot] >= potValue && time1[T2] < timer)
	{
		liftControl(-speed);
	}
	liftControl(hold);
	wait1Msec(wait);
}

void liftDown(int potValue, int speed, int hold, int wait, int timer)
{
	clearTimer(T2);
	while(SensorValue[liftPot] >= potValue && time1[T2] < timer)
	{
		liftControl(-speed);
	}
	liftControl(-hold);
	wait1Msec(wait);
}

void mogoOut2(int potValue, int speed, int hold)
{
	while(getMotorEncoder(mobileRight) < potValue)
	{
		motor[mobileLeft] = (-speed);
		motor[mobileRight] = (-speed);
	}
	motor[mobileLeft] = 0;
	motor[mobileRight] = 0;
}

void mogoIn2(int potValue, int speed, int hold)
{
	while(SensorValue[button] != 1)
	{
		motor[mobileLeft] = speed;
		motor[mobileRight] = speed;
	}
	resetMotorEncoder(mobileRight);
	motor[mobileLeft] = 0;
	motor[mobileRight] = 0;
}

void vbDown(int potValue, int speed, int hold)
{
	while(SensorValue[vbPot] >= potValue)
	{
		motor[mobileLeft] = (-speed);
		motor[mobileRight] = (-speed);
	}
}

void vbUp(int potValue, int speed, int hold)
{
	while(SensorValue[vbPot] <= potValue)
	{
		motor[mobileLeft] = speed;
		motor[mobileRight] = speed;
	}
}
void tipWarning()
{

	while(SensorValue[gyro] <= -70 && SensorValue[liftPot] < 1200)
	{
		playSound(soundBeepBeep);
		wait1Msec(100);
		base(127, 127);
		liftControl(-127);
		if(vexRT[Btn7R] == 1)
		{
			SensorValue[gyro] = 0;
		}
	}

	while(SensorValue[gyro] >= 80 && SensorValue[liftPot] < 1200)
	{
		playSound(soundBeepBeep);
		wait1Msec(100);
		base(-127, -127);
		liftControl(-127);
		if(vexRT[Btn7R] == 1)
		{
			SensorValue[gyro] = 0;
		}
	}

	if(time1[T1] >= 5000)
	{
		SensorValue[gyro] = 0;
		clearTimer(T1);
	}
	if(vexRT[Btn7R] == 1)
	{
		SensorValue[gyro] = 0;
	}
}





void autonRun();
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------Pre-Autonomous Functions----------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void pre_auton()
{
	clearLCD();
	SensorValue[gyro] = 0;
	clearEncoders();
	clearTimer(T1);
	LCDRun();
	resetMotorEncoder(mobileRight);
}
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                           */
/*                                                              Autonomous Task                                                              */
/*                                                                                                                                           */
/*-------------------------------------------------------------------------------------------------------------------------------------------*/


// RED  POLE     == 0 //
// RED  RIGHT1   == 1 //
// RED  LEFT1    == 2 //
// BLUE POLE     == 3 //
// BLUE RIGHT1   == 4 //
// BLUE LEFT1    == 5 //
// SKILLS        == 6 //
// BLUE RIGHT2   == 7 //
// RED  RIGHT2   == 8 //
// BLUE LEFT2    == 9 //
// RED  LEFT2    == 10//

task autonomous()
{
	autonRun();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/
task usercontrol()
{
	bLCDBacklight = false;
	clearLCD();
	SensorValue[gyro] = 0;
	clearEncoders();
	clearTimer(T1);
	while (true)
	{
		baseDriver(vexRT[Ch3], vexRT[Ch2]); //void base(int leftSpeed, int rightSpeed); //Function to control base during driver control
		mobileGoal();//Function used to control all the motors on the lift at once.
		tipWarning();
		if(vexRT[Btn6D] == 1)
		{
			motor[intake] = 127;
		}
		else if(vexRT[Btn6U] == 1)
		{
			motor[intake] = -127;
		}
		else
		{
			motor[intake] = 10;
		}

		if(vexRT[Btn5D] == 1)
		{
			motor[leftLift] = -127;
			motor[rightLift] = -127;
		}
		else if(vexRT[Btn5U] == 1)
		{
			motor[leftLift] = 127;
			motor[rightLift] = 127;
		}
		else
		{
			motor[leftLift] = 15;
			motor[rightLift] = 15;
		}


		if(vexRT[Btn8D] == 1)
		{
			motor[elevator] = -127;
		}
		else if(vexRT[Btn8U] == 1)
		{
			motor[elevator] = 127;
		}
		else if(vexRT[Btn8R]) //DOWN
		{
			int timer = 2000;
			clearTimer(T3);
			if(SensorValue[vbPot] <= 350 || SensorValue[vbPot] <= 1700)
			{
				while(SensorValue[vbPot] <= 1700 && time1[T3] < timer)
				{
					motor[elevator] = -127;
				}
				motor[elevator] = 10;
			}
			else if(SensorValue[vbPot] <= 1700 || SensorValue[vbPot] <= 2600)
			{

				while(SensorValue[vbPot] <= 2600 && time1[T3] < timer)
				{
					motor[elevator] = -127;
				}
				motor[elevator] = 10;
			}
			else
			{
				motor[elevator] = 10;
			}
		}
		else if(vexRT[Btn8L])//UP
		{
			int timer = 1000;
			clearTimer(T3);
			if(SensorValue[vbPot] >= 2600 || SensorValue[vbPot] >= 1900)
			{
				while(SensorValue[vbPot] >= 1900 && time1[T3] < timer)
				{
					motor[elevator] = 127;
				}
				motor[elevator] = 10;
			}
			else if(SensorValue[vbPot] >= 1700 || SensorValue[vbPot] >= 350)
			{
				while(SensorValue[vbPot] >= 400 && time1[T3] < timer)
				{
					motor[elevator] = 127;
				}
				motor[elevator] = 10;
			}
			else
			{
				motor[elevator] = 10;
			}
		}
		else
		{
			motor[elevator] = 10;
		}
	}
}

void autonRun()
{
	if(autonNum == 0)//---RED_POLE---//
	{
		clawClose(3100, -127, -10);//(potValue, speed, hold)
		//vbUp();
		liftUp(1150, -127, 40, 1000, 30000);
		fwds(1400, 80, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		liftDown(1580, -127, 40, 1000, 3000);
		clawOpen(2575, -127, -15);//(potValue, speed, hold)
		turnLeft(400, 127, 5, 300);
		bwds(1000, 127, 10, 250, 3000);//(distance, speed, brake, wait, timer)
	}
	else if(autonNum == 1)//---RED_RIGHT_10_POINT---//
	{

	}
	else if(autonNum == 2)//---RED_LEFT_10_POINT---//
	{

	}
	else if(autonNum == 3)//---Blue_Left_20_Point---//
	{

	}
	else if(autonNum == 4)//---BLUE_RIGHT_10_POINT---//
	{

	}
	else if(autonNum == 5)//---BLUE_LEFT_10_POINT---//
	{

	}
	else if(autonNum == 6)//---SKILLS---//
	{

	}
	else if(autonNum ==7) //---BLUE_RIGHT_20_POINT---//
	{
		clawClose(3100, -127, -10);//(potValue, speed, hold)
		//vbUp();
		mogoOut2(4, 127, 0);//(potValue, speed, hold)
		fwds(2500, 80, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		mogoIn2(1410, 127, 0);//(potValue, speed, hold)
		clawOpen(2575, -127, -15);//(potValue, speed, hold)
		bwds(2100, 70, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnLeft(750, 80, 10, 100);//(distance, speed, brake, wait)
		fwds(900, 70, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		turnLeft(400, 80, 10, 100);//(distance, speed, brake, wait)
		fwds(1200, 70, 10, 250, 3000);//(distance, speed, brake, wait, timer)
		mogoOut2(300, 127, 0);//(potValue, speed, hold)
		mogoIn2(1300, 127, 0);//(potValue, speed, hold)
		bwds(900, 70, 10, 250, 3000);//(distance, speed, brake, wait, timer)
	}
	else if(autonNum ==8) //---RED_RIGHT_20_POINT---//
	{

	}
	else if(autonNum == 9)//---Resistance_Block---//
	{

	}
	else if(autonNum == 10)//---RED_LEFT_20_POINT---//
	{
		mogoOut2(1290, 127, 0);//(potValue, speed, hold)
	}
}