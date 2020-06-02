# MoveMouse 
Control your mouse with your hands.

## Objective
The Objective of this project is to create a basic iteration of JARVIS from Iron Man the Movie. The program will consist of body tracking to control all aspects of the mouse, along with voice commands. Voice Integration will go as far as commands for the program to questions about the weather, set a timer, etc. Voice integration will be handled working with Window's Cortana. 

## minimum specs:
Note: these specs are according to microsoft's documentation. This will be revisited when point cloud enveloping is implemented along with other optimizations 
- 16 GB memory
- GTX 1060
- 8 core CPU
- USB 3 or 3.1
- Microsoft Azure Kinect Camera

## OS
### Linux:
Note: this will not run on Linux. for practice developing on Linux, I developed the UI on Ubunutu. 
- `sudo apt-get install qtcreator`
- ` sudo apt install qt5-default`
- `sudo apt-get install qt5-doc qtbase5-examples qtbase5-doc-html`
- `sudo apt install qt5-default`
- `make`
- resource: https://vitux.com/compiling-your-first-qt-program-in-ubuntu/  

### Windows:
Note: Developed on Windows 10 Professional. 
- Download Microsoft's body tracking examples: https://github.com/microsoft/Azure-Kinect-Samples/tree/master/body-tracking-samples
- Clone this repo within the 'body-tracking-samples' folder from the microsoft example repo
- Download and install CUDA toolkit and CUDNN
- open visual studio and download the following packages
	* Azure Kinect Sensor v1.3.0
	* Kinect Body Tracking 1.0.0
	* glfw v3.3.0
	* Kinect Body Tracking Dependancies v0.9.1
	* Note: if a wrong version or dependancy is installed, Visual studio will let you know and try and tell you what you're missing/ version number that's wrong.


### Misc Info:
Progress of this project is streamed via twitch.tv:
https://www.twitch.tv/brokenbeamer


### Credit: 
Based off the Jump analysis example provided by Microsoft: 
https://github.com/microsoft/Azure-Kinect-Samples/tree/master/body-tracking-samples/jump_analysis_sample
This example provided a good framework for camera configuration and header variables. 
