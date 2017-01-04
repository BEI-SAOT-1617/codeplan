#include "plan.h"

using namespace std;

Plan::Plan(int identifier, int ver) {
	this->id = identifier;
	this->version = ver;
	this->nInstructions = 0;
	
}

void Plan::printPlan(){

	for (int i =0; i < this->nInstructions; i++){
		this->ActivityList[i]->printInstruction();
	}


}


bool Plan::stockInstruction(GenericInstruction * newInstruction){
	if (nInstructions == maxInstructions){
		return false;
	}
	else{
		ActivityList[nInstructions] = newInstruction;
		nInstructions++;
		return true;
	}
}


void Plan::loadPlan(const char* filepath){

	ifstream  readFile;
	readFile.open(filepath);
	string type;
	
	cout << "Starting the reading of a plan \n";
	
	GenericInstruction * planInstruction;
	string planLine;
	int line = 0;
	
	if (readFile.is_open())	{
		cout << "\t File " << filepath<< " opened \n";
		while(  getline (readFile, planLine) ) {
			if (planLine != ""){
					type = planLine.substr(6,1);
					
					if (type == "a"){
						planInstruction = new AttitudeInstruction(planLine); 
					} 
					
					if (type == "p") {
						planInstruction = new PhotoInstruction(planLine); 
					}
					this->stockInstruction(planInstruction);
					line ++;
			}
		}

	cout << "Lines read: "<< line << endl;
	readFile.close();
	}
	else{
			
	}


}
