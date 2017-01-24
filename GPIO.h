#ifndef GPIO
#define GPIO

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int GPIOExport(int);
int GPIOUnexport(int);
int GPIODirection(int, int);
int GPIORead(int);  
int GPIOWrite(int, int);

#endif
