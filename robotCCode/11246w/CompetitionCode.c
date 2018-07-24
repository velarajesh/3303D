#pragma config(Motor,  motor2,          lefttoMotor,   tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor3,          leftfrMotor,   tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor4,          rightfrMotor,  tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor5,          righttoMotor,  tmotorVexIQ, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
This program will use the VEX IQ Wirless Controller to drive your Clawbot. This program uses
If/Else statements to provide a "threshold" for the transmitter - this allows your robot to
come to a stop even if the joysticks on the Wireless Controller haven't perfectly returned to
their zero position.

Note: You will have to set ROBOTC to enable "Wireless Control" to use the VEX IQ joystick.

ROBOT CONFIGURATION: VEX IQ Clawbot
MOTORS & SENSORS:
[I/O Port]          [Name]              [Type]                			[Location]
Port 1        			leftMotor           VEX IQ Motor		      			Left side motor
Port 6       				rightMotor          VEX IQ Motor		      			Right side motor (reversed)
Port 10							armMotor						VEX IQ Motor								Arm Up/Down motor
Port 11							clawMotor						VEX IQ Motor								Claw Open/Close motor
------------------------------------------------------------------------------------------------*/
void robotinitialize()
{
	setMotorBrakeMode(leftfrMotor, motorHold);
	//setMotorBrakeMode(leftbaMotor, motorHold);
	setMotorBrakeMode(rightfrMotor, motorHold);
	//setMotorBrakeMode(rightbaMotor, motorHold);
}


task main()
{

	robotinitialize();

	int threshold = 10;
	while(true)
	{
		//If the ChannelA (left Y-Axis) is greater than the threshold value,
		//then we'll set the speed of the motor to vlaue from the joystick.
		if(getJoystickValue(ChA) > threshold || getJoystickValue(ChA) < -threshold)
		{
	//		setMotorSpeed(leftdrMotor, getJoystickValue(ChA));
			setMotorSpeed(leftfrMotor, getJoystickValue(ChA));
		//	setMotorSpeed(leftbaMotor, getJoystickValue(ChA));


		}
		else  //If less than the threshold, we'll set the motor to zero.
		{
	//		setMotorSpeed(leftdrMotor, 0);
			setMotorSpeed(leftfrMotor, 0);
		//	setMotorSpeed(leftbaMotor, 0);

		}

		//If the ChannelD (right Y-Axis) is greater than the threshold value,
		//then we'll set the speed of the motor to vlaue from the joystick.
		if(getJoystickValue(ChD) > threshold || getJoystickValue(ChD) < -threshold)
		{
	//		setMotorSpeed(rightdrMotor, -getJoystickValue(ChD));
			setMotorSpeed(rightfrMotor, -getJoystickValue(ChD));
		//	setMotorSpeed(rightbaMotor, -getJoystickValue(ChD));

		}
		else  //If less than the threshold, we'll set the motor to zero.
		{
//			setMotorSpeed(rightdrMotor, 0);
			setMotorSpeed(rightfrMotor, 0);
		//	setMotorSpeed(rightbaMotor, 0);
		}





		//If Button "L-Up" is pressed in, we'll set the mid motor to run in reverse.
		/*		if(getJoystickValue(BtnLUp) == 1)
		{
		setMotorSpeed(midMotor, 127);
		}
		//If the "L-Up" isn't pressed, but "L-Down" is, we'll set the mid motor to run forward.
		else if(getJoystickValue(BtnLDown) == 1)
		{
		setMotorSpeed(midMotor, -127);
		}
		else  //If neither button is pressed, we'll set the mid motor off.
		{
		setMotorSpeed(midMotor, 0);
		}

		*/

		//If Button "R-Up" is pressed in, we'll set the arm motors to run in reverse.
		if(getJoystickValue(BtnRUp) == 1)
		{

			setMotorSpeed(righttoMotor, -127);
			setMotorSpeed(lefttoMotor, 127);
		}
		//If the "R-Up" isn't pressed, but "R-Down" is, we'll set the arm motors to run forward.
		else if(getJoystickValue(BtnRDown) == 1)
		{
			setMotorSpeed(righttoMotor, 127);
			setMotorSpeed(lefttoMotor, -127);
		}
		else	//If neither button is pressed, we'll set the arm motors off.
		{
			setMotorSpeed(righttoMotor, 0);
			setMotorSpeed(lefttoMotor, 0);

		}

/*

			if(getJoystickValue(BtnLUp) == 1)
		{

			setMotorSpeed(rightintaMotor, -127);
			setMotorSpeed(leftintaMotor, 127);
		}
		//If the "R-Up" isn't pressed, but "R-Down" is, we'll set the arm motors to run forward.
		else if(getJoystickValue(BtnLDown) == 1)
		{
			setMotorSpeed(rightintaMotor, 127);
			setMotorSpeed(leftintaMotor, -127);
		}
		else	//If neither button is pressed, we'll set the arm motors off.
		{
			setMotorSpeed(rightintaMotor, 0);
			setMotorSpeed(leftintaMotor, 0);

		}

*/




	}
}
