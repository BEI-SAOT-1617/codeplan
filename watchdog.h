#ifndef WATCHDOG
#define WATCHDOG


#include <iostream>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <sstream>
#include <unistd.h>


using namespace std;

class Watchdog {
private:

public:
	Watchdog();
	void set();
	int readw();
};

#endif
