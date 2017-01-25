#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "config_kernel.h"

pid_t pid[TFRAME]; // Major Frame repartition
pid_t pidList[N]; // table of pid, one per partition 

int Tperiod[N]; // table of periods, i.e. time budget per partition

int status;

int i;

pid_t p;

int active_p; // id of the running process

// main control loop

int main(int argc, char *argv[]) {

if ((argc==0) || (argc==1) ) {
	printf("Ooops! T'as oublié les arguments, les pid des process! (argc=%d)\n", argc);
	exit(1);
}

// Initialisation of the periods
Tperiod[0]=TIME_PM;
Tperiod[1]=TIME_SM;
Tperiod[2]=TIME_CT;

// Main body of the program

// Reading partition ids (pids)
	pid[0] = atoi(argv[1]) ; // FIRST process-partition PM
	pid[1] = atoi(argv[2]) ; // SECOND process-partition SM
	pid[2] = atoi(argv[1]) ; // FIRST process-partition PM
	pid[3] = atoi(argv[1]) ; // FIRST process-partition PM
	pid[4] = atoi(argv[2]) ; // SECOND process-partition SM
	pid[5] = atoi(argv[1]) ; // FIRST process-partition PM
	pid[6] = atoi(argv[3]) ; // THIRD process-partition CT

printf("********* LIST OF PARTITION IDS************\n");

for (i=0; i<N; i++)
	printf("pids - P%d:	%d\n",i,pid[i]);

printf("********* LIST OF PARTITION TIME BUDGET ************\n");

for (i=0; i<N; i++)
	printf("TIME_P - P%d:	%d\n",i,Tperiod[i]);

printf("********* STOPPING ALL PARTITION IDS************\n");

for (i=0; i<N; i++){
    printf("STOP - P%d:     %d\n",i,pid[i]);
	kill (pid[i],  SIGSTOP);
}

printf("********* WAITING BEF0RE SCHEDULING LOOP  ************\n");
printf("********* All partitions must be stopped  ************\n");

sleep (10);

printf("********* STARTING SCHEDULING LOOP ************\n");

active_p=0; // active process active_p set to 0 (1st process in major frame)

while (1) {  // Scheduler infinite loop

	// next process to schedule
	printf("Active P(%d) – PID: %d – ", active_p, pid[active_p]);
	kill (pid[active_p], SIGCONT);

	// scheduler waiting for active_p time budget
	printf("Tperiod: %d ms\n", Tperiod[active_p]);
	usleep (Tperiod[active_p]*1000); // parameter in usec

	// stop active_p after time budget elapsed
	kill (pid[active_p], SIGSTOP);

	// set active_p to next (modulo N, number of partitions)
	
	active_p=(active_p + 1) % TFRAME;
	
} // end of while - end of main loop

}; // end of program
