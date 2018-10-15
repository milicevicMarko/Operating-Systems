/*
 * IVTable.h
 *
 *  Created on: Aug 27, 2018
 *      Author: OS1
 */

#ifndef IVTABLE_H_
#define IVTABLE_H_

class IVTEntry;

class IVTable{
public:
	IVTable();
	~IVTable();
	IVTEntry *entries[256];
	static IVTable* table;//one isntance
};

//

#endif /* IVTABLE_H_ */
