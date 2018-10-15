/*
 * fakeTrd.h
 *
 *  Created on: Aug 11, 2018
 *      Author: OS1
 */
//
#ifndef FAKETRD_H_
#define FAKETRD_H_
#include "thread.h"


class FakeThread: public Thread{
public:
	FakeThread():Thread(0,1){
		//printf("fake prosao\n");
	}; //stack 0, time slice 1
	~FakeThread(){};
	void run();
	static FakeThread* idle;


};


#endif /* FAKETRD_H_ */
