// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <array>
#include <iostream>
#include <map>
#include <vector>

#include <k4a/k4a.h>
#include <k4abt.h>

#include <BodyTrackingHelpers.h>
#include <Utilities.h>
#include <Window3dWrapper.h>

#include "detect.h"


// Global State and Key Process Function
bool s_isRunning = true;

void printIns()
{
	printf("To lock on put your dominant hand in the top left most you can reach\n");
	printf("NOTICE, You will not be able to move your dominant hand more left once this origin is set, unless you reset the origin using the trigger gesture\n");
	printf("to lock that origin, raise your other hand above your head. tracking will begin after that\n");
	printf("to stop tracking, riase your hand above your head agin\n");
}


int main()
{
	printIns();

    k4a_device_t device = nullptr;
    VERIFY(k4a_device_open(0, &device), "Open K4A Device failed!");

    // Start camera. Make sure depth camera is enabled.
    k4a_device_configuration_t deviceConfig = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL; //hardcoded at 30 fps

	// wide view by default
    deviceConfig.depth_mode = K4A_DEPTH_MODE_NFOV_2X2BINNED;
    deviceConfig.color_resolution = K4A_COLOR_RESOLUTION_OFF; //was: K4A_COLOR_RESOLUTION_OFF 
    VERIFY(k4a_device_start_cameras(device, &deviceConfig), "Start K4A cameras failed!");



    // Get calibration information
    k4a_calibration_t sensorCalibration;
	k4a_result_t cal = k4a_device_get_calibration(device, deviceConfig.depth_mode, deviceConfig.color_resolution, &sensorCalibration);
    VERIFY(cal, "Get depth camera calibration failed!");


    // Create Body Tracker
    k4abt_tracker_t tracker = nullptr;
    k4abt_tracker_configuration_t tracker_config = K4ABT_TRACKER_CONFIG_DEFAULT;

	//tracker config: oritentation, processing mode, GPU ID
	k4a_result_t created_tracker = k4abt_tracker_create(&sensorCalibration, tracker_config, &tracker);
	

    VERIFY(created_tracker, "Body tracker initialization failed!");



    // Initialize the 3d window controller
    Window3dWrapper window3d;
    window3d.Create("3D Visualization", sensorCalibration);
    
	detect Detect;
	
	//move the mouse to the origin before the while true loop
	SetCursorPos(0, 0);


	//while true loop
	printf("CALIBRATION MODE ACTIVE: \n");
	printf("CALIBRATE LEFT\n");
    while (s_isRunning)
    {
		/*k4abt_tracker_*/
        k4a_capture_t sensorCapture = nullptr;
        k4a_wait_result_t getCaptureResult = k4a_device_get_capture(device, &sensorCapture, 0); // timeout_in_ms is set to 0

		//needed
        if (getCaptureResult == K4A_WAIT_RESULT_SUCCEEDED)
        {
            // timeout_in_ms is set to 0. Return immediately no matter whether the sensorCapture is successfully added
            // to the queue or not.
            k4a_wait_result_t queueCaptureResult = k4abt_tracker_enqueue_capture(tracker, sensorCapture, 0);

            // Release the sensor capture once it is no longer needed.
            k4a_capture_release(sensorCapture);
        }

        // Pop Result from Body Tracker
        k4abt_frame_t bodyFrame = nullptr;
        k4a_wait_result_t popFrameResult = k4abt_tracker_pop_result(tracker, &bodyFrame, 0); // timeout_in_ms is set to 0
		
																							 
		/************* Successfully get a body tracking result, process the result here ***************/
		if (popFrameResult == K4A_WAIT_RESULT_SUCCEEDED)
        {
            // Obtain original capture that generates the body tracking result
            k4a_capture_t originalCapture = k4abt_frame_get_capture(bodyFrame);

		
			//track the first body: 
			//todo: change this to a better implementation
            if (k4abt_frame_get_num_bodies(bodyFrame) > 0)
            {
                k4abt_body_t body;
                VERIFY(k4abt_frame_get_body_skeleton(bodyFrame, 0, &body.skeleton), "Get skeleton from body frame failed!");
                body.id = k4abt_frame_get_body_id(bodyFrame, 0);

	            uint64_t timestampUsec = k4abt_frame_get_device_timestamp_usec(bodyFrame);
				Detect.UpdateData(body, timestampUsec);
            }

			
            // Visualize the skeleton data
            window3d.CleanJointsAndBones(); //clears previous skel data
            uint32_t numBodies = k4abt_frame_get_num_bodies(bodyFrame);

			//goes through the number of bodies in the tracking data to be displayed
			//todo: investigate if this is needed
            for (uint32_t i = 0; i < numBodies; i++)
            {
                k4abt_body_t body;
                // VERIFY(k4abt_frame_get_body_skeleton(bodyFrame, i, &body.skeleton), "Get skeleton from body frame failed!");
                body.id = k4abt_frame_get_body_id(bodyFrame, i);

                Color color = g_bodyColors[body.id % g_bodyColors.size()];
                color.a = i == 0 ? 0.8f : 0.1f;

                window3d.AddBody(body, color);
            }//end for


			// Visualize point cloud
			//todo: make this optional
			//k4a_image_t depthImage = k4a_capture_get_depth_image(originalCapture);
			//window3d.UpdatePointClouds(depthImage);

			//releasing the capture before the next points are displayed
            k4a_capture_release(originalCapture);
            //k4a_image_release(depthImage);
            k4abt_frame_release(bodyFrame);

        } //end if

		//render the window
        window3d.Render();
    }//end while



	//closing the window
    window3d.Delete();
    k4abt_tracker_shutdown(tracker);
    k4abt_tracker_destroy(tracker);

    k4a_device_stop_cameras(device);
    k4a_device_close(device);

    return 0;
}
