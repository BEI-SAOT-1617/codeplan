#ifndef NOTIFICATION
#define NOTIFICATION

#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "genericInstruction.h"

using namespace std;

class Notification{
	protected: 
		string date;
		int index_plan;
		string description;
	public:
		Notification();
		Notification(string date,int index_plan,string description);
};

#endif