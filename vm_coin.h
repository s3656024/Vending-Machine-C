/******************************************************************************

** Student Name: <Jeffin Poovely>

** Student Number: <s3656024>

** Date of submission: <Fri, 13 Oct 2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/
#ifndef VM_COIN_H
#define VM_COIN_H

#include "vm_system.h"

/**
 * The default coin level used when resetting values.
 **/
#define DEFAULT_COIN_COUNT 20

#define COIN_DELIM ","

#define FIVE_C 5
#define TEN_C 10
#define TWENTY_C 20
#define FIFTY_C 50
#define ONE_D 100
#define TWO_D 200
#define FIVE_D 500
#define TEN_D 1000
#define ZERO_COINS 0
#define CHANGE 0
Boolean exactchange (double change,VmSystem * system);
int convertDenominToInt (Denomination denom);
Denomination convertIntToDenom (int cash);
void convertDenomtoStr (Denomination cash, char* coin);
void addCoin (int coin,VmSystem *system);
Boolean checkChangePossible(int change,VmSystem *system);
int findDenomLocation(int amount,VmSystem *system);
#endif
