#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

#include "cameraController.h"	
#include "attitudeController.h"
#include "planManager.h"

#include "statusManager.h"


using namespace std;

void test_time(){
/* Test for the time recognizition */

	time_t t = time(0);
	struct tm * now = localtime(&t);

	cout << now->tm_hour<< endl;
	cout << now->tm_min<< endl;
	cout << now->tm_sec<< endl;

}


void test_Controllers() {
/*  Test for the controlers */

	CameraController myCameraController;
	AttitudeController myAttitudeController;

	myCameraController.photoShoot("selfie", 100);
	myAttitudeController.attitudeChange(0, 120, 200);
}

void test_Integration() {
/* Integration of the classes PlanManager CameraController and AttitudeController*/

	PlanManager myPlanManager;

	CameraController myCameraController;
	AttitudeController myAttitudeController;

	/* Be carefull to have a file named plan1_1.txt under the same directory 
		and with the correct instructions */

	myPlanManager.generatePlan("plan1_1.txt");

	myPlanManager.printPlan(0);

	myPlanManager.executePlan(0, &myAttitudeController, &myCameraController);


}

void test_StatusManager() {

	StatusManager myStatusManager;
	CameraController myCameraController;
	AttitudeController myAttitudeController;
	
	string photoName = "selfie";

	bool errorCamera = myCameraController.photoShoot(photoName, 100);
	bool errorAttitude = myAttitudeController.attitudeChange(0, 120, 200);
	

	if (!errorCamera){
		char cmde[1024];
		sprintf(cmde, "It was not possible to take the photo %s.jpg", photoName.c_str());
		myStatusManager.newNotification(1, cmde);	
	}
	
	if (!errorAttitude){
		char descrip[1024];
		sprintf(descrip, "It was not possible to reach the wanted position");
		myStatusManager.newNotification(2, descrip);	
	}
}
 	

int main(int argc, char** argv) {
	
	test_StatusManager();
	
	return 0;
}

