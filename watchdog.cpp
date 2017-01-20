#include "Watchdog.h"

using namespace std;

#include <stdlib.h> 
#include <stdio.h>


Watchdog::Watchdog() {
	// par défaut en mode follower
	mode='F';

	// activation des GPIO
	char cmde_exportOut[] = {"                                "};
	char cmde_exportIn[] = {"                                "};

	sprintf(cmde_exportOut, "echo \"3\" > /sys/class/gpio/export");
	sprintf(cmde_exportIn, "echo \"2\" > /sys/class/gpio/export");

	cout << cmde_exportOut << endl;
	cout << cmde_exportIn << endl;

	// choix du mode (in/out) des GPIO
	char cmde_activOut[] = {"                                "};
	char cmde_activIn[] = {"                                "};

	sprintf(cmde_activOut, "echo \"out\" > /sys/class/gpio/gpio3/direction");
	sprintf(cmde_activIn, "echo \"in\" > /sys/class/gpio/gpio2/direction");

	cout << cmde_activOut << endl;
	cout << cmde_activIn << endl;
}


char Watchdog::getmode() {
	return mode;
}


void Watchdog::set() {
	// I'm alive!!!!
	char cmde_setOut[] = {"                                "};

	sprintf(cmde_setOut, "echo \"out\" > /sys/class/gpio/gpio3/value");

	cout << cmde_setOut << endl;

}


int Watchdog::read() {

	// Lecture de l'état du GPIO
	#define VALUE_MAX 30
	char path[VALUE_MAX];
	char value_str[3];
	int fd;
 
	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio2/value");
	fd = open(path, O_RDONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for reading!\n");
		return(-1);
	}
 
	if (-1 == read(fd, value_str, 3)) {
		fprintf(stderr, "Failed to read value!\n");
		return(-1);
	}
 
	close(fd);
 
	return atoi(value_str); // état : 0 si mort, 1 si vivant

}


