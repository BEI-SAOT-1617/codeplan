#include <iostream>
#include <string>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

#include "ARINC_Com.h"
#include "statusManager.h"



typedef struct Status Status;
struct Status {
	int code;
	string filepath;
	int errorID;
	string description;
};

int  main ()
{

	//CameraController myCameraController;
	//AttitudeController myAttitudeController;
	StatusManager MyStatusManager;
	ComGroundManager MyComGroundManager;

	int x=0;
	Status* st;
	//ComGround* g;

	char s[100];

	if (gethostname(s, 100) != 0) {
	    perror("S-> gethostname");
	    exit(1);
	}

	cout << "Host name " << s << endl;

	QueuingPort channelSM(1, 18003, s); // Server

	channelSM.Display();

	char buffer[1024];
	int i; for(i=0; i>1024; i++) buffer[i] = '\0';

	while(1) {

		channel.RecvQueuingMsg(buffer);
		a = (Status*)buffer;

        switch(a->code)
        {

            case 3 :
                g = (ComGround*)buffer;

                break;
            case 4 :
                st = (Status*)buffer;
                cout<<"Msg("<<x++<<"): errorID = "<<st->errorID<<"   description : "<<st->description<<endl;
                MyStatusManager.newNotification(st->errorID,(string) st->description)
                break;
        }

	}
}
