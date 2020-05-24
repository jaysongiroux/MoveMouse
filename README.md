# MoveMouse 
Control your mouse with your hands.

### Objective
Utilizes the Azure Kinect Camera to track your Dominant hand and moves the mouse according to the position of your wrist

### TODO:
- Calculate against origin for mouse movement
- Move the mouse with the given cords
- Support left and right dominant hands
- UI
- Optimization
- Installer
- Installation information for this project
- how to manage clicking, dragging, scrolling etc


### Done:
- Gesture recognition to determine origin
- Camera configuration
- Code refactoring
- Framework laid


### minimum specs:
Note: these specs are according to microsoft's documentation. This will be revisited when point cloud enveloping is implemented along with other optimizations 
- 16 GB memory
- GTX 1060
- 8 core CPU

### Misc Info:
Progress of this project is streamed via twitch.tv:
https://www.twitch.tv/brokenbeamer


### Credit: 
Based off the Jump analysis example provided by Microsoft: 
https://github.com/microsoft/Azure-Kinect-Samples/tree/master/body-tracking-samples/jump_analysis_sample
This example provided a good framework for camera configuration and header variables. 