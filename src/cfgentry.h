/* cfgentry.h:     classes for config read from a file
 *
 * Copyright (c) 2012, by:      Sebastian Riemer
 *    All rights reserved.      Ernst-Reinke-Str. 23
 *                              10369 Berlin, Germany
 *                             <sebastian.riemer@gmx.de>
 *
 * This file may be used subject to the terms and conditions of the
 * GNU Library General Public License Version 2, or any later version
 * at your option, as published by the Free Software Foundation.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 */

#ifndef CFGENTRY_H
#define CFGENTRY_H

#include <string>
#include <list>
using namespace std;

typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;

#ifdef __i386__
typedef u32 ptr_t;
#else
typedef u64 ptr_t;
#endif

enum {
	DO_UNCHECKED,
	DO_LT,
	DO_GT
};

class CheckEntry {
public:
	void *addr;
	bool is_signed;
	i32 size;
	long value;
	i32 check;
};

class DynMemEntry {
public:
	size_t mem_size;
	void *code_addr;
	void *stack_offs;
	void *mem_addr;  /* filled by malloc for free */
};

class CfgEntry {
public:
	string name;
	void *addr;
	bool is_signed;
	i32 size;
	long value;
	long old_val;
	i32 check;
	list<CheckEntry> *checks;
	DynMemEntry *dynmem;
};

#endif
