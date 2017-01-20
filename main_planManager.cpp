#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

#include "cameraController.h"	
#include "attitudeController.h"
#include "planManager.h"

#include "statusManager.h"
#include "watchdog.h"


using namespace std;

Watchdog watchdog;
PlanManager planManager;
char mode; // 'F' pour follower et 'L' pour leader
// En pratique, le mode devra aussi être envoyé au ComGroundManager


void before() {
// Vérification watchdog, recouvrement si besoin

	if (mode=='L') {
	watchdog.set(); 		// I'm alive!!!!!
	}


	if (mode=='F') { 
		sleep(1);
		int state;
		state = watchdog.read(); // test watchdog

		// Recovery
		if(c==0) {
			mode='L'; // changement de mode
		}
	}

}


void proceed() {
// Fonctionnement normal
	planManager.executePlan(); // à modifier


}

void after() {
// .... do nothing
}

int main(int argc, char** argv) {
	
	mode = 'F'; // par défaut, follower

	while(1) {
		before();
		proceed();
		after();
	}

	return 0;
}

