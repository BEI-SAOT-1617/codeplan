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

cout << cmde_pitch<< endl;
cout << cmde_yaw  << endl;

/*
systeme(cdme_pitch);
systeme(cdme_yaw);
*/

return true; 
}
