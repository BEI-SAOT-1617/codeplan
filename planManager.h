#ifndef PLANMANAGER
#define PLANMANAGER


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "plan.h"
#include "attitudeController.h"
#include "cameraController.h"


using namespace std;

class PlanManager {
protected:
	Plan Plans[2];
	int nPlan;
	int ptInstruction;
	int indexPlan;
	bool bannedInstructions[100]={false};

public:
	PlanManager();
	void executePlan();
	Plan generatePlan(const char*);
	void printPlan(int indexPlan);
	void pushBan(int index);
};


#endif


