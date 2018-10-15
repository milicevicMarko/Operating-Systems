/*
 * main.cpp
 *
 *  Created on: Aug 8, 2018
 *      Author: OS1
 */

#include <stdio.h>
#include "PCB.h"
#include "thread.h"
#include "fakeTrd.h"
#include "mainTrd.h"
#include "BlckList.h"
#include "timer.h"


//
FakeThread*	FakeThread::idle=new FakeThread();//id 0
MainThread*	MainThread::oneInstance=new MainThread();//id 1


int main(int argc, char* argv[]){

		asm pushf;
		asm cli;
		PCB* mainPcb = new PCB(0, 0, 1);	//podrazumevane, ne treba mu thread, nema stek, time slice 1

		mainPcb->state = RUNNING;
		PCB::running = mainPcb;

		asm popf;
		inic();




		MainThread::oneInstance->setArgs(argc, argv);
	//printf("\nprosla dodela argumenata, running je %d\n", PCB::running->getID());


		MainThread::oneInstance->start();

//	printf("running je %d\n", PCB::running->getID());
//	printf("pre brisanja main tr request je %d\n", PCB::request);
	delete MainThread::oneInstance;

	restore();
	int ret =  MainThread::oneInstance->getValue();

	asm pushf;
	asm cli;
	delete mainPcb;
	delete FakeThread::idle;
	delete BlockList::oneInstance;
	asm popf;


	PCB* errorSched = Scheduler::get();
	if(errorSched!=0)
		printf("ostala u scheduleru: %d", errorSched->getID());
	printf("\n>>exit(%d)", ret);
	return ret;
}


