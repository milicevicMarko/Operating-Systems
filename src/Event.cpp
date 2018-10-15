/*
 * Event.cpp
 *
 *  Created on: Aug 21, 2018
 *      Author: OS1
 */
#include "Event.h"
#include "KernelEv.h"
#include "STDIO.H"

//

extern volatile int lockSem=0;

Event::Event(IVTNo ivtNo){
	lock;
	myImpl=new KernelEv(ivtNo);
	unlock;
}
Event::~Event(){
	lock;
	delete myImpl;
	unlock;
}

void Event::wait(){
	//printf("!ovamo cigani!\n");
	lock;
	myImpl->wait();
	unlock;
}

void Event::signal(){
	lock;
	myImpl->signal();
	unlock;
}
