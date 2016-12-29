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
/*      For a attitude change: string instruction[ ]=”HHMMSSaAAABBBCCCIn	*/
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
		void display();
};


class PhotoInstruction:public GenericInstruction{
	protected:
			
	public:
		PhotoInstruction(string base);
};

class AttitudeInstruction:public GenericInstruction{
	protected:
			
	public:
		AttitudeInstruction(string base);
};

#endif
