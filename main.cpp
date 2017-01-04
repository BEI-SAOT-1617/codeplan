#include <iostream>
// #include <stdlib.h>
// #include <stdio.h>
#include <string>
#include <fstream>
#include "plan.h"
#include "genericInstruction.h"

using namespace std;

void lecturePlan( ){
	
	ifstream  readFile;
	readFile.open("plan.txt");
	string type;
	
	cout << "Starting the reading of a plan \n";
	
	GenericInstruction * planInstruction;
	string planLine;
	int line = 0;
	
	if (readFile.is_open())	{
		while(  getline (readFile, planLine) ) {
			// readFile >> planLine;
			if (planLine != ""){
					type = planLine.substr(6,1);
					// cout << line << " "<<  type << "$\n";
					
					if (type == "a"){
						planInstruction = new AttitudeInstruction(planLine); 
					} 
					
					if (type == "p") {
						planInstruction = new PhotoInstruction(planLine); 
					}
					planInstruction->printInstruction();
					line ++;
			}
		}

	cout << "Lines read: "<< line<< endl;
	readFile.close();
	}
	else{
			
	}
	

return;
}

int main(int argc, char** argv) {
	
	lecturePlan();
	//string test = "PAUSE";
	//system(test.c_str());
	return 0;
}

