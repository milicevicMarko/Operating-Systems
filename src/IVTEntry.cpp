/*
 * IVTEntry.cpp
 *
 *  Created on: Aug 26, 2018
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "IVTable.h"
#include "DOS.H"
#include "KernelEv.h"
#include "STDIO.H"

IVTable* IVTEntry::table=IVTable::table;

IVTEntry::IVTEntry(int numEntry, pInterrupt intr) {
	//numEntry mora da bude manji od 256
	//printf("Ivtentry %d\n", numEntry);
	lock;
	if(numEntry<0 || numEntry>255)
		printf("greska: numEntry<0 || numEntry>255");

	entry = numEntry;
#ifndef BCC_BLOCK_IGNORE
	oldIR=getvect(entry);
	setvect(entry, intr);
#endif

//	kerEv= new KernelEv(entry);
	table->entries[entry] = this;
	unlock;
	//stavi u tabelu u svoj ulaz
}

IVTEntry::~IVTEntry(){
	//restore
	lock;
#ifndef BCC_BLOCK_IGNORE
	setvect(entry, oldIR);
#endif
	unlock;
	IVTable::table->entries[entry] = 0;
	kerEv=0;
	//eventualno oldIR=0;
	//ali nema potrebe svakako ce se isto pozivati zbog restorea
}
//
void IVTEntry::callOld(){
	//printf("call old 1\n");
	oldIR();
}

void IVTEntry::signal() {
	lock;
	//printf("ivtentry signal");
	kerEv->signal();
	unlock;
}

void IVTEntry::setSem(KernelEv* ke){
	kerEv=ke;
}
