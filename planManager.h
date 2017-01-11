#ifndef PLANMANAGER
#define PLANMANAGER


#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "plan.h"

using namespace std;

class PlanManager {
protected:
	Plan Plans[4];
	
public:
	PlanManager();
	// Plan(int identifier, int ver, GenericInstruction newInstruction);
	void executePlan(Plan);
	void getStatus();
	Plan generatePlan(const char*);
};









#endif
