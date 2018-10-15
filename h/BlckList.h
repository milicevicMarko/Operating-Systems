/*
 * BlockList.h
 *
 *  Created on: Aug 10, 2018
 *      Author: OS1
 */

#ifndef BLCKLIST_H_
#define BLCKLIST_H_

#include "PCB.h"
class BlockList {
private:
	struct List {
		PCB *pcb;
		int slice;
		List *next;
		List(PCB *p, int sl, List *s = 0) :
				pcb(p), slice(sl), next(s) {
		}

	};
	List *first, *last;
//
public:
	static BlockList* oneInstance;
	BlockList() :
			first(0), last(0) {
	}
	~BlockList();
	void add(PCB* pcb);
	int empty();
	void decrement();
	void putAllZeros();
	void printAll() const;

};

#endif /* BLCKLIST_H_ */
