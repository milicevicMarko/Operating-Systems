/*
 * semaphore.cpp
 *
 *  Created on: Aug 15, 2018
 *      Author: OS1
 */

#include "Semaphor.h"
#include "Event.h"
#include "kerSem.h"
//
Semaphore::Semaphore(int init) {
	lock;
	myImpl = new KernelSem(init);
	unlock;
}
Semaphore::~Semaphore() {
	lock;
	delete myImpl;
	unlock;
}

int Semaphore::wait(int toBlock) {
	lock;//ako je 0 nece da se blokira i vraca -1 kao gresku
	int ret = myImpl->wait(toBlock);
	unlock;
	return ret;
}
void Semaphore::signal() {
	lock;
	myImpl->signal();
	unlock;
}

int Semaphore::val() const {
	lock;
	int ret = myImpl->getValue();
	lock;
	return ret;
}

