/*
 * thread.cpp
 *
 *  Created on: Aug 9, 2018
 *      Author: OS1
 */
#include "Thread.h"
#include "PCB.h"
#include "timer.h"

void Thread::start() {
	myPCB->start();
}

void Thread::sleep(Time timeToSleep) {
	PCB::sleep(timeToSleep);
}

void Thread::waitToComplete() {
	myPCB->waitToComplete();
}
//
Thread::~Thread() {
	myPCB->waitToComplete();
	delete myPCB;
}

Thread::Thread(StackSize stackSize, Time timeSlice) {
	//create new pcb and send all pars to pcb contructor

	myPCB = new PCB(this, stackSize, timeSlice);
}

void dispatch(){
//	printf("desih se %d\n", PCB::running->getID());
	asm pushf;
	asm cli;
	PCB::callRequest();
	asm popf;
}

int Thread::getID() const{
	return myPCB->getID();
}

