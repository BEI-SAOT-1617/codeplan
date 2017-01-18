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
	int nPlan;
public:
	PlanManager();
	void executePlan(int indexPlan);
	Plan generatePlan(const char*);
	void printPlan(int indexPlan);
};


#endif


