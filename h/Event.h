/*
 * Event.h
 *
 *  Created on: Aug 21, 2018
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

//
#include "Defs.h"
#include "timer.h"
#include "PCB.h"
#include "IVTEntry.h"

//volatile int lockSem=0;
extern volatile int counter;
extern volatile int lockSem;
#define lock ++lockSem;
#define unlock --lockSem;\
if (lockSem == 0 && counter==0) { counter= 0; dispatch(); }

#define PREPAREENTRY(numEntry, callOldFlag) \
void interrupt inter##numEntry(...); \
IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
void interrupt inter##numEntry(...) { \
	newEntry##numEntry.signal(); \
	if (callOldFlag == 1) \
		newEntry##numEntry.callOld(); \
	dispatch(); \
}

class KernelEv;
class PCB;
class Event{
public:
	Event(IVTNo ivtNo);
	~Event();

	void wait();

protected:
	friend class KernelEv;
	void signal();
private:
	KernelEv* myImpl;
};



#endif /* EVENT_H_ */
