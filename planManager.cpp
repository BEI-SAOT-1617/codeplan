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
	this->nPlan = 0;
	this->ptInstruction = 0;
	this->indexPlan = 0;
	//this->bannedInstructions[]={false};
}
/* Merci Felix!! :) */


void PlanManager::executePlan(){


if (nPlan > 0)
{
	Plan P = this->Plans[indexPlan];
	GenericInstruction* currentInst;

	bool instructionCatched, jumpInstruction;
	//for (int i = 0 ; i < P.getnInstructions(); i++){

		currentInst = P.getInstruction(ptInstruction);
		instructionCatched = false;
		jumpInstruction = false;

		//while(wt){

		time_t t = time(0);
		struct tm * now = localtime(&t);

		int group = currentInst->getIndex();
		if ((this->bannedInstructions[group]) == true) jumpInstruction = true;

		if (jumpInstruction == false) {
			if ((now->tm_hour == currentInst->getHour()) & (now->tm_min == currentInst->getMin()) & (now->tm_sec == currentInst->getSec())) {

				if (currentInst->getType() == 'p') {

					int exposure = currentInst->getExposure();
					string photoName = currentInst->getPhotoName();

					exposure = 500;
					cout << endl << "New photo! Smile!" << endl;
					//myCameraController->photoShoot(photoName, exposure);

				}
				else if (currentInst->getType() == 'a') {

					int yaw = currentInst->getYaw();
					int pitch = currentInst->getPitch();
					int roll = currentInst->getRoll();

					cout << endl << "New attitude change!!" << endl;
					//myAttitudeController->attitudeChange(yaw, pitch, roll); // roll(not used)
				}

				ptInstruction++;
				if (ptInstruction > P.getnInstructions()){
				ptInstruction = 0;
				indexPlan++;
				indexPlan=indexPlan%2;
				nPlan--;
				}


				instructionCatched = false;
			}
		}
		//}
	//}

}
}

Plan PlanManager::generatePlan(const char* filepath){

	unsigned int version;
	unsigned int num_plan;
	bool existnewPlan = true;

	string s = filepath;
	version = s[6]-'0';
	num_plan = s[4]-'0';

	Plan myPlan(num_plan, version);
	myPlan.loadPlan(filepath);

	//Plans[nPlan].printPlan();

	cout << "version "<< version << endl;
	cout << "num_plan "<< num_plan<< endl;

	for (int i = 0 ; i < nPlan; i++){
		cout << "nplan " << Plans[(i+indexPlan)%2].getID()<< endl;
		if (Plans[(i+indexPlan)%2].getID()==num_plan){
				cout << "hola " << Plans[(i+indexPlan)%2].getVersion()<<endl;
				if (Plans[(i+indexPlan)%2].getVersion() < version){
					Plans[(i+indexPlan)%2] = myPlan;
					existnewPlan = false;
					cout << " New version of an existing plan "<< endl;
				}
		}
	}

	if (existnewPlan){
			Plans[(nPlan+indexPlan)%2]= myPlan;
			nPlan++;
	}

}


void PlanManager::printPlan(int indexPlan){
     if (indexPlan >=nPlan){
            cout << "Plan " << indexPlan << "does not exist"<< endl;
        return;
     }
	this->Plans[indexPlan].printPlan();
	return;

}



	void PlanManager::pushBan(int index){
		this->bannedInstructions[index]= true;
	}
