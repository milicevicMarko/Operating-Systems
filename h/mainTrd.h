/*
 * mainTrd.h
 *
 *  Created on: Aug 21, 2018
 *      Author: OS1
 */

#ifndef MAINTRD_H_
#define MAINTRD_H_
#include "thread.h"


class MainThread:public Thread{
public:
	static MainThread* oneInstance;
	MainThread():Thread(){
//		printf("Main t prosao \n");
	}
	~MainThread();
	void run();
	static void setArgs(int argc, char* argv[]);
	static int getValue(){
		return retVal;
	}
//
private:
	static int argc;
	static char** argv;
	static int retVal;
};

#endif /* MAINTRD_H_ */
