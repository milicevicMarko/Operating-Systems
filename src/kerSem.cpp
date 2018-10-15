/*
 * kerSem.cpp
 *
 *  Created on: Aug 15, 2018
 *      Author: OS1
 */

#include "kerSem.h"
#include "PCBList.h"
#include "PCB.h"
#include "Event.h"

//SemList* allSems = new SemList();
//int KernelSem::ID=0;
//
KernelSem::KernelSem(int initialVal) {
	lock;
	value = initialVal;
	waitingList=new PCBList();
	unlock;
	//id=ID++;
	//allSems->add(this);
}
KernelSem::~KernelSem() {
	lock;
	delete waitingList;
	unlock;
	//allSems->deleteId(id);
}

int KernelSem::wait(int toBlock) { //april 2014
//	printf("%d pozvao wait\n", PCB::running->getID());
	//printf("wait semafor je %d\n", value);
	lock;
	 int ret = 0;
	 if (!toBlock && value<=0)
	 ret = -1;
	 else
	 if (--value<0) {
	 ret = 1;
	 			PCB::running->state=BLOCKED;
	 			waitingList->add(PCB::running);
	 		//	printf("ker sem: \n");waitingList->printAll();
	 		//	printf("treba mi dispatch jer sam blokriao nit %d\n", PCB::running->getID());
	 			dispatch();
	 }
	 unlock;
	 return ret;

}
void KernelSem::signal() {

	//printf("signal semafora je %d\n", value);
//	asm pushf;
//	asm cli;
	lock;
	value++;
	if(value<=0){
		PCB* toPut=waitingList->getFirst();//vraca 0 ako nema nista zato ispitujem da ne bih 0-thread stavio u scheduler
		if(toPut){
			toPut->makeReady();//state=ready, scheduler::put
		}
	}
	unlock;
	//asm popf;
}

int KernelSem::getValue() const {
	return value;
}


