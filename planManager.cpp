#include "planManager.h"
#include "plan.h"
#include <stdlib>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <time>
#include <iostream>
#include "genericInstruction.h"
using namespace std;



PlanManager::PlanManager(){
	nPlan=0;
}



void PlanManager::executePlan(Plan P){

	GenericInstruction* A = P.getInstruction();
	bool wt = true;
	for (i = 0,i++,P.getnInstructions){
		
		While(wt){

			time_t now = time(0);	

			if ( (now.hours==A(i).gethour) & (now.min==A(i).getmin) & (now.sec==A(i).getsec) ){
			
				wt = false;
											
				if (A(i).gettype == 'p'){
					int exposure=A(i).getexposure();
					string photoName=A(i).getphotoName();
						
													
				/// stub ?							
						}
				else if (A(i).gettype == 'a'){

					int pitch=A(i).getpitch();
					int yaw=A(i).getyaw();
					int roll=A(i).getroll();
						

				///stub ?

					}
						
				}
			}
		

	    }
 
}

Plan PlanManager::generatePlan(const char* filepath){
	
	unsigned int version;
	unsigned int num_plan;

	string s = filepath;
	version = s[4];
	num_plan = s[6];
	Plan myPlan(version, num_plan);
	myPlan.loadPlan(filepath);
	myPlan.printPlan();
}
