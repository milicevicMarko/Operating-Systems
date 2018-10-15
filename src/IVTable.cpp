/*
 * IVTable.cpp
 *
 *  Created on: Aug 28, 2018
 *      Author: OS1
 */

#include "IVTable.h"

IVTable* IVTable::table = new IVTable();

IVTable::~IVTable(){
	for(int i=0; i<256; i++)
			entries[i]=0;
	delete entries;
}
//
IVTable::IVTable(){
	for(int i=0; i<256; i++)
		entries[i]=0;
}
