#include "Watchdog.h"
#include "GPIO.h"

using namespace std;

#define IN  0
#define OUT 1
 
#define LOW  0
#define HIGH 1

#include <stdlib.h> 
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


Watchdog::Watchdog() {

	// activation des GPIO
	
	GPIOExport(3);
	GPIOExport(2);

	// choix du mode (in/out) des GPIO

	GPIODirection(3,OUT);
	GPIODirection(2,IN);

}


void Watchdog::set() {
	// I'm alive!!!!
	GPIOWrite(3,HIGH);
	usleep(1000);
	GPIOWrite(3,LOW);
	usleep(1000);

}


int Watchdog::readw() {

	// Lecture de l'état du GPIO
	return GPIORead(2);

}


