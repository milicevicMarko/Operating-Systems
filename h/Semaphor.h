/*
 * semaphore.h
 *
 *  Created on: Aug 15, 2018
 *      Author: OS1
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

class KernelSem;
//
class Semaphore{
public:
	Semaphore(int init=1);
	virtual ~Semaphore();

	virtual int wait(int toBlock); //ako je 0 nece da se blokira i vraca -1 kao gresku
	virtual void signal();

	int val() const;

private:
	KernelSem* myImpl;
};



#endif /* SEMAPHORE_H_ */
