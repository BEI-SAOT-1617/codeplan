#include "genericInstruction.h"

using namespace std;

GenericInstruction::GenericInstruction() {
}

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


PhotoInstruction::PhotoInstruction():GenericInstruction(){
}

PhotoInstruction::PhotoInstruction(string base):GenericInstruction(base){
/*  	For a photo shoot :    string instruction = "HHMMSSpEXPOUNomImage In"	*/

string exposure = base.substr(7,5);
this->exposure = atoi(exposure.c_str());

string cut = base.substr(12,base.length()-12);
this->photoName = cut.substr(0, cut.find(" "));

string leftover = base.substr(13+this->photoName.length(), 2);
this->index = atoi( leftover.c_str()  );


}

void GenericInstruction::printInstruction() {
	printf("Time: %02d:%02d:%02d ", this->hour, this->min, this->sec);
	printf("Type: %c ", this->type );	
}

void PhotoInstruction::printInstruction (){
	printf("Time: %02d:%02d:%02d ", this->hour, this->min, this->sec);
	printf("Type: %c ", this->type );
	printf("Ph. Name: %s \t", this->photoName.c_str()); 
	printf("Expo.: %d \t", this->exposure); 
	printf("Index: %d \n", this->index);

}


AttitudeInstruction::AttitudeInstruction():GenericInstruction(){
}

AttitudeInstruction::AttitudeInstruction(string base):GenericInstruction(base){
/*      For a attitude change: string instruction[ ]="HHMMSSaAAABBBCCC In"	*/
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
	printf("Attitude: %03d:%03d:%03d \t\t\t", this->roll, this->pitch, this->yaw );	
	printf("Index: %d \n", this->index);

}

int GenericInstruction::getHour(){
return this->hour;
}

int GenericInstruction::getMin(){
return this->min;
}

int GenericInstruction::getSec(){
return this->sec;
}

char GenericInstruction::getType(){
return this->type;
}

int GenericInstruction::getIndex(){
return this->index;
}

int AttitudeInstruction::getPitch(){
return this->pitch;
}

int AttitudeInstruction::getYaw(){
return this->yaw;
}

int AttitudeInstruction::getRoll(){
return this->roll;
}

int PhotoInstruction::getExposure(){
return this->exposure;
}

string PhotoInstruction::getPhotoName(){
return this->photoName;
}


/* From this point the code is useless!!!!!!!*/

int PhotoInstruction::getPitch(){
return -1;
}

int PhotoInstruction::getYaw(){
return -1;
}

int PhotoInstruction::getRoll(){
return -1;
}


int AttitudeInstruction::getExposure(){
return -1;
}

string AttitudeInstruction::getPhotoName(){
return "-1";
}


/* More bullshit !!!!!!!*/
int GenericInstruction::getPitch(){
return -1;
}

int GenericInstruction::getYaw(){
return -1;
}

int GenericInstruction::getRoll(){
return -1;
}


int GenericInstruction::getExposure(){
return -1;
}

string GenericInstruction::getPhotoName(){
return "-1";
}


