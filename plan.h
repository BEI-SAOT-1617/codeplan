#ifndef PLAN
#define PLAN

#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "genericInstruction.h"

using namespace std;

const int maxInstructions = 100;

class Plan{
	protected:
		GenericInstruction* ActivityList[maxInstructions]; 
		int nInstructions;
		int id;
		int version;
	public:
		Plan(int identifier, int ver);
		void printPlan();
		void loadPlan(const char* filepath);
		bool stockInstruction(GenericInstruction* newInstruction);
};

#endif
