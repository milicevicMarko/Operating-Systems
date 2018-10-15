/*
 * timer.cpp
 *
 *  Created on: Aug 16, 2018
 *      Author: OS1
 */

#include "timer.h"
#include "PCB.h"
#include "fakeTrd.h"
#include "BlckList.h"
#include "PCBList.h"


volatile int counter = 10;
volatile unsigned tss = 0, tsp = 0, tbp = 0;
pInterrupt oldIR;
PCB *mainPcb;
void tick();


void interrupt timer(...) {
	//nema potrebe da se blokira, tajmer je blokrian sam po sebi
//	printf("req = %d ", PCB::request);
//	printf("usao u interrupt jer je ");
	if (counter == 0 || PCB::request) {
//
//		unsigned ss = PCB::running->ss;
//		unsigned sp = PCB::running->sp;
//		unsigned bp = PCB::running->bp;
//		printf("%x %x %x \n", ss,sp, bp);
		//radi testiranja
//		if (PCB::request != 0)
//			printf("context switch requested\n");
//		else
//			printf("counter=0\n");
		//radi testiranja

#ifndef BCC_BLOCK_IGNORE
		asm {
			mov tss, ss;
			mov tsp, sp;
			mov tbp, bp;
		}
#endif

		PCB::running->ss = tss;
		PCB::running->sp = tsp;
		PCB::running->bp = tbp;

//		printf("stari running: %d\n", PCB::running->getID());

		if (PCB::running->state == RUNNING
				&& PCB::running != FakeThread::idle->getMyPCB()) { //fake ne sme u scheduler

			PCB::running->state = READY;
				//printf("cu metnem u skedz %d, status %s\n", PCB::running->getID(), PCB::running->state);
			Scheduler::put(PCB::running);

		}

		PCB::running = Scheduler::get();
		//while(PCB::running->state!=READY){
		if (PCB::running == 0) { //ako je prazan scheduler stavi na beskonacnu
			PCB::running = FakeThread::idle->getMyPCB();
//			printf("prazan sch\n");
			//break;
		}// else {
//			printf("novi running: %d\n", PCB::running->getID());
//		}
		PCB::running->state = RUNNING;
		counter = PCB::running->getTimeSlice();

		tsp = PCB::running->sp;
		tss = PCB::running->ss;
		tbp = PCB::running->bp;


//		printf("novi counter je %d\n", counter);

#ifndef BCC_BLOCK_IGNORE
		asm {
			mov sp, tsp;
			mov ss, tss;
			mov bp, tbp;
		}
#endif
	}

	if (!PCB::request) {
		//printf("counter: %d		 id:%d\n", counter, PCB::running->getID());
		counter--;
		tick();
		asm int 60h;
		//oldIR();
		BlockList::oneInstance->decrement();
			//stari interrupt
}
//	if(PCB::running->getID()==6)
		//printf("novi running: %d\n", PCB::running->getID());
	//reseting request
	PCB::request = 0;
}

void inic() {
	counter=10;
	PCB::request=0;
#ifndef BCC_BLOCK_IGNORE


	asm pushf;
	asm cli;

	oldIR = getvect(0x8);
	setvect(0x8, timer);
	setvect(0x60, oldIR);

	asm popf;
	#endif

}

void restore() {

	#ifndef BCC_BLOCK_IGNORE
	asm pushf;
	asm cli;

	setvect(0x8, oldIR);

	asm popf;
	#endif

//	printf("resotre uspesan");
}

