#include "BlckList.h"
//

BlockList* BlockList::oneInstance=new BlockList();

BlockList::~BlockList(){
	List* toDel=first;
	while(toDel!=0){
		first=first->next;
		delete toDel;
		toDel=first;
	}
	first=0;
	last=0;
}

void BlockList::add(PCB* pcb) {
	if (first == 0) {
		last = new List(pcb, pcb->getTimeToSleep());
		first = last;
	} else {
		int diff = first->slice - pcb->getTimeToSleep(); //? first - new ?
		if (diff >= 0) { //treba novi prvi
			//printf("treba novi prvi jer je %d  <= %d\n", pcb->getTimeToSleep(), first->slice);
			List* newNode = new List(pcb, pcb->getTimeToSleep()); //List(newPCB, 5, null) primer iz pdfa
			first->slice = diff;
			newNode->next = first;
			first = newNode;
		} else if (diff < 0) { //first<new, ide se u dubinu (5-6)
			//printf("ide se dublje!\n");
			List* curr = first->next;
			List* old = first;
			diff *= -1;
			while (curr != 0) {
				int newDiff = diff - curr->slice; //ovde si okrenuo na new - diff vodi racuna kad isprobavas
				if (newDiff <= 0) {
					curr->slice=(-1)*newDiff;
					old->next = new List(pcb, diff, curr);
					return;
				} else {
					diff = newDiff;
					old = old->next;
					curr = curr->next;
				}
			}
			//last
			last->next = new List(pcb, diff);
			last = last->next;
		}
	}
}

int BlockList::empty(){
	if(first==0 && last==0)
		return 1;
	else
		return 0;
}

//skida sve koji imaju 0 slice
void BlockList::putAllZeros() {
	List* curr = first;
	while (curr != 0 && curr->slice == 0) {
		curr->pcb->makeReady();//state=ready, scheduler.put
		first = curr->next;
		delete curr;
		curr = first;
	}
	if (first == 0) {
		first = last = 0;
	}

}

void BlockList::decrement() {
	if (first != 0) {
		first->slice--;
		if (first->slice == 0) {
			putAllZeros();
		}
	}
}

void BlockList::printAll() const {
	List* curr = first;
	printf("============all are under==========\n");
	if(first==0 && last==0)
		printf("List is empty!");
	else{
		while (curr != 0) {
			printf("[%d, %d] -> ", curr->pcb->getID(), curr->slice);
			curr = curr->next;
		}
	}
	printf("\n===================================\n");
}

