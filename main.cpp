#include <iostream>
// #include <stdlib.h>
// #include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;

int sizeMAX_planLine = 100;
int sizeMAX_photoname = 90; // 100 - (10 caracters fixes)

void lecturePlan( ){ //string *Plan, int NInstructions
	ifstream  readFile;
	readFile.open("plan.txt");
cout << "Lecture du plan \n";
	char planLine[sizeMAX_planLine];
	string planLine2;
	int line = 0;

	if (readFile.is_open())	{
		while(  getline (readFile, planLine2) ) {
			// readFile >> planLine;
			if (planLine2 != ""){
						cout << line<< " "<< planLine2<< "$\n";
						//printf("%d: %s \n", line, planLine2);
						line ++;
			}
		}
		
	readFile.close();
	}
	else{
			
	}
	

return;
}


int main(int argc, char** argv) {
	
	lecturePlan();
	return 0;
}
