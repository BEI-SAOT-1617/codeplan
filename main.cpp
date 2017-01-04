#include <iostream>
// #include <stdlib.h>
// #include <stdio.h>
#include <string>
#include <fstream>
#include "plan.h"
#include "genericInstruction.h"

using namespace std;


int main(int argc, char** argv) {
	
	Plan myPlan(0,1);
	myPlan.loadPlan("plan.txt");
	
	myPlan.printPlan();

	//string test = "PAUSE";
	//system(test.c_str());
	return 0;
}

