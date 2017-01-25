#ifndef PLANMANAGER
#define PLANMANAGER


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "plan.h"
#include "attitudeController.h"
#include "cameraController.h"
#include "ARINC_Com.h"

#define PLANS_BUFFER_SIZE	2

using namespace std;

class PlanManager {
protected:
	Plan Plans[PLANS_BUFFER_SIZE];
	int nPlan;
	int ptInstruction;
	int indexPlan;
	bool bannedInstructions[100]={false};

public:
	PlanManager();
	void executePlan(QueuingPort* , int *,QueuingPort*);
	void generatePlan(const char*);
	void printPlan(int indexPlan);
	void pushBan(int index);
};
#endif
