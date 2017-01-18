#include <iostream>
// #include <stdlib.h>
// #include <stdio.h>
#include <string>
#include <fstream>

#include "cameraController.h"	
#include "attitudeController.h"
#include "planManager.h"

#include <time.h>

using namespace std;


int main(int argc, char** argv) {
	
/*  Test for the controlers */
	
	PlanManager myPlanManager;

	CameraController myCameraController;
	AttitudeController myAttiudeController;
	/*
	myCameraController.photoShoot("selfie", 100);
	myAttiudeController.attitudeChange(0, 120, 200);*/


	myPlanManager.generatePlan("plan1_1.txt");

	myPlanManager.printPlan(0);

	myPlanManager.executePlan(0);

/* Test for the time recognizition

	time_t t = time(0);
	struct tm * now = localtime(&t);

	cout << now->tm_hour<< endl;
	cout << now->tm_min<< endl;
	cout << now->tm_sec<< endl;
*/
	
	return 0;
}

