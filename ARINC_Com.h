#ifndef ARINC_COM
#define ARINC_COM

#define MAXLGMSG 1024
#define LNGHOST 128
#define LNGMAX 1024

#include <netinet/in.h>

class QueuingPort {
protected:
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

public:
	// mode, port number; host name
	QueuingPort(int, int , char*); 

	// Message sending of a given size
	int SendQueuingMsg (char*, int);

	// Message receive of a given size
	int RecvQueuingMsg (char*);

	// Port display
        void Display();
};


class SamplingPort : public QueuingPort {
private:
	int nfds;			// number of selected input descriptors by select
	struct timeval timeout;		// Timeout setting variable
	int nds;			// number of descriptors
	fd_set readfds, writefds, exceptfds;	// bit masks for select

protected:
	long us_delay; // waiting delay for reading in microsec	

public:
	// delay, mode, port number; host name
	SamplingPort(long, int, int , char*);
	
	// Message writing of a given size
	int WriteSamplingMsg(char*, int);

	// Message reading of a given size
	int ReadSamplingMsg(char*);
};

typedef struct Attitude Attitude;
struct Attitude {
	int code;
	int yaw;
	int pitch;
	int roll;
};

typedef struct Camera Camera;
struct Camera {
	int code;
	char photoName[64];
	int exposure;
};

typedef struct Status Status;
struct Status {
	int code;
	int errorID;
	char description[128];
	
};

typedef struct PlanFilePath PlanFilePath;
struct PlanFilePath {
	int code;
	char filepath[64];
};

typedef struct PlanName PlanName;
struct PlanName {
	int code;
	char name[11];
};

typedef struct statusControl statusControl;
struct statusControl {
	int code;
	bool returnControl;
};
/*
typedef struct ReturnControl ReturnControl;
struct ReturnControl {
	int code;
	bool result;
	int indexInhibit;
};*/

#endif
