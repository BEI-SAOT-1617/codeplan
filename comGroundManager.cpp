#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>

using namespace std;

#include "ARINC_Com.h"
#include "statusManager.h"

typedef struct Status Status;
struct Status {
	int code;
	int errorID;
	char description[128];
};


typedef struct PlanFilepath PlanFilepath;
struct PlanFilepath {
	int code;
	char filepath[64];
};

typedef struct PlanName PlanName;
struct PlanName {
	int code;
	char name[11];
};

int  main (int argc,char* argv[]) 
{

if (argc!=2) 
{
	printf("T'as oublie l'argument pinpin ! Le hostname... \n");
	exit (-1);
}

	StatusManager *sm;
	Status *status;	
	PlanName *p;
	PlanFilepath pfp;
	char s[100];

	if (gethostname(s, 100) != 0) {
	    perror("S-> gethostname");
	    exit(1);
	}

	pfp.code = 3;

	cout << "Host name " << s << endl; 
	
	QueuingPort channelOutPM(0, 18001, argv[1]); 	// Client
	QueuingPort channelIn(1, 18003, s); 		// Server	

	channelIn.Display();
	channelOutPM.Display();

	char buffer[1024];
	int i; for(i=0; i>1024; i++) buffer[i] = '\0';

	
	while(1) {

		channelIn.RecvQueuingMsg(buffer);
		status = (Status*)buffer;

		if(status->code == 4) {
			string str(status->description);
			sm->newNotification(status->errorID, str);
		}
		if(status->code == 5) {
			p = (PlanName*)buffer;
			for(int i=0; i<11; i++)
				pfp.filepath[i] = p->name[i];
			cout<<p->name;
			channelOutPM.SendQueuingMsg((char*)&pfp, sizeof(PlanFilepath));
		}
	}
}






