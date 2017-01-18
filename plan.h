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
		Plan();
		Plan(int identifier, int ver);
		int getnInstructions();
		void printPlan();
		GenericInstruction* getInstruction(int i);
		void loadPlan(const char* filepath);
		bool stockInstruction(GenericInstruction* newInstruction);
};

#endif
