#include "cameraController.h"

using namespace std;

#include <stdlib.h> 
#include <stdio.h>
#include <exception.h>


CameraController::CameraController(){


}

bool CameraController::photoShoot(string fileName, int exposure) {

	char cmde[1024];

sprintf(cmde, "raspistill -rot 90 -o %s.jpg -t %d", fileName.c_str(), exposure);

cout << cmde <<endl;

try
{
systeme(cmde);
}
catch (exception& e)
{
	cout << "exception caught:" << e.what()<< endl;
}
	

	return true; 
}
