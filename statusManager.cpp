#include "statusManager.h"

using namespace std;

StatusManager::StatusManager(){
	this->nNotifications = 0;
}


void StatusManager::newNotification(int errorID, string description){

	printf("Error %d: %s \n\n", errorID, description.c_str());

}
