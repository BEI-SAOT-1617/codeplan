#include "StatusManager.h"

using namespace std;

StatusManager::StatusManager(){
	string defautlPath = "LogError.txt";
	this->pathLogFile= defautlPath;
}

StatusManager::StatusManager(string filepath){
	this->pathLogFile= filepath;
}

void StatusManager::newNotification(int errorID){
	ofstream writeFile;
	writeFile.open(this->pathLogFile.c_str(), ofstream::app);
	string type;
	string description;
	
	time_t rawtime;

	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	
	switch(errorID) {
		case 0: description = "ErrorID = 0"; break;
		case 1: description = "ErrorID = 1"; break;
		case 2: description = "ErrorID = 2"; break;
		case 3: description = "ErrorID = 3"; break;
		default: description = "ErrorID = default"; break;

	}	
	
	cout << "Adding notification in file log : "<< this->pathLogFile << endl;

	if(writeFile.is_open()){
		char logLine[1000];
		sprintf(logLine, "Error %d:\t%s%s\n\n",errorID, asctime(timeinfo),description.c_str());
		printf("Error %d:\t%s%s\n\n", errorID,asctime(timeinfo), description.c_str());
		writeFile << logLine;
		writeFile.close();
	}

	else{
		cout << "Could not open the log error file " << this->pathLogFile << endl;
	}
}
