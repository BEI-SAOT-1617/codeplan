#ifndef STATUSMANAGER
#define STATUSMANAGER


#include <iostream>
#include <stdlib.h> 
#include <stdio.h>

#include "notification.h"

using namespace std;

const int MAX_NOTIFICATION = 1000;

class StatusManager{
protected:
	Notification ErrorList[MAX_NOTIFICATION];
	int nNotifications;
public:
	StatusManager();
	void newNotification(int errorID, string);

};


#endif


