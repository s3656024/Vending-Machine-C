/******************************************************************************

** Student Name: <Jeffin Poovely>

** Student Number: <s3656024>

** Date of submission: <Fri, 13 Oct 2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/
#ifndef VM_STOCK_H
#define VM_STOCK_H

#include "vm_coin.h"

/**
 * The default stock level that all new stock should start with and the value
 * to use when restting stock.
 **/

#define DEFAULT_STOCK_LEVEL 20

#define STOCK_DELIM "|"
void addToList(VmSystem *vmSystem, Stock * stock);
void findLocation(List *list, Node *newNode);
void initList(List *list);
Boolean removeNode(VmSystem *system, char *deleteID);
#endif
