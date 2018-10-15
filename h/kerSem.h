/*
 * kerSem.h
 *
 *  Created on: Aug 15, 2018
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_
//
class PCBList;
class BlockList;

class KernelSem{
public:
	KernelSem(int initialVal=1);
	virtual ~KernelSem();

	virtual int wait(int toBlock); //ako je 0 nece da se blokira i vraca -1 kao gresku
	virtual void signal();

	int getValue() const;

protected:
	int value;
	PCBList *waitingList;//cuva blokirane na semaforu
//private:
//	//static SemList* allSems;
//	//static int ID:
//	//int id;
};



#endif /* KERSEM_H_ */
