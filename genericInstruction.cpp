#include "genericInstruction.h"


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
/*  	For a photo shoot :    string instruction = "HHMMSSpNomImage In"	*/

string cut = base.substr(7,base.length()-7);
this->photoName = cut.substr(0, cut.find(" "));

string leftover = base.substr(8+this->photoName.length(), 2);
this->index = atoi( leftover.c_str()  );


}

void printInstruction() {
	printf("Time: %02d:%02d:%02d ", this->hour, this->min, this->sec);
	printf("Type: %c ", this->type );	
}

void PhotoInstruction::printPInstruction (){
	this->printInstruction();
	printf("Ph. Name: %s \t", this->photoName.c_str()); 
	printf(" Index: %d \n", this->index);

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


void AttitudeInstruction::printAInstruction (){
	this->printInstruction();
	printf("Attitude: %03d:%03d:%03d \t", this->roll, this->pitch, this->yaw );	
	printf(" Index: %d \n", this->index);

}
