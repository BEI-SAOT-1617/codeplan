#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <time.h>
#include <iostream>
#include <unistd.h>

#include "genericInstruction.h"
#include "planManager.h"
#include "plan.h"
using namespace std;


PlanManager::PlanManager(){
	this->nPlan = 0;
	this->ptInstruction = 0;
	this->indexPlan = 0;
}


void PlanManager::executePlan(QueuingPort* ChannelEmission, int* responseController,QueuingPort* ChannelErreur){


if (nPlan > 0) {
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

	if ((jumpInstruction == false) && (nPlan > 0) ) {
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
			cout<<"C'est l'heure ";
			bool start_timeout = false;
/*---------------------------------------------------------*/
			// To find the type of order: photo or attitude
			if (currentInst->getType() == 'p') {
				Camera C;
				C.code = 1; 
				C.exposure = currentInst->getExposure();
				string aux = currentInst->getPhotoName(); 
				strcpy(C.photoName,aux.c_str());

				cout << endl << "New photo! Smile!" << endl;
				ChannelEmission->SendQueuingMsg((char*)&C, sizeof(Camera));
				//myCameraController->photoShoot(photoName, exposure);
				
				start_timeout = true;
			} else if (currentInst->getType() == 'a') {

				Attitude A;
				A.code = 0;
				A.yaw = currentInst->getYaw();
				A.pitch = currentInst->getPitch();
				A.roll = currentInst->getRoll();

				cout << endl << "New attitude change!!" << endl;
				ChannelEmission->SendQueuingMsg((char*)&A, sizeof(Attitude));
				//myAttitudeController->attitudeChange(yaw, pitch, roll); // roll(not used)
				
				start_timeout = true;
			}else {
				Status S;
				S.code = 4;
				S.errorID = 2; // A changer.		
				sprintf(S.description, "Wrong instruction type, Plan %d.%d : Line #%d : Index : #%d ",P.getID(),P.getVersion(), ptInstruction+1,  group);

				ChannelErreur->SendQueuingMsg((char*)&S, sizeof(Status));
			}
/*---------------------------------------------------------*/

			/*-------------Wait for Time Out of the controller response-----------*/
			int time_out = 1000000; 
			if (start_timeout == true) {
				while (time_out > 0 && *responseController == 0){
					usleep(1);
					time_out--;
				}
			}
			/*-------------------------------------------------------------------*/

			/*--------------------   Management of the errors    ----------------*/
			if (*responseController != 1) {
				bannedInstructions[group] = true; 
				if (*responseController == -1){
					cout<<"Instruction "<<group<<" banned : error from controller"<<endl;
						Status S_controller;
						S_controller.code = 4;

						if (currentInst->getType() == 'a'){
							// The attitude was not reached 
							S_controller.errorID = 0; 	// Look the error list
							sprintf(S_controller.description, "Attitude not reached. Plan %d.%d : Line #%d : Index #%d ",P.getID(),P.getVersion(), ptInstruction+1,  group);
						}	
						if (currentInst->getType() == 'p'){
							// The photo was not taken 
							S_controller.errorID = 1; // Look the error list
							sprintf(S_controller.description, "Photo not taken. Plan %d.%d : Line #%d : Index #%d ",P.getID(),P.getVersion(), ptInstruction+1,  group);	
						}
						
							
						
						cout << S_controller.description << endl;

						ChannelErreur->SendQueuingMsg((char*)&S_controller, sizeof(Status));
				}
				if (time_out == 0){
					cout<<"Instruction "<<group<<" banned : timeout."<<endl;
					// Time out in the response of the attitude controller
				}
			}
			/*-------------------------------------------------------------------*/
			
			/*-----------------   Photo sending to the ComGrdMnger  -------------*/
			if ( *responseController == 1  && currentInst->getType() == 'p') {	
					PlanFilePath PhotoPath;
					PhotoPath.code = 3;
					string aux =  currentInst->getPhotoName();
					strcpy (PhotoPath.filepath , aux.c_str()) ; 	
					printf("Sending the photo %s \n", PhotoPath.filepath);
					ChannelErreur->SendQueuingMsg((char*)&PhotoPath, sizeof(PlanFilePath));
			
			}
			/*-------------------------------------------------------------------*/

			*responseController = 0;
			ptInstruction++;

		

		} else if (	// Cas où le temps de l'instruction est déjà passé... on l'aura jamais !
			 ( (now->tm_hour == currentInst->getHour())  && 	( now->tm_min > currentInst->getMin() )) ||
									( (now->tm_min  == currentInst->getMin() )  &&  ( now->tm_sec > currentInst->getSec() ))
														) { 
					cout<<"L'heure est deja passé "<<ptInstruction<<endl;
					Status S_heure;
					S_heure.code = 4;
					S_heure.errorID = 3;
					ChannelErreur->SendQueuingMsg((char*)&S_heure, sizeof(Status));

					ptInstruction++;
		
		}
	} else if (jumpInstruction) {
		ptInstruction++;
		cout<<"Instruction jumped"<<endl;
	}

	//}
	if (ptInstruction >= P.getnInstructions()){ // Fin d'un plan d'instruction, on passe au suivant.
				ptInstruction = 0;
				indexPlan = (indexPlan + 1)%PLANS_BUFFER_SIZE;
				nPlan--;
				for (int k=0; k< 100; k++) this->bannedInstructions[k] = false;
		}
	} // end big if
}

void PlanManager::generatePlan(const char* filepath){

	int version;
	int num_plan;
	bool existnewPlan = false;

	string s = filepath;
	version = s[6]-'0';
	num_plan = s[4]-'0';

	Plan myPlan(num_plan, version);
	myPlan.loadPlan(filepath);

	//Plans[nPlan].printPlan();

	cout << "version "<< version << endl;
	cout << "num_plan "<< num_plan<< endl;

	for (int i = 0 ; i < nPlan; i++){
		cout << "nplan " << Plans[(i+indexPlan)%PLANS_BUFFER_SIZE].getID()<< endl;
		int k = (i+indexPlan)%PLANS_BUFFER_SIZE;
		if (  (Plans[k].getID()==num_plan) & (k != indexPlan)  ){
				cout << "hola " << Plans[k].getVersion()<<endl;
				if (Plans[k].getVersion() < version){
					Plans[k] = myPlan;
					cout << " New version of an existing plan "<< endl;
				}
				existnewPlan = true;
		}
	}

	cout<<endl<<"Le plan existe ? "<<existnewPlan<<endl;
	if (!existnewPlan){
			Plans[(nPlan+indexPlan)%PLANS_BUFFER_SIZE] = myPlan;
			nPlan++;
	}
	cout<<"Plan ajouté"<<endl;

}


void PlanManager::printPlan(int indexPlan){
     if (indexPlan >=nPlan){
            cout << "Plan " << indexPlan << "does not exist"<< endl;
        return;
     }
	this->Plans[indexPlan].printPlan();

}



void PlanManager::pushBan(int index){
	this->bannedInstructions[index]= true;
}
