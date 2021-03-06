
#pragma config(Sensor, dgtl1,  leftBaseEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, rightBaseEncoder, sensorQuadEncoder)
#pragma config(Motor,  port4,           leftFrontBase, tmotorVex393TurboSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           rightFrontBase, tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port6,           rightMiddleBase, tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port7,           leftMiddleBase, tmotorVex393TurboSpeed_MC29, openLoop, driveLeft)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// PID using optical shaft encoder
//
// Shaft encoder has 360 pulses per revolution
//

#define PID_SENSOR_SCALE    ((4*PI*6)/(24*360))

	//   1 rotation      24 teeth      360 ticks
	//   ----------- * ------------ * ------------
	//   4*pi inches    1 rotation       6 teeth
	//
	//    ticks
	//   -------
	//   inches
//((24*360)/(4*pi*6))

#define PID_MOTOR_SCALE     1

#define PID_DRIVE_MAX       127
#define PID_DRIVE_MIN     (-127)

#define PID_INTEGRAL_LIMIT  50


#define leftBaseSensor SensorValue[leftBaseEncoder]
#define rightBaseSensor SensorValue[rightBaseEncoder]

// These could be constants but leaving
// as variables allows them to be modified in the debugger "live"
float  pid_Kp = 20.0;
float  pid_Ki = 0.004;
float  pid_Kd = 250;

static int   pidRunning = 1;
static float pidRequestedValue;


int sensorAverage()
{
	return ((leftBaseSensor+rightBaseSensor)/2);
}

//-----BASE_CONNECTION_FUNCTIONS-----//
void leftBase(int power)//Function used to control all the motors on the left side of the base at once.
{
	motor[leftMiddleBase] = power;
	motor[leftFrontBase] = power;
}

void rightBase(int power)//Function used to control all the motors on the right side of the base at once.
{
	motor[rightMiddleBase] = power;
	motor[rightFrontBase] = power;
}

void base(int power)
{
	leftBase(power);
	rightBase(power);
}
//-----BASE_CONNECTION_FUNCTIONS-----//




/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  pid control task                                                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

task pidController()
{
    float  pidSensorCurrentValue;

    float  pidError;
    float  pidLastError;
    float  pidIntegral;
    float  pidDerivative;
    float  pidDrive;

    // If we are using an encoder then clear it
    leftBaseSensor = 0;
    rightBaseSensor = 0;


    // Init the variables - thanks Glenn :)
    pidLastError  = 0;
    pidIntegral   = 0;

    while( true )
        {
        // Is PID control active ?
        if( pidRunning )
            {
            // Read the sensor value and scale
            pidSensorCurrentValue = sensorAverage() * PID_SENSOR_SCALE;

            // calculate error
            pidError = pidSensorCurrentValue - pidRequestedValue;

            // integral - if Ki is not 0
            if( pid_Ki != 0 )
                {
                // If we are inside controlable window then integrate the error
                if( abs(pidError) < PID_INTEGRAL_LIMIT )
                    pidIntegral = pidIntegral + pidError;
                else
                    pidIntegral = 0;
                }
            else
                pidIntegral = 0;

            // calculate the derivative
            pidDerivative = pidError - pidLastError;
            pidLastError  = pidError;

            // calculate drive
            pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);

            // limit drive
            if( pidDrive > PID_DRIVE_MAX )
                pidDrive = PID_DRIVE_MAX;
            if( pidDrive < PID_DRIVE_MIN )
                pidDrive = PID_DRIVE_MIN;

            // send to motor
            base(pidDrive * PID_MOTOR_SCALE);
            }
        else
            {
            // clear all
            pidError      = 0;
            pidLastError  = 0;
            pidIntegral   = 0;
            pidDerivative = 0;
            base(0);
            }

        // Run at 50Hz
        wait1Msec(25);
        }
}

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  main task                                                                  */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

task main()
{
    // send the motor off somewhere
    pidRequestedValue = -36;

    // start the PID task
    startTask( pidController );

    // use joystick to modify the requested position
    while( true )
        {
        // maximum change for pidRequestedValue will be 127/4*20, around 640 counts per second
        // free spinning motor is 100rmp so 1.67 rotations per second
        // 1.67 * 360 counts is 600

        pidRequestedValue = pidRequestedValue + (vexRT[ Ch2 ]/4);

        wait1Msec(50);
        }

}
