/*
 * PCBList.h
 *
 *  Created on: Aug 15, 2018
 *      Author: OS1
 */

#ifndef PCBLIST_H_
#define PCBLIST_H_



//

class PCB;

class PCBList{
private:
	struct List{
		PCB* pcb;
		List* next;
		List(PCB* p, List* n=0):pcb(p),next(n){};
	};
	List* first, *last;

public:
	PCBList();
	~PCBList();

	void add(PCB* pcb);
	PCB* getFirst();
	PCB* find(int id);
	void deleteID(int id);
	int getSize() const;
	void printAll() const;
	void startAll() const;

};



#endif /* PCBLIST_H_ */
