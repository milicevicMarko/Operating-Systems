/*
 * KernelEv.cpp
 *
 *  Created on: Aug 21, 2018
 *      Author: OS1
 */

#include "KernelEv.h"
#include "IVTable.h"
#include "PCB.h"

//
KernelEv::KernelEv(int No){
	lock;
	pcb=PCB::running;//moze da se blokira samo ona koja je napravila semafor
	ivtNo=No;
	semVal=0;
	//printf("semafor sa ulazom %d nad niti br %d\n", ivtNo, pcb->getID());
	IVTable::table->entries[(int) ivtNo]->setSem(this);
	unlock;
}

KernelEv::~KernelEv(){
	IVTable::table->entries[(int) ivtNo]->setSem(0);
	pcb=0;
}

void KernelEv::signal(){
//	asm pushf;
//	asm cli;
	lock;
	if(pcb==0)
			semVal=1;
	else{
			//printf("%d nit is ready\n", pcb->getID());
		//semVal=1;
			pcb->makeReady();//ready, put
	}
	unlock;
//	asm popf;
//	//printf("	spemna je %d	", pcb->getID()); to je ok
}

void KernelEv::wait(){
	lock;
	if(pcb==PCB::running){
		if(semVal==0){//cekam da se desi prekid
			pcb->state=BLOCKED;
			//printf("blokirao %d\n", pcb->getID());
			dispatch();
		}
		else
			semVal=0; //desio se prekid vec
	}
	lock;
}



