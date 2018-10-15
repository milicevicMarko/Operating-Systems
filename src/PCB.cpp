/*
 * PCB.cpp
 *
 *  Created on: Aug 9, 2018
 *      Author: OS1
 */
#include "Event.h"
#include "PCB.h"
#include "BlckList.h"
#include "PCBList.h"
#include "fakeTrd.h"

int PCB::ID = 0;
int PCB::request = 0;
//PCBList* PCB::allPCBs = new PCBList();

void PCB::callRequest() {
	PCB::request = 1;
	asm int 8h;
}

PCB* PCB::running = 0;

PCB::PCB(Thread* trd, StackSize AstackSize, Time timeSlice) {
if (stackSize > 65535)
	stackSize = 65534;

stackSize = AstackSize / sizeof(unsigned);
stack = new unsigned[stackSize];

this->timeSlice = timeSlice;
this->timeToSleep = 0;
this->state = NEW;
this->thread = trd;

id = ID++;
//
waitList = new WaitList();
//
#ifndef BCC_BLOCK_IGNORE
stack[stackSize - 1]=0x200; //psw setovan I bit
stack[stackSize - 2]=FP_SEG(PCB::wrapper);
stack[stackSize - 3]=FP_OFF(PCB::wrapper);//pc za funkciju wrapper

ss=FP_SEG(stack+stackSize - 12);
sp=FP_OFF(stack+stackSize - 12);
bp=sp;
#endif
//	if(id==1){
//		printf("zovem za 1: %d\n", id);
//		printStack(this);
//	}
//printf("\nzavrsio konstruktor niti %d\n", id);
}
PCB::~PCB() {
	delete waitList;
	delete[] stack;
	thread=0;
	//delete thread; greska, pcb je pozvan od strane thread destruktora
	//	PCB::allPCBs->deleteID(getID());//deletes this thread from the global list
}

void PCB::start() {
//	asm pushf;
//	asm cli;
	lock;
	if (this->state == NEW && this != FakeThread::idle->getMyPCB()) {
		this->state = READY;
		Scheduler::put(this);
		//printf("stavio %d u skedz\n", id);
	}
	unlock;
//	asm popf;
}

void PCB::waitToComplete() {
	// status na blokiran i promeniti kontekst
	//proveriti da nije beskonacna, da nije to ta ista ili da nije gotova
	//printf(" wtc usao: this: %d vs runn: %d\n", id,PCB::running->getID());
	if (this != PCB::running && this->state != FINISHED && this->state != NEW
		&& this != FakeThread::idle->getMyPCB()) {
		PCB::running->state = BLOCKED;
		waitList->add(PCB::running);
		//	printf("blokirao %d \n", PCB::running->getID());
		dispatch();
	}
}

	//running timetosleep
void PCB::sleep(Time timeToSleep) {
	PCB::running->timeToSleep = timeToSleep;
	//printf("trd %d sleeping: %d\n", PCB::running->getID(), timeToSleep);
	if (timeToSleep == 0) {
		//specijalan slucaj
		dispatch();
	} else {
		PCB::running->state = BLOCKED;
		BlockList::oneInstance->add(PCB::running);
		dispatch();
	}
}

void PCB::wrapper() {
	//printf("\n\nwrap od %d\n\n", PCB::running->id);
	PCB::running->thread->run();
	PCB::running->waitList->readyAll();
	PCB::running->state = FINISHED;
	//printf("Zavrsavam thread %d\n", PCB::running->id);
	dispatch();
}

void PCB::makeReady() {
	state = READY;
	Scheduler::put(this);
}

void PCB::printStack(PCB* pcb) {
	printf("stek size: %d\n", pcb->stackSize);
	printf("stek -1 %x ", pcb->stack[pcb->stackSize - 1]);
	printf("stek -2 %x ", pcb->stack[pcb->stackSize - 2]);
	printf("stek -3 %x \n", pcb->stack[pcb->stackSize - 3]);

	printf("ss %x\n", pcb->stack + pcb->stackSize - 12);
	printf("sp %x\n", pcb->stack + pcb->stackSize - 12);
	printf("bp %x\n", pcb->stack + pcb->stackSize - 12);

}

