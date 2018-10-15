/*
 * WaitList.cpp
 *
 *  Created on: Aug 9, 2018
 *      Author: OS1
 */

#include "WaitList.h"

void WaitList::add(PCB* pcb) {//na pocetak
	//printf("%d is waiting for to complete %d\n", PCB::running->getID(),pcb->getID());
	if (first == 0) {
		first = new List(pcb);
		last = first;
	} else {
		List* newNode=new List(pcb, first);
		first=newNode;
	}
	pcb->state=BLOCKED;
}

PCB* WaitList::getFirst() {
	if(first==0)
		return 0;
	PCB* ret = first->pcb;
	List* old = first;
	first = first->next;
	delete old;
	if (first == 0)
		last = 0;
	ret->makeReady();
	return ret;
}

WaitList::~WaitList() {
	readyAll();
	delete first;
	delete last;
}
//
void WaitList::readyAll(){
	List* curr=first;
	while(curr){
		curr->pcb->makeReady();//state->ready, sch->put
		first=curr->next;
		delete curr;
		curr=first;
	}
	first=last=0;
}
