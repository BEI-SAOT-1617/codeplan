#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "ARINC_Com.h"

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

int main (int argc,char* argv[]) 
{

if (argc!=2) 
{
	printf("T'as oublie l'argument banane!le hostname... \n");
	exit (-1);
}

// Suite si hostname en argument

cout << "Host name " << argv[1] << endl; 

Attitude a;
Camera c;

int choix =0;

QueuingPort channel(0, 18002, argv[1]);

channel.Display();

while (1) {
	cout<<"attitude = 1/camera = 2\n";
	scanf("%d", &choix);
	if (choix == 1) {
		cin>>a.yaw;
		cout<<"attitude : yaw ?"<<endl;
		cin>>a.yaw;
		cout<<"attitude : pitch ?"<<endl;
		cin>>a.pitch;
		cout<<"attitude : roll ?"<<endl;
		cin>>a.roll;
		a.code = 0;
		channel.SendQueuingMsg((char*)&a, sizeof(Attitude));
	}
	else if (choix == 2) {
		cout<<"camera : name ?"<<endl;
		cin>>c.photoName;
		cout<<"camera : exposure ?"<<endl;
		cin>>c.exposure;
		c.code = 1;
		channel.SendQueuingMsg((char*)&c, sizeof(Camera));
	}
		 
	sleep(3);
	}
}
