/*
 * SemList.cpp
 *
 *  Created on: Aug 15, 2018
 *      Author: OS1
 */

#include "PCBList.h"
#include "PCB.h"

//

PCBList::PCBList() {
	first = last = 0;
}
PCBList::~PCBList() {
	List* curr = first;
	while (curr != 0) {
		//curr->pcb->makeReady(); //ne mogu da tvrdim da treba da se stavi u sch
		first = first->next;
		delete curr;
		curr = first;
	}
	first = 0;
	last = 0;
}

void PCBList::add(PCB* pcb) {
	//printf("zelim da dodam: %d\n", pcb->getID());
	//cout<<first<<endl;
//ne dodaje 0 nikad
	if (first == 0) {
		//printf("prvi: %d\n", pcb->getID());
		first = last = new List(pcb);
	} else {
		//printf("else: %d\n", pcb->getID());
		last = last->next = new List(pcb);
//		List* newNode= new List(pcb,first);
//		first=newNode;
	}
}
PCB* PCBList::getFirst() {
	PCB* ret;
	if (first == 0)
		return 0;
	else{
		List* toDel=first;
		ret = first->pcb;
	first = first->next;
	delete toDel;//!!!!!!!!!!!!!!!!!!!!!!!!!dodao u post produkciji
	if (first == 0)
		last = 0;
	return ret;
	}
}

PCB* PCBList::find(int id) {
	List* curr = first;
	while (curr != 0) {
		if (curr->pcb->getID() == id)
			return curr->pcb;
		else
			curr = curr->next;
	}
	return 0; //didnt find
}

void PCBList::deleteID(int id) {
	List* curr = first, *prev = 0;
	while (curr != 0) {
		if (curr->pcb->getID() == id) {
			if (prev != 0)
				prev->next = curr->next;
			else {
				first = curr->next;
				if (first == 0)
					last = first;
			}
			delete curr;
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

int PCBList::getSize() const {
	List* curr = first;
	int size = 0;
	while (curr != 0) {
		size++;
		curr = curr->next;
	}
	return size;
}

void PCBList::printAll() const {
	List* curr = first;
	int size = 0;
	while (curr != 0) {
		printf("%d\n", curr->pcb->getID());
		curr = curr->next;
	}
}

void PCBList::startAll() const{
	List* curr = first;
		int size = 0;
		while (curr != 0) {
			//printf("pokrenuo %d\n", curr->pcb->getID());
			curr->pcb->start();
			curr = curr->next;
		}
}

