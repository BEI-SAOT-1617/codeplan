#include <iostream>
#include <string>
#include <signal.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>



using namespace std;

#include "planManager.h"
int tid_FD, tid_FP;
pthread_t *thread1, *thread2;
PlanManager PM;
int responseController = 0;
QueuingPort* channelController; 	// Client_PM vers controller
QueuingPort* channelSM; 		// Client_PM vers com ground / SM
QueuingPort* channelReceptionPM; 		// Server_PM	


/*
typedef struct Attitude Attitude;
struct Attitude {
	int code;
	int yaw;
	int pitch;
	int roll;
};


typedef struct Camera Camera;
struct Camera {
	int code;
	char photoName[32];
	int exposure;
};
*/

typedef struct statusControl statusControl;
struct statusControl {
	int code;
	bool returnControl;
};

typedef struct Status Status;
struct Status {
	int code;
	int errorID;
	char description[64];
	char filePath[64];
};

typedef struct PlanFilePath PlanFilePath;
struct PlanFilePath {
	int code;
	const char filePath[64];
};

typedef struct ReturnControl ReturnControl;
struct ReturnControl {
	int code;
	bool result;
	int indexInhibit;
};

void * Server_PM(void *args){
	//PlanManager* PM = (PlanManager*) args;
	cout << "Bonjour du Thread Processeur " << tid_FD << endl;

	//QueuingPort* ChannelReceptionSM
	//ChannelReceptionSM = (args*)QueuingPort

	int x=0;

	char s[100];
	PlanFilePath* f;
	ReturnControl* r;

	if (gethostname(s, 100) != 0) {
	    perror("S-> gethostname");
	    exit(1);
	}

	cout << "Host name " << s << endl;

	// KEZAKO ???
	channelReceptionPM->Display();

	char buffer[1024];
	int i; for(i=0; i>1024; i++) buffer[i] = '\0';

	while(1) {

		channelReceptionPM->RecvQueuingMsg(buffer);
		f = (PlanFilePath*)buffer;

		if(f->code == 3) {
			cout<<"Msg("<<x++<<"):  path ="<<f->filePath<<endl;
			PM.generatePlan(f->filePath);
		} else if (f->code == 2) {
			r = (ReturnControl*)buffer;
			cout<<"Msg("<<x++<<"):  code retour ="<<r->result<<"):  code retour ="<<r->indexInhibit<<endl;
			if (r->result == false) {
				// PM->pushBan(r->indexInhibit);
				responseController = -1;
			}
			else{
				responseController = 1;
			}
		}
	

 	cout << "Terminaison du Thread " << tid_FD << endl;
	}
return NULL;
}

void * Client_PM(void *args){
	// Partie Surete de fonctionnement
	while(1){
	PM.executePlan(channelController, &responseController,channelSM );
	}
return NULL;
}


int  main (int argc,char* argv[]) {

	if (argc!=2) {
		printf("T'as oublie l'argument pinpin ! Le hostname... \n");
		exit (-1);
	}
	

	char s[100];

	if (gethostname(s, 100) != 0) {
	    perror("S-> gethostname");
	    exit(1);
	}

	cout << "Host name " << s << endl; 
	
	channelController = new QueuingPort(0, 18002, argv[1]); 	// Client_PM vers controller
	channelSM = new QueuingPort(0, 18003, argv[1]); 		// Client_PM vers com ground / SM
	channelReceptionPM = new QueuingPort(1, 18001, s); 		// Server_PM	

	// generate thread
	pthread_attr_t *thread_attributes;
	pthread_t *thread;

	/* creation du thread Server1 */
	tid_FD = 1;

	thread_attributes=(pthread_attr_t *)malloc(sizeof(pthread_attr_t));
	thread=(pthread_t *)malloc(sizeof(pthread_t));

	thread1 = thread;
	pthread_attr_init(thread_attributes);
	if (pthread_create(thread, thread_attributes, Server_PM,(void *) NULL) != 0) 
		perror ("Thread_Server-> Failure detector thread pb!");

	tid_FP = 2;

	thread_attributes=(pthread_attr_t *)malloc(sizeof(pthread_attr_t));
	thread=(pthread_t *)malloc(sizeof(pthread_t));

	thread2 = thread;
	pthread_attr_init(thread_attributes);
	if (pthread_create(thread, thread_attributes, Client_PM,(void *) NULL) != 0) 
		perror ("Thread_Server-> Failure detector thread pb!");

	while(1) {	}


	
return 0;


}
