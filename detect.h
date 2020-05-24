// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include <k4abttypes.h>
#include <chrono>

class detect
{
public:
    void UpdateData(k4abt_body_t selectedBody, uint64_t currentTimestampUsec);
	void moveMouse(float cords);
	float calcAgainstOrigin();

    bool LeftHandRaised() 
	{ 
		return m_leftHandRaised;
	}

private:
	//origin set to 0,0 by default
	float m_origin[2] = {0,0};

    bool m_leftHandRaised = false;
    std::chrono::microseconds m_handRaisedTimeSpan = std::chrono::microseconds::zero();
    std::chrono::microseconds m_previousTimestamp = std::chrono::microseconds::zero();
    const std::chrono::seconds m_stableTime = std::chrono::seconds(2);
};