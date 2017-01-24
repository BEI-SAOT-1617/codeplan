#ifndef CAMERA_CONTROLLER
#define CAMERA_CONTROLLER


#include <iostream>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <sstream>


using namespace std;

class CameraController {
private:

public:
	CameraController();	
	bool photoShoot(string fileName, int exposure); // pitch, yaw and roll
};


#endif
