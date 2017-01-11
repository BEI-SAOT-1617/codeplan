#include "planManager.h"
#include "plan.h"
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

PlanManager::PlanManager(){

}

void PlanManager::executePlan(Plan P){
 
}

void PlanManager::getStatus(){
  
}

Plan PlanManager::generatePlan(const char* filepath){
	
	unsigned int version;
	unsigned int num_plan;

	std::string s = filepath;
	version = s[4];
	num_plan = s[6];
	Plan myPlan(version, num_plan);
	myPlan.loadPlan(filepath);
	myPlan.printPlan();
}
