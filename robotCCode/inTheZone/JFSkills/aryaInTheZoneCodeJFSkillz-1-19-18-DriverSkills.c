#pragma config(Sensor, in1,    baseGyro,       sensorGyro)
#pragma config(Sensor, in3,    mogoPot,        sensorPotentiometer)
#pragma config(Sensor, in4,    gyro,           sensorGyro)
#pragma config(Sensor, in5,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, in6,    clawPot,        sensorPotentiometer)
#pragma config(Sensor, in7,    vbPot,          sensorPotentiometer)
#pragma config(Sensor, in8,    navPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,  ,               sensorTouch)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,           mogo1,         tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           frontRight2,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           rightMiddle,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rightBack,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           leftBack,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           leftMiddle,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           frontLeft2,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           frontLeft,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          mogo2,         tmotorVex393_HBridge, openLoop)
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

void Kill()//Kills power
{
	motor[mogo1] = 0;
	motor[frontRight] = 0;
	motor[frontRight2] = 0;
	motor[rightMiddle] = 0;
	motor[rightBack] = 0;
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[frontLeft2] = 0;
	motor[frontLeft] = 0;
	motor[mogo2] = 0;
}

//-----MOTOR_CONNECTION_FUNCTIONS-----//
void leftBase(int power)//Function used to control all the motors on the left side of the base at once.
{
	motor[frontLeft] = power;
	motor[frontLeft2] = power;
	motor[leftMiddle] = power;
	motor[leftBack] = power;
}

void rightBase(int power)//Function used to control all the motors on the right side of the base at once.
{
	motor[frontRight] = power;
	motor[frontRight2] = power;
	motor[rightMiddle] = power;
	motor[rightBack] = power;
}

void baseDriver(int leftSpeed, int rightSpeed)//Function to control base during driver control
{
	leftBase(-leftSpeed);
	rightBase(rightSpeed);
}
void base(int rSpeed, int lSpeed){
	baseDriver(lSpeed, rSpeed);}

void clearEncoders()
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
}

void fwds(int distance, int speed, int brake, int wait, int timer)
{
	clearTimer(T2);
	clearEncoders();
	while(abs(SensorValue[leftEncoder]) < distance && time1[T2] < timer)
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

void turnRightEncoder(int distance, int speed, int brake, int wait)
{
	SensorValue[leftEncoder] = 0;
	//RIGHT
	while(abs(SensorValue[leftEncoder]) <= distance)
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

void turnLeftEncoder(int distance, int speed, int brake, int wait)
{
	SensorValue[leftEncoder] = 0;
	//LEFT
	while(abs(SensorValue[leftEncoder]) <= distance)
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

void mogoOut(int potValue, int speed, int hold)
{
	clearTimer(T2);
	while(SensorValue[mogoPot] >= potValue && time1[T2] < 3000)
	{
		motor[mogo1] = -speed;
		motor[mogo2] = -speed;
	}
	motor[mogo1] = 0;//change to hold if needed
	motor[mogo2] = 0;//change to hold if needed
}

void mogoIn(int potValue, int speed, int hold)
{
	clearTimer(T2);
	while(SensorValue[mogoPot] <= potValue && time1[T2] < 3000)
	{
		motor[mogo1] = speed;
		motor[mogo2] = speed;
	}
	motor[mogo1] = 0;//change to hold if needed
	motor[mogo2] = 0;//change to hold if needed
}

void autonRun();
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------Pre-Autonomous Functions----------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void pre_auton()
{
	SensorValue[gyro] = 0;
	SensorValue[baseGyro] = 0;
	clearEncoders();
	clearTimer(T1);
}
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                           */
/*                                                              Autonomous Task                                                              */
/*                                                                                                                                           */
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
task autonomous()
{
	fwds(400, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
	wait1Msec(1000);
	turnRightEncoder(620, 127, 0, 100);//(distance, speed, brake, wait)
	fwds(200, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
	turnLeftEncoder(620, 127, 0, 100);//(distance, speed, brake, wait)
	mogoOut(2000, 127, 0);//(potValue, speed, hold)
	fwds(200, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
	mogoIn(4090, 127, 0);//(potValue, speed, hold)
	bwds(400, 127, 10, 0, 3000);//(distance, speed, brake, wait, timer)
}
/////////////////////////////////////////////////////////////////////////////////

void mobileGoal()//Function used to control all the motors on the lift at once.
{
	if(vexRT[Btn6U] == 1)
	{
		motor[mogo2] = 127;
		motor[mogo1] = 127;
	}
	else if(vexRT[Btn6D] == 1)
	{
		motor[mogo2] = -127;
		motor[mogo1] = -127;
	}
	else
	{
		motor[mogo2] = 0;
		motor[mogo1] = 0;
	}
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/
task usercontrol()
{
	bLCDBacklight = false;
	SensorValue[gyro] = 0;
	clearEncoders();
	clearTimer(T1);
	while (true)
	{
		baseDriver(vexRT[Ch3], vexRT[Ch2]);
		mobileGoal();
	}
}