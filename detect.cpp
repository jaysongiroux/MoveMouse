// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <Window3dWrapper.h>

#include "detect.h"
#include <iostream>

using namespace std::chrono;


int* getDestopSize()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	int size[] = { desktop.right, desktop.bottom };
	return size;
}

//mouse the mouse after the user declares where the origin is
//moves the mouse smoother
//todo this needs a lot of work
void detect::moveMouse(int x, int y)
{
	x = abs(x * multiplyer);
	y = abs(y * multiplyer);
	int interations = 5; 
	for (int i = 0; i<interations; i++)
	{
		//this math is very wrong fix this
		int point_Next_X = abs(previousPosition[0] - x / interations);
		int point_Next_Y = abs(previousPosition[1] - y/ interations);
		
		if ( i = interations)
		{
			SetCursorPos(x, y);
		}
		else
		{
			SetCursorPos(point_Next_X, point_Next_Y);
		}
		Sleep(10);
	}

}


int opp(int a)
{
	if (a <= 0)
	{
		return 0 - a;
	}
	else
	{
		return abs(a);
	}
}


// todo: will be used to check the position of the hand
void detect::UpdateData(k4abt_body_t selectedBody, uint64_t currentTimestampUsec)
{
    k4a_float3_t leftWristJoint = selectedBody.skeleton.joints[K4ABT_JOINT_WRIST_LEFT].position;
    k4a_float3_t rightWristJoint = selectedBody.skeleton.joints[K4ABT_JOINT_WRIST_RIGHT].position;
    k4a_float3_t headJoint = selectedBody.skeleton.joints[K4ABT_JOINT_HEAD].position;

    
	// bool set to true when the gestiure is performed
	//todo: dominant hand 

	// calibrate
	bool leftHandRaised = leftWristJoint.xyz.y < headJoint.xyz.y;

	//toggle start and stop
	bool bothHandsUp = leftHandRaised && rightWristJoint.xyz.y < headJoint.xyz.y;

	// exmaple how to print float: 
	//printf("%9.6f\n", leftWristJoint.xyz.x);

	///////////////////////////////////////////////

	//x: uses the center of the screen as the origin
	//x: side to side - left to right
	//y: uses center of the screen as the origin
	//y: up and down -> higher = neg
	
	//might need in order to calculate the circle around the person if designed for vr
	//z: not used --> depth



	//tracking statement: 
	if (isAllCalibrated == true && inCalibration == false && inDormant == false)
	{
		//hand tracking starts here
		//x,y 
		//moveMouse(rightWristJoint.xyz.x, rightWristJoint.xyz.y); //moves the mouse every iteration
		printf("RUNNING\n");
		bothHandsUp = false;
	}

	microseconds currentTimestamp(currentTimestampUsec);
	if (m_previousTimestamp == microseconds::zero())
	{
		m_previousTimestamp = currentTimestamp;
		m_handRaisedTimeSpan = microseconds::zero();
	}

	if (m_previousTimestampBHU == microseconds::zero())
	{
		m_previousTimestampBHU = currentTimestamp;
		m_BHUtimeSpan = microseconds::zero();
	}


///////////////////////////////////////////////////////////////


	//if the gesture is performed
	//calibrating gesture
	if (!m_leftHandRaised && leftHandRaised && isAllCalibrated == false)
	{
		// Start accumulating the hand raising time
		m_handRaisedTimeSpan += currentTimestamp - m_previousTimestamp;
		if (m_handRaisedTimeSpan > m_stableTime)
		{

			//calibration sequence
			if (isLeftCalibrated == false)
			{
				calibration[0] = rightWristJoint.xyz.x;
				isLeftCalibrated = true;
				std::cout << "MAX LEFT: " << calibration[0] << std::endl;
				printf("LEFT CALIBRATION DONE\n");
				printf("CALIBRATE RIGHT\n");
			}
			else if (isRightCalibrated == false)
			{
				calibration[1] = rightWristJoint.xyz.x;
				isRightCalibrated = true;
				std::cout << "MAX RIGHT: " << calibration[1] << std::endl;
				printf("RIGHT CALIBRATION DONE\n");
				printf("CALIBRATE TOP\n");

			}
			else if (isTopCalibrated == false)
			{
				calibration[2] = rightWristJoint.xyz.y;
				isTopCalibrated = true;
				std::cout << "MAX TOP: " << calibration[2] << std::endl;
				printf("TOP CALIBRATION DONE\n");
				printf("CALIBRATE DOWN\n");
			}
			else if (isDownCalibrated == false)
			{
				calibration[3] = rightWristJoint.xyz.y;
				isDownCalibrated = true; 
				std::cout << "MAX DOWN: " << calibration[3] << std::endl;
				printf("DOWN CALIBRATION DONE\n");
				printf("CALIBRATION DONE\n");
			}

			//if all cords are calibrated
			if (isLeftCalibrated && isRightCalibrated && isTopCalibrated && isDownCalibrated)
			{
				int* size = getDestopSize();
				std::cout << "Width: " << size[0] << " Height: " << size[1] << std::endl;

				//calculate our scallers
				vert_scaler = (size[1]) / (abs(calibration[0]) + abs(calibration[1]));
				hor_scaler = (size[0]) / (abs(calibration[2]) + abs(calibration[3])) ;
				//getting screen size

				printf("PLACE BOTH HANDS ABOVE HEAD TO BEGIN TRACKING\n");
				isAllCalibrated = true; 
				inDormant = true; //waiting to start tracking
			}
			m_leftHandRaised = leftHandRaised;
		}
	}

	//when gesture is performed after calibration sequence
	//start seq if statement
	if (!m_bothHandsUp && bothHandsUp && isAllCalibrated && inCalibration)
	{
		m_BHUtimeSpan += currentTimestamp - m_previousTimestampBHU;
		if (m_BHUtimeSpan > m_stableTimeBHU)
		{
			//start tracking the right hand to control the mouse
			printf("BOTH HANDS RAISED, BEGINNING TRACKING TO LINK TO THE MOUSE...\n");
			inDormant = false; //tracking...
			inCalibration = false;
			m_bothHandsUp = false;
		}
	}

	//stop running 
	//todo: having issues here. stops tracking immediatly after starting to track
	if (bothHandsUp && !inDormant)
	{
		m_BHUtimeSpan += currentTimestamp - m_previousTimestampBHU;
		if (m_BHUtimeSpan > m_stableTimeBHU)
		{
			//start tracking the right hand to control the mouse
			printf("STOPING\n");
			inDormant = true; //tracking...
			m_bothHandsUp = bothHandsUp;
		}
	}


///////////////////////////////////////////////////////////////


	else if (!leftHandRaised)
	{
		// Stop the time accumulation immediately when hands are put down
		m_leftHandRaised = false;
		m_previousTimestamp = microseconds::zero();
		m_handRaisedTimeSpan = microseconds::zero();
	}

	else if (!bothHandsUp)
	{
		m_bothHandsUp = false;
		m_previousTimestampBHU = microseconds::zero();
		m_BHUtimeSpan = microseconds::zero();
	}

}
