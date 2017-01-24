#include "notification.h"

using namespace std;

#include <stdlib.h> 
#include <stdio.h>

Notification::Notification(){
}
	
Notification(string d,int ind,string desc);	
	this->date = d;
	this->index_plan = ind;
	this->description = desc;
}
