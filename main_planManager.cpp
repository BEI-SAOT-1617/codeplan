#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#define LOW 0

#include "cameraController.h"	
#include "attitudeController.h"
#include "planManager.h"

#include "statusManager.h"
#include "watchdog.h"
#include "GPIO.h"

// Pour lancer :
// g++ main_planManager.cpp attitudeController.cpp cameraController.cpp planManager.cpp plan.cpp genericInstruction.cpp statusManager.cpp GPIO.cpp Watchdog.cpp -o exec 

// Pour changer la date = sudo date --set "xx:xx:xx"


using namespace std;

Watchdog watchdog;
PlanManager planManager;
char mode; // 'F' pour follower et 'L' pour leader
// En pratique, le mode devra aussi être envoyé au ComGroundManager


void changeMode() {
	// passage en mode Leader : le mode doit être envoyé au ComGroundManager
	mode='L';
}

void before() {
// Vérification watchdog, recouvrement si besoin

	if (mode=='L') {
	watchdog.set(); 		// I'm alive!!!!!

	cout << "Leader : I'm alive" << endl;

	}


	if (mode=='F') { 
		sleep(1);
		int state;
	cout << "Follower : Test watchdog" << endl;
		state = watchdog.readw(); // test watchdog
	cout << "State " << state << endl;

		// Recovery
		if(state==0) {
	cout << "Follower : changement de mode" << endl;
			changeMode(); // changement de mode
		}
	}

}


void proceed() {
// Fonctionnement normal
	cout << "Fonctionnement" << endl;
	planManager.executePlan();


}

sig_t bye() {
	cout << "Mort........" << endl;
	GPIOWrite(3,LOW);
	exit(0);
}

void after() {
	// .... do nothing
}

int main(int argc, char** argv) {
	
	mode = 'F'; // par défaut, follower
	planManager.generatePlan("plan1_1.txt");

	signal(SIGINT, (sig_t)bye);

	while(1) {
		before();
		proceed();
		after();
	}

	return 0;
}
