#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "ARINC_Com.h"

int main (int argc,char* argv[]) 
{

if (argc!=2) 
{
	printf("T'as oublie l'argument banane ! Le hostname... \n");
	exit (-1);
}

// Suite si hostname en argument


char s[100];
string cmde;
PlanName p;

if (gethostname(s, 100) != 0) {
	perror("S-> gethostname");
	exit(1);
}

QueuingPort channelOut(0, 18003, argv[1]); 	//Client

channelOut.Display();

cout << "Host name " << argv[1] << endl; 
cout << "Welcome to the Ground Station, what do you want to do ?" << endl;

while (1) {
	cout << "('p' to send a plan ; 'r' to receive the photos)" << endl;
	char c;
	scanf(" %c", &c);
	
	if (c == 'p'){	// Envoi d'un plan
		cout << "What is the plan name ? (end it by '.txt'" << endl;
		p.code = 5;
		scanf(" %c", &p.name)
		cout << "Sending Plan..." << endl;
		string aux(p.name);
		sprintf(cmde, "sh uploadGtoS.sh %s", aux);
		system(cmde);
		sleep(2);
		channelOut.SendQueuingMsg((char*)&p, sizeof(PlanName));
		
		cout << "Plan sent !" << endl;
	}else { // Demande des photos
		p.code = 10;
		channelOut.SendQueuingMsg((char*)&p, sizeof(PlanName));
		cout << "Receiving the images..." << endl;
		sleep(2);
	}

cout << "What do you want to do ?"<< endl;

/*
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
*/


}

}
