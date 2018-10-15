/*
 * trd1.h
 *
 *  Created on: Aug 16, 2018
 *      Author: OS1
 */

#ifndef TRD1_H_
#define TRD1_H_

#include "thread.h"
#include <stdio.h>


//volatile Time ts;
//
//void tick()
//{
//	printf("timeSlice=%d\n",ts);
//}
//

class Thread1: public Thread{
public:
	void run(){
		for(int i=0; i<2; i++){
				printf("run od %d\n", getID());
		}
	}
	Thread1(int i, int j):Thread(i,j){}
	Thread1():Thread(){}
};



#endif /* TRD1_H_ */
