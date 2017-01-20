#include "ComGroundManager.h"

using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include <exception.h>

ComGroundManager::ComGroundManager(){

}

void ComGroundManager::setPlan(const char* filepath) {
    PM->generatePlan(filepath);
}

void ComGroundManager::getStatus() {
    const char* statusFilepath=SM->sendStatus();

    // Send Status.txt at statusFilepath
}

void ComGroundManager::Connect() {

}
