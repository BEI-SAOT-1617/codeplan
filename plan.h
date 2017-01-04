#ifndef PLAN
#define PLAN

#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#include "genericInstruction.h"

using namespace std;

const int maxInstructions = 100;

class Plan{
	protected:
		GenericInstruction ActivityList[maxInstructions]; // or a dynamic vector?? 
		int nInstructions;
		int id;
		int version;
	public:
		Plan(int identifier, int ver);
		// Plan(int identifier, int ver, GenericInstruction newInstruction);
		void printPlan();
};

#endif
