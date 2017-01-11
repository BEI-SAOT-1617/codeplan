#ifndef PLANMANAGER
#define PLANMANAGER


#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <plan.h>

using namespace std;

class PlanManager {
protected:
	
public:
	PlanManager();
	// Plan(int identifier, int ver, GenericInstruction newInstruction);
	void executePlan();
	void getStatus();
	Plan generationPlan(string);
};









#endif
