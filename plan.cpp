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
	
	printf("Time: %02d:%02d:%02d ", this->hour, this->min, this->sec);
	printf("Type: %c \n", this->type );
}

PhotoInstruction::PhotoInstruction(string base):GenericInstruction(base){
	
}


AttitudeInstruction::AttitudeInstruction(string base):GenericInstruction(base){
	
}

