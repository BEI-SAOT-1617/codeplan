#include "planManager.h"
#include "plan.h"

#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <time.h>
#include <iostream>
#include <unistd.h>

#include "genericInstruction.h"

using namespace std;


PlanManager::PlanManager(){
	this->nPlan = 0;
	this->ptInstruction = 0;
	this->indexPlan = 0;
	//this->bannedInstructions[]={false};
}
/* Merci Felix!! :) */


void PlanManager::executePlan(QueuingPort* ChannelEmission, int* responseController){


if (nPlan > 0)
{
	Plan P = this->Plans[indexPlan];
	GenericInstruction* currentInst;

	bool jumpInstruction;
	//for (int i = 0 ; i < P.getnInstructions(); i++){

		currentInst = P.getInstruction(ptInstruction);
		jumpInstruction = false;

		//while(wt){

		time_t t = time(0);
		struct tm * now = localtime(&t);

		int group = currentInst->getIndex();
		if ((this->bannedInstructions[group]) == true) jumpInstruction = true;

		if (jumpInstruction == false) {
			if ((now->tm_hour == currentInst->getHour()) & (now->tm_min == currentInst->getMin()) & (now->tm_sec == currentInst->getSec())) {
			/*
			/ Codes des messages a envoyer :
			/ 0 = Attitude
			/ 1 = Photo
			/ 2 = RetourController
			/ 3 = PlanFilePath
			/ 4 = Status
			/ 5 = data
			*/
				if (currentInst->getType() == 'p') {
					Camera C;
					C.code = 1; 
					C.exposure = currentInst->getExposure();
					string aux = currentInst->getPhotoName(); 
					strcpy(C.photoName,aux.c_str());

					cout << endl << "New photo! Smile!" << endl;
					ChannelEmission->SendQueuingMsg((char*)&C, sizeof(Camera));
					//myCameraController->photoShoot(photoName, exposure);

				}
				else if (currentInst->getType() == 'a') {

					Attitude A;
					A.code = 0;
					A.yaw = currentInst->getYaw();
					A.pitch = currentInst->getPitch();
					A.roll = currentInst->getRoll();

					cout << endl << "New attitude change!!" << endl;
					ChannelEmission->SendQueuingMsg((char*)&A, sizeof(Attitude));

					//myAttitudeController->attitudeChange(yaw, pitch, roll); // roll(not used)
				}
				int time_out = 1000000; // 1 secondes
				while (time_out > 0 && *responseController == 0){
					usleep(1);
					time_out--;

				}

				if (*responseController != 1) {
					bannedInstructions[ptInstruction] = true;
					if (*responseController == -1){
						// The attitude was not reached 
						// We'll have to send it thru the channel
					}
					if (time_out == 0){
						// Time out in the response of the attitude controller
						// We'll have to send it thru the channel
					}
				}

				*responseController = 0;
				ptInstruction++;

				if (ptInstruction >= P.getnInstructions()){
					ptInstruction = 0;
					indexPlan++;
					indexPlan=indexPlan%2;
					nPlan--;
				}

			}
		} else ptInstruction++;
		//}
	//}

}
}

void PlanManager::generatePlan(const char* filepath){

	int version;
	int num_plan;
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
