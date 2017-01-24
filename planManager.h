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
	void executePlan(QueuingPort* , int *);
	void generatePlan(const char*);
	void printPlan(int indexPlan);
	void pushBan(int index);
};

typedef struct Attitude Attitude;
struct Attitude {
	int code;
	int yaw;
	int pitch;
	int roll;
};

typedef struct Camera Camera;
struct Camera {
	int code;
	char photoName[64];
	int exposure;
};

#endif
