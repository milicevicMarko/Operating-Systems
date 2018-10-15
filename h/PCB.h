/*
 * PCB.h
 *
 *  Created on: Aug 9, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include "Thread.h"
#include "WaitList.h"
#include "PCBList.h"
#include "SCHEDULE.H"
#include "dos.h"
#include <STDIO.H>

enum State {
	NEW, RUNNING, READY, BLOCKED, FINISHED
};
#ifndef BCC_BLOCK_IGNORE
#define lock() asm {pushf; cli; }
#define unlock() asm popf
#endif

class WaitList;
class PCBList;

//

class PCB {
public:

	PCB(Thread* tr=0, StackSize stackSize = 4096, Time timeSlice = 2);
	~PCB();
	void start();
	static void wrapper();

	void waitToComplete();
	static void sleep(Time timeToSleep);

	int getTimeSlice() const {
		return timeSlice;
	}
	int getTimeToSleep() const{
		return timeToSleep;
	}
	int getID() const{
		return id;
	}
	Thread* getThread() const{
		return thread;
	}
	static void callRequest();

	static void printStack(PCB* pcb);

	void makeReady();

	State state;
	static PCB* running;
	volatile unsigned sp;
	volatile unsigned ss;
	volatile unsigned bp;
	 static int request;
protected:
	friend class Thread;
	friend class ContextChange;
private:
	 WaitList* waitList;
	 static PCBList* allPCBs;


	Thread* thread;


	Time timeSlice;
	Time timeToSleep;
	StackSize stackSize;
	static int ID;
	int id;

	unsigned* stack;
};

#endif /* PCB_H_ */
