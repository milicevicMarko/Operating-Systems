/*
 * thread.h
 *
 *  Created on: Aug 8, 2018
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_
#include <stdio.h>

//#include "Defs.h"

typedef unsigned long StackSize;
typedef unsigned int Time; // time, x 55msS

#include "Defs.h"

const StackSize defaultStackSize = 4096;//2048;
const Time defaultTimeSlice = 5; // default = 5*55mss

class PCB;
//
class Thread {
public:
	void start();
	void waitToComplete();
	virtual ~Thread();
	static void sleep(Time timeToSleep);
	PCB* getMyPCB(){
		return myPCB;
	}
	int getID() const;
		int getId() const{//zbog testova
			return getID();
		}
protected:
	friend class PCB;
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice =
			defaultTimeSlice);
	virtual void run() {
	}

private:
	PCB* myPCB;
};

void dispatch();
void interrupt timer(...);


#endif /* THREAD_H_ */
