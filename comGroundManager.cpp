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
#include "AES.h"

int copiefichier(char* srce, char* dest);

int main (int argc,char* argv[]) {

	if (argc!=2) {
		printf("T'as oublie l'argument pinpin ! Le hostname... \n");
		exit (-1);
	}

	StatusManager sm;
	Status *status;
	PlanName *p;
	ModeStruct *m;
	PlanFilePath pfp;
	PlanFilePath *imageName;
	string imageList[128];
	int ptImageReceived = 0;
	int ptImageSent = 0;
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
	char cmde[] = {" "};

	while(1) {
		channelIn.RecvQueuingMsg(buffer);
		status = (Status*)buffer;

		if (status->code == 3) { // utilisation d'un type p
			imageName = (PlanFilePath*)buffer;
			string aux(imageName->filepath);
			imageList[ptImageReceived] = aux;
			ptImageReceived = (ptImageReceived + 1)%128;
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
		else if((status->code == 10) && (mode == true)){
			sprintf(cmde, "sh uploadStoG.sh LogError.txt");
			system(cmde);
			while(ptImageSent != ptImageReceived){
				string temp = strcat("ciphered",imageList[ptImageSent];
				
				copiefichier(imageList[ptImageSent].c_str(), temp.c_str());
				sprintf(cmde, "sh uploadStoG.sh %s", imageList[ptImageSent].c_str());
				system(cmde);
				sleep(1);
				sprintf(cmde, "rm %s", imageList[ptImageSent].c_str());
				system(cmde);
				ptImageSent = (ptImageSent + 1)%128;
			}// lancer bash qui envoie chaque photo du tableau.
		}
	}
}

int copiefichier(char* srce, char* dest) { 	// copie le fichier srce dans dest
						// renvoie 1 si ok, 0 sinon
	cout << "\t --- Cipher AES ---" << endl;
	cout << "Ouverture du fichier d'entree: " << srce << "\n" ;
	ifstream fi(srce, ios::in|ios::binary);

     	if (!fi)  {
		cout << "PB Ouverture fichier source " << srce << "\n" ;
		return 0;        // srce impossible a lire
	}

	cout << "Ouverture du fichier de sortie: " << dest << "\n" ;
     	ofstream fo(dest, ios::out|ios::binary);

     	if (!fo) {
		cout << "PB Ouverture fichier destination " << dest << "\n" ;
	return 0;
	}

	

     	unsigned char bloc[16];
     	char tampon;
     	int i=0; 
     	int j;
	unsigned char k[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    	unsigned char *output = new unsigned char[16];
    	
	AES *aes;
    	aes = new AES(k);
	
     	while ( fo && fi.get(tampon) ) {
		// chargement du bloc
		bloc[i++]=tampon;
		if (i==16) {
			// crypto du bloc
			aes->SetInput(bloc);
    			aes->Cipher();
			output = aes->GetOutput();
			i=0;
			// ecriture dans fo
			for (j=0;j<16;j++)
				fo.put(*(output+j));		
		}
	}
     	return fo.good() && fi.eof();
}
