#include "attitudeController.h"

using namespace std;

#include <stdlib.h> 
#include <stdio.h>


AttitudeController::AttitudeController(){

}

bool AttitudeController::attitudeChange(int roll, int pitch, int yaw) {



char cmde_pitch[] = {"                                "};
char cmde_yaw[] = {"                                "};

sprintf(cmde_pitch, "echo \"5=%d\" > /dev/servoblaster", pitch);
sprintf(cmde_yaw, "echo \"2=%d\" > /dev/servoblaster", yaw);

//cout << cmde_pitch<< endl;
//cout << cmde_yaw  << endl;

if (system(cmde_pitch) != 0){
	//cout << "Error in the pitch mouvement \n\n";

	return false;
}

if (system(cmde_yaw) != 0 ){
	//cout << "Error in the yaw mouvement \n\n";
	return false;
}

/*
try
{
cout << system(cmde_pitch)<< endl;
cout << system(cmde_yaw)<< endl;
}
catch (exception& e)
{
	cout << "exception caught:" << e.what()<<endl;
}
*/

return true; 
}
