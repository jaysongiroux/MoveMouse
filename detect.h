// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include <k4abttypes.h>
#include <chrono>

class detect
{
public:
    void UpdateData(k4abt_body_t selectedBody, uint64_t currentTimestampUsec);
	void moveMouse(float x, float y, float z);
    bool LeftHandRaised() 
	{ 
		return m_leftHandRaised;
	}

private:
	//left, right, top, down
	float calibration[4] = {0,0,0,0};
	float pervious_values[3] = { 0.0, 0.0, 0.0};
	bool isLeftCalibrated = false;
	bool isRightCalibrated = false;
	bool isTopCalibrated = false;
	bool isDownCalibrated = false;
	bool inCalibration = true;
	bool isAllCalibrated = false;

	//not tracking and not calibrating
	bool inDormant = true;

	int vert_scaler = 0;
	int hor_scaler = 0;
	float multiplyer = 2;
    bool m_leftHandRaised = false;
	bool m_bothHandsUp = false;


	//calibrate
    std::chrono::microseconds m_handRaisedTimeSpan = std::chrono::microseconds::zero();
    std::chrono::microseconds m_previousTimestamp = std::chrono::microseconds::zero();
    const std::chrono::seconds m_stableTime = std::chrono::seconds(1);

	//start stop tracking
	std::chrono::microseconds m_BHUtimeSpan = std::chrono::microseconds::zero();
	std::chrono::microseconds m_previousTimestampBHU = std::chrono::microseconds::zero();
	const std::chrono::seconds m_stableTimeBHU = std::chrono::seconds(1);
};