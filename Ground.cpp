#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "ARINC_Com.h"

typedef struct Plan Plan;
struct Plan {
	int code;
	char name[11];
};

int main (int argc,char* argv[]) 
{

if (argc!=2) 
{
	printf("T'as oublie l'argument banane ! Le hostname... \n");
	exit (-1);
}

// Suite si hostname en argument

cout << "Host name " << argv[1] << endl; 

Plan p;
p.code = 5;
p.name[0] = 'p';
p.name[1] = 'l';
p.name[2] = 'a';
p.name[3] = 'n';
p.name[4] = '1';
p.name[5] = '_';
p.name[6] = '1';
p.name[7] = '.';
p.name[8] = 't';
p.name[9] = 'x';
p.name[10] = 't';
p.name[11] = '\0';
p.name[12] = '\0';
p.name[13] = '\0';
p.name[14] = '\0';
p.name[15] = '\0';


char s[100];

if (gethostname(s, 100) != 0) {
	perror("S-> gethostname");
	exit(1);
}

QueuingPort channelOut(0, 18003, argv[1]); 	//Client

channelOut.Display();


channelOut.SendQueuingMsg((char*)&p, sizeof(Plan));

}
