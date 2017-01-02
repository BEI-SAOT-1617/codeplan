#include "plan.h"

#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

using namespace std;


GenericInstruction::GenericInstruction(string base) {
	string time = base.substr(0,6);
	
	this->hour =  atoi(time.c_str())/10000;
	this->sec =  atoi(time.c_str())%100;
	this->min =  (atoi(time.c_str())%10000)/100;
	
	string type = base.substr(6,1);
	char *aux = new char[1];
	strcpy(aux , type.c_str()  );
	this->type = *aux;

}

PhotoInstruction::PhotoInstruction(string base):GenericInstruction(base){
/*  	For a photo shoot :    string instruction = ”HHMMSSpNomImage In”	*/

string cut = base.substr(7,base.length()-7);
this->photoName = cut.substr(0, cut.find(" "));

string leftover = base.substr(8+this->photoName.length(), 2);
this->index = atoi( leftover.c_str()  );


}

void PhotoInstruction::printInstruction (){
	printf("Time: %02d:%02d:%02d ", this->hour, this->min, this->sec);
	printf("Type: %c ", this->type );		
	printf("Ph. Name: %s \t", this->photoName.c_str()); 
	printf(" Index: %d \n", this->index);

}


AttitudeInstruction::AttitudeInstruction(string base):GenericInstruction(base){
/*      For a attitude change: string instruction[ ]=”HHMMSSaAAABBBCCC In"	*/
	string att = base.substr(7,9);
	
	this->roll =  atoi(att.c_str())/1000000;
	this->yaw =  atoi(att.c_str())%1000;
	this->pitch =  (atoi(att.c_str())%1000000)/1000;

	string leftover = base.substr(17,2);
	this->index = atoi( leftover.c_str()  );	
}

void AttitudeInstruction::printInstruction (){
	
	printf("Time: %02d:%02d:%02d ", this->hour, this->min, this->sec);
	printf("Type: %c ", this->type );	
	printf("Attitude: %02d:%02d:%02d \t", this->roll, this->pitch, this->yaw );	
	printf(" Index: %d \n", this->index);

}

Plan::Plan(int identifier, int ver) {
	this->id = identifier;
	this->version = ver;
	this->nInstructions = 0;
	
}

void Plan::printPlan(){

/*	for (int i =0; i < this->nInstructions; i++){
		this->ActivityList[i].printInstruction();
	}
*/

}
