#ifndef plan
#define plan
#include <string>

using namespace std;

/*==========================================================================*/
/*				Definion of the intructions in a plan			 			*/
/*==========================================================================*/
/*																			*/
/* We've considered 2 types : photo shoot and attitude change				*/
/* They are definied as follows:											*/
/* 																			*/
/*  	For a photo shoot :    string instruction = ”HHMMSSpNomImage In”	*/
/*      For a attitude change: string instruction[ ]=”HHMMSSaAAABBBCCC In"	*/
/*                                       AAA = roll BBB = pitch CCC = yaw   */
/*==========================================================================*/


const int sizeMAX_planLine = 100;
const int sizeMAX_photoname = 90; // 100 - (10 caracters fixes)

class GenericInstruction{
	protected:
		int hour;
		int min;
		int sec;
		char type;
		int index;
	public:
		GenericInstruction(string base);
		virtual void printInstruction()=0;
};


class PhotoInstruction:public GenericInstruction{
	protected:
		string photoName;
	public:
		PhotoInstruction(string base);
		void printInstruction();
};

class AttitudeInstruction:public GenericInstruction{
	protected:
		int pitch;
		int yaw;
		int roll;			
	public:
		AttitudeInstruction(string base);
		void printInstruction();
};


const int maxInstructions = 100;

class Plan{
	protected:
		//PhotoInstruction ActivityList; // or a dynamic vector?? [maxInstructions]
		int nInstructions;
		int id;
		int version;
	public:
		Plan(int identifier, int ver);
		// Plan(int identifier, int ver, GenericInstruction newInstruction);
		void printPlan();
};

#endif
