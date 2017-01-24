#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

typedef struct Attitude Attitude;
struct Attitude {
	int code;
	int yaw;
	int pitch;
	int roll;
};

typedef struct statusControl statusControl;
struct statusControl {
	int code;
	bool returnControl;
};

typedef struct Camera Camera;
struct Camera {
	int code;
	char photoName[32];
	int exposure;
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
	
	QueuingPort channelC(0, 18002, argv[1]); 	// Client
	QueuingPort channel1(0, 18003, argv[1]); 	// Client
	QueuingPort channel2(1, 18001, s); 		// Server	


PlanManager PM;

	// generate
	thread

	while(1) {
		PM.executePlan();
	}



}
