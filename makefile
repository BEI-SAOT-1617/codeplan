#!/bin/sh
.SUFFIXES : .c .o 

# CONSTANTES 
CC = g++ -Wall -std=c++11 -lpthread -pthread
MAKE = make


# exemples sur les sockets :  quels sockets???
all:
	$(MAKE) genericInstruction
	$(MAKE) plan
	$(MAKE) planManager
	$(MAKE) statusManager
	$(MAKE) attitudeController
	$(MAKE) cameraController
#	$(MAKE) comGroundManager
	$(MAKE) ARINC_Com
	$(MAKE) main_PM 
	$(MAKE) main_run

# SOCKET INET 

main_run: *.o
	$(CC) *.o -o main_run

main_PM: main_PM.cpp
	$(CC) -c main_PM.cpp

genericInstruction: genericInstruction.cpp genericInstruction.h
	$(CC) -c genericInstruction.cpp genericInstruction.h

plan: plan.cpp plan.h
	$(CC) -c plan.cpp plan.h

planManager: planManager.cpp planManager.h
	$(CC) -c planManager.cpp planManager.h

statusManager:  statusManager.cpp statusManager.h
	$(CC) -c statusManager.cpp statusManager.h

attitudeController:  attitudeController.cpp attitudeController.h
	$(CC) -c attitudeController.cpp attitudeController.h

cameraController:  cameraController.cpp cameraController.h
	$(CC) -c cameraController.cpp cameraController.h

#comGroundManager:  
#	$(CC) -c comGroundManager.cpp comGroundManager.h

ARINC_Com:  ARINC_Com.cpp ARINC_Com.h
	$(CC) -c ARINC_Com.cpp ARINC_Com.h


# CLEAN .o
clean:
	rm *.o *.gch
