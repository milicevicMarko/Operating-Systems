/*
 * WaitList.h
 *
 *  Created on: Aug 9, 2018
 *      Author: OS1
 */

#ifndef WAITLIST_H_
#define WAITLIST_H_
#include "PCB.h"//ovo je mozda greska
//
class WaitList {
private:
	struct List {
		PCB *pcb;
		List *next;

		List(PCB *p, List *s = 0) :
				pcb(p), next(s) {
		}
	};
	List *first, *last;
public:

	WaitList() :
			first(0), last(0) {
	}
	~WaitList();
	void add(PCB* pcb);
	PCB* getFirst();
	void readyAll();
};

#endif /* WAITLIST_H_ */
