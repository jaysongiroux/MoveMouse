// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include <vector>
#include <k4abt.h>

#include "detect.h"
#include "Window3dWrapper.h"



class eval
{
public:
    void UpdateData(k4abt_body_t selectedBody, uint64_t currentTimestampUsec);
};
