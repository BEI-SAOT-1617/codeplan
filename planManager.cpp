#include "planManager.h"
#include "plan.h"

#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <time.h>
#include <iostream>

#include "genericInstruction.h"

using namespace std;


PlanManager::PlanManager(){
	this->nPlan=0;
}
/* Merci Felix!! :) */


void PlanManager::executePlan(int indexPlan){

	Plan P = this->Plans[indexPlan];
	GenericInstruction* currentInst;

	bool wt;

	for (int i = 0 ; i < P.getnInstructions(); i++){

		currentInst = P.getInstruction(i);
		wt = true;

		while(wt){

			time_t t = time(0);
			struct tm * now = localtime(&t);


			if ( (now->tm_hour==currentInst->getHour()) & (now->tm_min==currentInst->getMin()) & (now->tm_sec==currentInst->getSec()) ){
			
				wt = false;
											
				if (currentInst->getType() == 'p'){
					
					int exposure = currentInst->getExposure();
					string photoName = currentInst->getPhotoName();
						
						cout<< "New photo! Smile!";						
					}
				else if (currentInst->getType() == 'a'){

					int pitch = currentInst->getPitch();
					int yaw  = currentInst->getYaw();
					int roll = currentInst->getRoll();
						
						cout<< "New attitude change!!";

					}
						
				}
			}
		

	    }


}

Plan PlanManager::generatePlan(const char* filepath){
	
	unsigned int version;
	unsigned int num_plan;

	string s = filepath;
	version = s[4]-'0';
	num_plan = s[6]-'0';

	//cout << "version"<< version << endl;
	//cout << "num_plan"<< num_plan<< endl;


	Plan myPlan(version, num_plan);
	myPlan.loadPlan(filepath);
	
	
	Plans[nPlan] = myPlan;

	// Plans[nPlan].printPlan();

	nPlan++;

}

void PlanManager::printPlan(int indexPlan){

	this->Plans[indexPlan].printPlan();
	return;

}


