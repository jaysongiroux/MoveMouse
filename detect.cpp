// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "detect.h"

using namespace std::chrono;

//mouse the mouse after the user declares where the origin is
void detect::moveMouse(float cords)
{

}

// calculates against the origin
float detect::calcAgainstOrigin()
{
	return .1;
}


// todo: will be used to check the position of the hand
void detect::UpdateData(k4abt_body_t selectedBody, uint64_t currentTimestampUsec)
{
    k4a_float3_t leftWristJoint = selectedBody.skeleton.joints[K4ABT_JOINT_WRIST_LEFT].position;
    k4a_float3_t rightWristJoint = selectedBody.skeleton.joints[K4ABT_JOINT_WRIST_RIGHT].position;
    k4a_float3_t headJoint = selectedBody.skeleton.joints[K4ABT_JOINT_HEAD].position;

    
	// bool set to true when the gestiure is performed
	//todo: dominant hand 

	//todo: triggers to start
	bool leftHandRaised = leftWristJoint.xyz.y < headJoint.xyz.y;
                              

	// exmaple how to print float: 
	//printf("%9.6f\n", leftWristJoint.xyz.x);

	///////////////////////////////////////////////

	//x: uses the center of the screen as the origin
	//x: side to side - left to right
	//y: uses center of the screen as the origin
	//y: up and down -> higher = neg
	
	//might need in order to calculate the circle around the person if designed for vr
	//z: not used --> depth


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
			printf("left hand is raised");

			//declaring our origin to calculate against
			m_origin[0] = rightWristJoint.xyz.x;
			m_origin[1] = rightWristJoint.xyz.y;




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
