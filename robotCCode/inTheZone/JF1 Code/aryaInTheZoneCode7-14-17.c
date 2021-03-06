#pragma config(Sensor, in1,    clawPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, dgtl9,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl11, rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,           claw,          tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           leftFront,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftMiddle,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           leftBack,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           liftOne,       tmotorNone, openLoop)
#pragma config(Motor,  port6,           liftTwo,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rightFront,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightMiddle,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           rightBack,     tmotorVex393_MC29, openLoop, reversed)
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

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/



//********************************************************************************************************//
//********************************************AUTON_FUNCTIONS*********************************************//
//********************************************************************************************************//
//---Base---//:Controls the speed of the base motors.
/*
void base(int rSpeed, int lSpeed)
{
rightBase(rSpeed);
leftBase(lSpeed);
}

//---Turn---//:Turns robot to a given angle at a given speed.
void turn(int distance, int speed, bool direction, int brake, int wait)
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
	if(direction == 0)
	{
		while(SensorValue[leftEncoder] <= distance || SensorValue[rightEncoder] <= distance)
		{
			base((-speed),(speed));
		}
		if(brake != 0)
		{
			base(-direction * brake,direction * brake);
			wait1Msec(100);
		}
		base(0,0);
		wait1Msec(wait);
	}
	else
	{
		while(SensorValue[leftEncoder] >= -distance || SensorValue[rightEncoder] >= -distance)
		{
			base((speed),(-speed));
		}
		if(brake != 0)
		{
			base(-direction * brake,direction * brake);
			wait1Msec(100);
		}
		base(0,0);
		wait1Msec(wait);
	}

}



//---Swing---//:Turns using only one side of the base.
void swing(int distance, int speed, int direction, int brake, int wait)
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
	if(direction > 0)
	{
		while(direction * SensorValue[rightEncoder] < distance)
		{
			base(direction * speed,-10);
		}
		if(brake != 0)
		{
			base(-brake,0);
			wait1Msec(200);
		}
	}
	else
	{
		while(direction * SensorValue[leftEncoder] < distance)
		{
			base(-10,-direction * speed);
		}
		if(brake != 0)
		{
			base(0,-brake);
			wait1Msec(200);
		}
	}

	base(0,0);
	wait1Msec(wait);
}

void swingB(int distance, int speed, int direction, int brake, int wait)
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
	if(direction > 0)
	{
		while(direction * SensorValue[leftEncoder] < distance)
		{
			base(10,-direction * speed);
		}
		if(brake != 0)
		{
			base(0,brake);
			wait1Msec(200);
		}
	}
	else
	{
		while(direction * SensorValue[rightEncoder] <distance)
		{
			base(direction * speed,10);
		}
		if(brake != 0)
		{
			base(brake,0);
			wait1Msec(200);
		}
	}

	base(0,0);
	wait1Msec(wait);
}

//---Forwards/Backwards---//:Moves the base forward and backward using IME's.
void fwds(int distance, int speed, int brake, int wait, int timer)
{
	clearTimer(T2);
	SensorValue[rightEncoder] = 0;
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

void stopBase()
{
	motor[leftBackBase] = 0;
	motor[leftFrontBase] = 0;
	motor[rightBackBase] = 0;
	motor[rightFrontBase] = 0;
}

*/
task autonomous()
{
	/*
	while(SensorValue[liftPot] <= 2000)
	{
	motor[bottomLift] = 80;
	motor[topRightLift] = 80;
	motor[topLeftLift] = 80;
	}
	motor[bottomLift] = 10;
	motor[topRightLift] = 10;
	motor[topLeftLift] = 10;


	while(SensorValue[mobileReset] == 0)
	{
	motor[mobileGoalIntake] = -127;
	}
	motor[mobileGoalIntake] = 0;
	SensorValue[mobileEncoder] = 0;
	SensorValue[mobileIndicator] = 1;
	wait1Msec(500);

	fwds(375, 65, 1, 500, 3000);

	while (SensorValue[liftPot] >= 1800)
	{
	motor[bottomLift] = -80;
	motor[topRightLift] = -80;
	motor[topLeftLift] = -80;
	}
	motor[bottomLift] = 15;
	motor[topRightLift] = 15;
	motor[topLeftLift] = 15;

	motor[claw] = 30;
	wait10Msec(1000);
	/*
	while(SensorValue[mobileEncoder] >= -150)
	{
	motor[mobileGoalIntake] = 25;
	}
	motor[mobileGoalIntake] = 0;


	bwds(1000, 90, 10, 500, 3000);
	bwds(350, 110, 10, 500, 3000);

	while(SensorValue[mobileReset] == 0)
	{
	motor[mobileGoalIntake] = -127;
	}
	motor[mobileGoalIntake] = 0;
	wait1Msec(500);

	fwds(925, 80, 10, 500, 3000);
	turn(130, 75, 0, 10, 500);

	fwds(550, 80, 10, 500, 3000);

	turn(180, 75, 0, 10, 500);

	fwds(300, 80, 10, 500, 3000);

	SensorValue[mobileEncoder] = 0;
	while(SensorValue[mobileEncoder] >= -150)
	{
	motor[mobileGoalIntake] = 127;
	}
	motor[mobileGoalIntake] = -15;
	bwds(400, 90, 10, 500, 3000);
	while(SensorValue[mobileEncoder] >= -180)
	{
	motor[mobileGoalIntake] = 127;
	}
	motor[mobileGoalIntake] = 0;
	fwds(30, 80, 10, 500, 2000);

	while(SensorValue[mobileReset] == 0)
	{
	motor[mobileGoalIntake] = -127;
	}
	motor[mobileGoalIntake] = 0;
	fwds(600, 75, 10, 500, 3000);
	*/
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void leftBase(int power)
{
	motor[leftFront] = power;
	motor[leftMiddle] = power;
	motor[leftBack] = power;
}
void rightBase(int power)
{
	motor[rightFront] = power;
	motor[rightMiddle] = power;
	motor[rightBack] = power;
}

void liftControl(int power)
{
	motor[liftOne] = power;
	motor[liftTwo] = power;
}
void base(bool setting, int duration, int speedLeft, int speedRight)//function to control base during auton and driver
{
	if(setting == 0) //Driver Code
	{
		leftBase( vexRT[Ch3]);
		rightBase(vexRT[Ch2]);
	}
	else
	{

	}
}

void lift(int upSpeed, int downSpeed, int hold)
{
	if(vexRT[Btn5U] == 1 && SensorValue[liftPot] <= 3200)
	{
		liftControl(upSpeed);
	}
	else if(vexRT[Btn5D] == 1 && SensorValue[liftPot] >= 1100)
	{
		liftControl(downSpeed);
	}
	else
	{

		if(SensorValue[liftPot] <= 1400)
		{
			liftControl(hold-10);
		}
		else
		{
			liftControl(hold);
		}
	}
}

void clawMove(int openSpeed, int closeSpeed, int hold)
{
	if(vexRT[Btn6U] == vexRT[Btn6D])
	{
		motor[claw] = hold;
	}
	else if(vexRT[Btn6U] == 1 && SensorValue[clawPot] >= 2400)
	{
		motor[claw] = openSpeed;
	}
	else if(vexRT[Btn6D] == 1  && SensorValue[clawPot] <= 3000)
	{
		motor[claw] = closeSpeed;
	}
}



task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
		base(0,0,0,0); //base(bool setting, int speed, int duration,int side);
		lift(127, -90, 15); //lift(int upSpeed, int downSpeed, int hold);
		clawMove(127, -127, 10);
	}
}
