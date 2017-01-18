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
		int getHour();
		int getMin();
		int getSec();
		char getType();
		int getIndex();

		virtual string getPhotoName()=0;
		virtual int getExposure()=0;

		virtual int getPitch()=0;
		virtual	int getYaw()=0;
		virtual int getRoll()=0;
};


class PhotoInstruction:public GenericInstruction{
	protected:
		string photoName;
		int exposure;
	public:
		PhotoInstruction();
		PhotoInstruction(string base);
		void printInstruction();
		string getPhotoName();
		int getExposure();

		/*  This is bullshit!!!!*/
		int getPitch();
		int getYaw();
		int getRoll();
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
		int getPitch();
		int getYaw();
		int getRoll();

		/*  This is bullshit!!!!*/
		string getPhotoName();
		int getExposure();

};

#endif

