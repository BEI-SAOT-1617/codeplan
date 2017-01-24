#include "cameraController.h"

using namespace std;

#include <stdlib.h> 
#include <stdio.h>



CameraController::CameraController(){


}

bool CameraController::photoShoot(string fileName, int exposure) {

	char cmde[1024];

sprintf(cmde, "raspistill -rot 90 -o %s.jpg -t %d", fileName.c_str(), exposure);

//cout << cmde <<endl;

if (system(cmde) != 0){
	//cout << "Error in the photo shoot \n\n";
	return false;
}

/*
try
{
system(cmde);
}
catch (exception& e)
{
	cout << "exception caught:" << e.what()<< endl;
}
*/	

	return true; 
}
