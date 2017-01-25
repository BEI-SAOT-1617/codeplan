#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>

#include <iostream>
using namespace std;

#include "ARINC_Com.h"

#define SOCK_ERR        -1      /* erreur fonctions sockets */

/*******************************/
// Additional utility functions

/* Exit from program closing sockets */
void bye(int s)
{
  cout << "C-> Salut !\n" << endl;;
  close(s);
  exit(0);
}


/* Display of IP address */
void DisplayAddress(struct in_addr a)
{
  printf("%s\n", inet_ntoa(a));
} 


/* Display of a socket address */
void DisplaySocketAddress(struct sockaddr_in *sa)
{
  printf("Address IP : ");
  DisplayAddress(sa->sin_addr);
  printf("\nPort : %d.\n\n",ntohs(sa->sin_port));
}

/*******************************/

// IMPLEMENTATION OF QUEUING PORT COMMUNICATION

/* Protected ATTRIBUTES **** REMINDER */

/***
        char buffer [MAXLGMSG];
        int size;
        int s_d;  // Socket descriptor id
        struct sockaddr_in s_a; // Server @
        struct sockaddr_in c_a; // Client @
        char host_s[LNGHOST]; // Host name
        int port; // Server port number
        struct hostent *s_h; // Host entry descriptor
        struct hostent *h_emetteur;     // Host entry descriptor of client machine
        int mode; // Client(0), Server (1)
***/

QueuingPort::QueuingPort (int m, int p, char* S) {

              // Parameters
                mode=m; // m=1 client, m=2 server
                cout << "Initialization in mode (O: client; 1:server) = " << mode << endl;
                port=p;
                strcpy(host_s, S);

                // Initialisation of host entry
                if ((s_h = gethostbyname(host_s)) == NULL) {
                        perror("gethostbyname");
                        exit(1);
                        } 

                // Initialisation of server address
                bzero((char *) &s_a, sizeof(s_a));
                bcopy(s_h->h_addr, (char *)&s_a.sin_addr, s_h->h_length);
                s_a.sin_family = s_h->h_addrtype;
                s_a.sin_port = port /* SERVER port */ ;

                // Creation of the Socket
                 if ((s_d = socket(AF_INET, SOCK_DGRAM, 0)) == SOCK_ERR) {
                        perror("C-> socket");
                        bye(s_d);
                }
                cout << "Socket creation... ok!" << endl;

                // Binding in server mode
                if (mode==1) { // Server mode
                        cout << "Status Server mode (bind)... " << endl;
                        if (bind(s_d, (struct sockaddr *)&s_a, sizeof(s_a)) == SOCK_ERR) { 
                        perror("S-> bind");
                        bye(s_d);
                        }
                }
                else 
                        cout << "Status Client Mode..." << endl;

        }; // End of client/server constructor 


// Message sending of a given size
int QueuingPort::SendQueuingMsg (char* s_t, int ls_t) {

                int nbeff;
                if ((nbeff = sendto(s_d,s_t,ls_t,0,(struct sockaddr *)&s_a, sizeof(s_a)))== SOCK_ERR) {
                        perror("C-> sendto");
                        bye(s_d);
                        }
                else
                        cout << "C-> Number of char sent = " << nbeff << endl;
                return(nbeff); // returns the number of char effectively sent
        };

// Message receive of a given size
int QueuingPort::RecvQueuingMsg (char* e_t){;

                int lc_a = sizeof(c_a);
                int le_t;

                cout << "Waiting for input message..." << endl;
                if ((le_t = recvfrom(s_d,e_t,MAXLGMSG,0,(struct sockaddr *)&c_a,(socklen_t *)&lc_a)) == SOCK_ERR) {
                        perror("S-> recvfrom");
                        bye(s_d);
                        }       
                else {
                        h_emetteur = gethostbyaddr(&c_a.sin_addr,sizeof(&c_a.sin_addr),c_a.sin_family); 
                        cout << "S-> client port : " << c_a.sin_port << endl;;
                        cout << "S-> client host : " << h_emetteur->h_name << endl;
                        *(e_t+le_t)='\0';
                        cout << "S-> Buffer(" << le_t << ") : " << e_t << endl;
                }
                return(le_t); // returns the number of char effectively received 
        };

// QueuingPort display
 void QueuingPort::Display() {
                cout << "Mode: " << mode << " Port Server: " << port << " Host_s: " << host_s << endl;
  
        }


// IMPLEMENTATION OF SAMPLING PORT COMMUNICATION


// delay, mode, port number; host name
SamplingPort::SamplingPort(long d, int m, int p, char* S):QueuingPort(m, p, S){
us_delay=d;
timeout.tv_sec = 0;
timeout.tv_usec = d;
nds = getdtablesize();
};
        
// Message writing of a given size
int SamplingPort::WriteSamplingMsg(char* s_t, int ls_t){
	int nbeff;
	nbeff=this->SendQueuingMsg (s_t, ls_t);
	return (nbeff);
};

// Message reading of a given size
int SamplingPort::ReadSamplingMsg(char* M){

		// Setting bit masks
  		FD_ZERO(&readfds);
		FD_SET(s_d, &readfds);
  		FD_ZERO(&writefds);
  		FD_ZERO(&exceptfds);

        int lc_a = sizeof(c_a);
	char e_t[LNGMAX]; // input buffer for message
        int le_t; // number of characters received

	int replys=0;

	// Reading loop until last message
	int last =0;

	// Socket desc id
	printf("Socket desc id = %d\n", s_d);

	// Table size
	printf("desc table size = %d\n", nds);

	while (last==0) {
		
    		 if ((nfds = select(nds,&readfds, &writefds, &exceptfds ,&timeout)) == SOCK_ERR) {
			printf("TRACE : errno = %d\n", errno);
    			perror("S-> select");
    			bye(s_d);
		}
    		else
			if (nfds==0) { // No more message in input queue, timeout elapsed
                       		printf("TRACE : no more message in the input queue \n");
                        	last=1;
                        }
			else { // Yes a message was read! nfds != 0)
                			//printf("TRACE : nfds = %d\n",nfds);
                			//printf("TRACE : reception sur PORT1\n");
                			lc_a = sizeof(c_a); le_t=0;
                			if ((le_t = recvfrom(s_d,e_t,sizeof(e_t),0,(struct sockaddr *)&c_a,(socklen_t *)&lc_a)) == SOCK_ERR) {
                			perror("S-> recvfrom");
                			bye(s_d);
                			}
                			else {
						//printf("TRACE : S-> %d ! Longueur tampon = %d\n", replys, le_t);
                        			//printf("TRACE : S-> tampon = %s\n", e_t);
                        			h_emetteur = gethostbyaddr(&c_a.sin_addr,sizeof(&c_a.sin_addr),c_a.sin_family); 
                        			//printf("TRACE : S-> Emetteur = %s \n",h_emetteur->h_name);
                        			//printf("TRACE : S-> Adresse IP: "); DisplaySocketAddress(&c_a);
                        			replys++;
                     			}
      				}

	} // end of while

	// Now , it's time to return last message and its size
	strcpy(M,e_t); // return the content of the message

	return(le_t); // return size of message

};


