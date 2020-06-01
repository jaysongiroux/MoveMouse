# MoveMouse 
Control your mouse with your hands.

### Objective
Utilizes the Azure Kinect Camera to track your Dominant hand and moves the mouse according to the position of your wrist

### TODO:
- Support left and right dominant hands --> most likely different files, until a customizable UI is implemented
- UI
- Optimization
- Installer
- Installation information for this project
- how to manage clicking, dragging, scrolling etc
- Jitter control -> temporal smoothing is maxed out and there is still too much jitter. will look into this further

### Done:
- Gesture recognition to determine origin
- Camera configuration
- Code refactoring
- Framework laid
- hand tracking + update the mouse with position of the hand
- reduce jitter - set to 1/1 instead of 0/1 FLOAT
- syncing & calibrating
	max left
	max right
	max up
	max down
	
 - calibration K value --> integration of calibration data into the movement of the mouse
 - tracking bugs --> both hands up to stop, left hand up to start

### minimum specs:
Note: these specs are according to microsoft's documentation. This will be revisited when point cloud enveloping is implemented along with other optimizations 
- 16 GB memory
- GTX 1060
- 8 core CPU

### OS
Note: this will not run on Linux. for practice developing on Linux, I developed the UI on Ubunutu. 
- `sudo apt-get install qtcreator`
- ` sudo apt install qt5-default`
- `sudo apt-get install qt5-doc qtbase5-examples qtbase5-doc-html`
- `sudo apt install qt5-default`
- `make`
- resource: https://vitux.com/compiling-your-first-qt-program-in-ubuntu/  

### Misc Info:
Progress of this project is streamed via twitch.tv:
https://www.twitch.tv/brokenbeamer


### Credit: 
Based off the Jump analysis example provided by Microsoft: 
https://github.com/microsoft/Azure-Kinect-Samples/tree/master/body-tracking-samples/jump_analysis_sample
This example provided a good framework for camera configuration and header variables. 
