#ifndef GENERIC_INSTRUCTION
#define GENERIC_INSTRUCTION

#include <iostream>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>

using namespace std;

/*==============================================================================*/
/*			Definition of the intructions in a plan			*/
/*==============================================================================*/
/*										*/
/* We've considered 2 types : photo shoot and attitude change			*/
/* They are definied as follows:						*/
/*										*/
/*  	For a photo shoot :    string instruction = "HHMMSSpNomImage In"	*/
/*      For a attitude change: string instruction[ ]="HHMMSSaAAABBBCCC In"	*/
/*                                       AAA = roll BBB = pitch CCC = yaw   	*/
/*==============================================================================*/


const int SIZEMAX_PLANLINE = 100;
const int SIZEMAX_PHOTONAME = 90; // 100 - (10 caracters fixes)

class GenericInstruction{
	protected:
		int hour;
		int min;
		int sec;
		char type;
		int index;
	public:	
		GenericInstruction();
		GenericInstruction(string base);
		virtual void printInstruction();
		int gethour();
		int getmin();
		int getsec();
		char gettype();
		int getindex();
};


class PhotoInstruction:public GenericInstruction{
	protected:
		string photoName;
		int exposure;
	public:
		PhotoInstruction();
		PhotoInstruction(string base);
		void printInstruction();
		string getphotoname();
		int exposure();
};

class AttitudeInstruction:public GenericInstruction{
	protected:
		int pitch;
		int yaw;
		int roll;			
	public:
		AttitudeInstruction();
		AttitudeInstruction(string base);
		void printInstruction();
		int getpitch();
		int getyaw();
		int getroll();
};

#endif

