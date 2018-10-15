/*
 * KernelEv.h
 *
 *  Created on: Aug 21, 2018
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

//
#include  "Event.h"
//#include "Defs.h"


class PCB;

class KernelEv{
public:
	KernelEv(int No);
	~KernelEv();

	void wait();
	void signal(); //can call KernelEv
protected:

	friend class Event;

	PCB* pcb;
	int ivtNo;
	int semVal;
};


#endif /* KERNELEV_H_ */
