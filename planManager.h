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
	void executePlan(Plan);
	Plan generatePlan(const char*);
};


#endif
