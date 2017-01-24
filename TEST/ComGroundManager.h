#ifndef COM_GROUND_MANAGER
#define COM_GROUND_MANAGER


#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>


using namespace std;

class ComGroundManager {
private:
    int groundPublicKey;
    int selfPrivateKey;
    PlanManager* PM;
    StatusManager* SM;
    char mode;
public:
	ComGroundManager();
	void setPlan(const char*);
	void Connect();
	void getStatus();
};


#endif
