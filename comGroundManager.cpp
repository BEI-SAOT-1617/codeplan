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

int  main (int argc,char* argv[]) 
{

if (argc!=2) 
{
	printf("T'as oublie l'argument pinpin ! Le hostname... \n");
	exit (-1);
}

	StatusManager sm;
	Status *status;	
	PlanName *p;
	Mode *m;
	PlanFilePath pfp;
	PlanFilePath *imageName;
	string imageList[128];
	ptImages = 0;
	bool mode = false; // Mode slave;
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
		if (status->code == 3){		// utilisation d'un type p
			imageName = (PlanFilePath*)buffer;
			string aux(imageName->filepath);
			imageList[ptImages] = aux;
			ptImages = (ptImages + 1)%128;
		}
		else if(status->code == 4) {
			string str(status->description);
			sm.newNotification(status->errorID, str);
		}
		else if(status->code == 5) {
			p = (PlanName*)buffer;
			for(int i=0; i<11; i++)
				pfp.filepath[i] = p->name[i];
			cout<<p->name;
			channelOutPM.SendQueuingMsg((char*)&pfp, sizeof(PlanFilePath));
		}
		else if(status->code == 6){
			m = (ModeStruct*)buffer;
			mode = m->rpiMode;
		}
		else if(status->code == 10){
			// lancer bash qui envoie chaque photo du tableau.
		}
	}
}
