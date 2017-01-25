#!/bin/sh
.SUFFIXES : .c .o 

# CONSTANTES 
CC = g++ -Wall -std=c++11 -lpthread -pthread
MAKE = make


# exemples sur les sockets :  quels sockets???
all:
	$(MAKE) ARINC_Com
	$(MAKE) genericInstruction
	$(MAKE) plan
	$(MAKE) planManager
	$(MAKE) statusManager
	$(MAKE) attitudeController
	$(MAKE) cameraController
	$(MAKE) gpio
	$(MAKE) watchdog
	$(MAKE) main_PM 
	$(MAKE) main_run
	$(MAKE) comGroundManager
	$(MAKE) Ground
	$(MAKE) Control_run
	$(MAKE) kernel
	$(MAKE) clean

# Commandes a executer
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

comGroundManager: ARINC_Com.o statusManager.o comGroundManager.o
	$(CC) ARINC_Com.o statusManager.o comGroundManager.o -o main_Com_ST

ARINC_Com:  ARINC_Com.cpp ARINC_Com.h
	$(CC) -c ARINC_Com.cpp ARINC_Com.h

Ground: ARINC_Com.o Ground.o
	$(CC) ARINC_Com.o Ground.o -o main_Ground

Control_run : ARINC_Com.o attitudeController.o cameraController.o control.o
	$(CC) ARINC_Com.o attitudeController.o cameraController.o control.o -o main_Control
	
watchdog : watchdog.cpp watchdog.h
	$(CC) -c watchdog.cpp watchdog.h
	
gpio : GPIO.cpp GPIO.h
	$(CC) -c GPIO.cpp GPIO.h

kernel: kernel_arinc.cpp
	gcc kernel_arinc.cpp

# CLEAN .o
clean:
	rm *.o *.gch
