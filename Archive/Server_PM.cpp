#include <iostream>
#include <string>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

#include "ARINC_Com.h"
#include "planManager.h"


typedef struct FilePlan FilePlan;
struct FilePlan {
	int code;
	const char* path;
};

typedef struct ReturnControl ReturnControl;
struct ReturnControl {
	int code;
	bool result;
};

int  main (*PLanManager PlanM)
{	
	int x=0;

	char s[100];
	FilePlan* f;
	ReturnControl* r;

	if (gethostname(s, 100) != 0) {
	    perror("S-> gethostname");
	    exit(1);
	}

	cout << "Host name " << s << endl; 

	QueuingPort channel(1, 18002, s); // Server

	channel.Display();

	char buffer[1024];
	int i; for(i=0; i>1024; i++) buffer[i] = '\0';

	while(1) {

		channel.RecvQueuingMsg(buffer);
		f = (FilePlan*)buffer;

		if(f->code == 2) {
			cout<<"Msg("<<x++<<"):  path ="<<f->path<<endl;
			PlanM->generatePlan(;
		} else if (f->code == 3) {
			r = (ReturnControl*)buffer;
			cout<<"Msg("<<x++<<"):  code retour ="<<r->result<<endl;
			myCameraController.photoShoot((string) c->photoName, c->exposure);
		}
	}
}
