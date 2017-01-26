#include <iostream>
#include <string>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

#include "ARINC_Com.h"
#include "cameraController.h"	
#include "attitudeController.h"

int  main (int argc,char* argv[]) 
{

if (argc!=2) 
{
	printf("T'as oublie l'argument pinpin ! Le hostname... \n");
	exit (-1);
}

	cout << "The controller partition " << ::getpid() << " is ready !" << endl;
	CameraController myCameraController;
	AttitudeController myAttitudeController;

	int x=0;
	Attitude* a;
	Camera* c;
	statusControl sc;
	
	sc.code = 2;
	sc.returnControl = true;
	
	char s[100];

	if (gethostname(s, 100) != 0) {
	    perror("S-> gethostname");
	    exit(1);
	}

	//cout << "Host name " << s << endl; 
	
	QueuingPort channelOut(0, 18001, argv[1]); 	// Client
	QueuingPort channelIn(1, 18002, s); 		// Server	

	channelIn.Display();
	channelOut.Display();

	char buffer[1024];
	int i; for(i=0; i>1024; i++) buffer[i] = '\0';

	while(1) {

		channelIn.RecvQueuingMsg(buffer);
		a = (Attitude*)buffer;

		if(a->code == 0) {
			cout<<"Msg("<<x++<<"):  yaw ="<<a->yaw<<"    pitch = "<<a->pitch<<"    roll = "<<a->roll<<endl;
			sc.returnControl = myAttitudeController.attitudeChange(a->roll, a->pitch, a->yaw);
			channelOut.SendQueuingMsg((char*)&sc, sizeof(statusControl));


		} else if (a->code == 1) {
			c = (Camera*)buffer;
			cout<<"Msg("<<x++<<"):  name ="<<c->photoName<<"    exposure = "<<c->exposure<<endl;
			sc.returnControl = myCameraController.photoShoot((string) c->photoName, c->exposure);
			channelOut.SendQueuingMsg((char*)&sc, sizeof(statusControl));
		}
	}
}
