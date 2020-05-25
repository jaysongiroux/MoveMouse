// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <Window3dWrapper.h>

#include "detect.h"
#include <iostream>

using namespace std::chrono;


//mouse the mouse after the user declares where the origin is
//moves the mouse smoother
void detect::moveMouse(int x, int y)
{
	x = abs(x * multiplyer);
	y = abs(y * multiplyer);
	int interations = 5; 
	for (int i = 0; i<interations; i++)
	{
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
		Sleep(1);
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

	//start tracking
	bool leftHandRaised = leftWristJoint.xyz.y < headJoint.xyz.y;
                    
	//stop tracking
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

	if (m_origin[0] != 0 && m_origin[1] != 0)
	{
		//hand tracking starts here
		//x,y 
		moveMouse(rightWristJoint.xyz.x, rightWristJoint.xyz.y);
		//SetCursorPos(abs(hor_offset - rightWristJoint.xyz.x) * multiplier, abs(vert_offset - rightWristJoint.xyz.y) * multiplier);
		
		//setting the previous position
		previousPosition[0] = rightWristJoint.xyz.x;
		previousPosition[1] = rightWristJoint.xyz.y;

		if (bothHandsUp)
		{
			printf("setting origin to 0 \n");
			m_origin[0] = 0;
			m_origin[1] = 0;
		}
	}


	//if an origin has not been set
	else
	{
		microseconds currentTimestamp(currentTimestampUsec);
		if (m_previousTimestamp == microseconds::zero())
		{
			m_previousTimestamp = currentTimestamp;
			m_handRaisedTimeSpan = microseconds::zero();
		}

		if (!m_leftHandRaised && leftHandRaised)
		{
			// Start accumulating the hand raising time
			m_handRaisedTimeSpan += currentTimestamp - m_previousTimestamp;
			if (m_handRaisedTimeSpan > m_stableTime)
			{

				//this is where the gesture is detected and assigned
				printf("left hand is raised\n");


				//declaring our origin to calculate against
				m_origin[0] = rightWristJoint.xyz.x;
				m_origin[1] = rightWristJoint.xyz.y;


				vert_offset = opp(rightWristJoint.xyz.x);
				hor_offset = opp(rightWristJoint.xyz.y);


				//printing the detected origin
				//troubleshooting for printing out the origin
				std::cout << "X: " << m_origin[0] << " Y: " << m_origin[1] << std::endl;

				m_leftHandRaised = leftHandRaised;
			}
		}
		else if (!leftHandRaised)
		{
			// Stop the time accumulation immediately when hands are put down
			m_leftHandRaised = false;
			m_previousTimestamp = microseconds::zero();
			m_handRaisedTimeSpan = microseconds::zero();
		}
	}
    
}
