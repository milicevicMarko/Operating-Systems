/*
 * IVTEntry.h
 *
 *  Created on: Aug 26, 2018
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
//#include "Event.h"
#include "Defs.h"
//#include "KernelEv.h"


//

class IVTable;
class KernelEv;

class IVTEntry{
public:
	IVTEntry(int no, pInterrupt intr);

	~IVTEntry();

	void signal();
	void callOld();
	void setSem(KernelEv* ke);

	int entry;//entry 0-255
	static IVTable* table;

	pInterrupt oldIR;

	KernelEv *kerEv;
};

#endif /* IVTENTRY_H_ */
