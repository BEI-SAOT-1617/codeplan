#ifndef STATUSMANAGER
#define STATUSMANAGER


#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <time.h> 

#include "notification.h"

using namespace std;

const int MAX_NOTIFICATION = 1000;

class StatusManager{
protected:

string pathLogFile;

public:
	StatusManager();
	StatusManager(string);
	void newNotification(int errorID, string desc);
};


#endif


