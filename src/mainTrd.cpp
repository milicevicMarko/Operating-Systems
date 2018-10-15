/*
 * mainTread.cpp
 *
 *  Created on: Aug 21, 2018
 *      Author: OS1
 */


#include "mainTrd.h"
#include "Defs.h"
int MainThread::argc = 0;
char** MainThread::argv = 0;
int MainThread::retVal = 0;
//MainThread::MainThread* MainThread::oneInstance = new MainThread();

int userMain (int argc, char* argv[]);


MainThread::~MainThread(){

	waitToComplete();
	//printf("pozvao waittc, sad brisem mainThread\n");
}
//

void MainThread:: run(){
	//printf("usao u run od maint\n");
	MainThread::retVal=userMain(argc,argv);
}
void MainThread:: setArgs(int argc, char** argv){
	MainThread::argc=argc;
	MainThread::argv=argv;
}
