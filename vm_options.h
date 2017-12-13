/******************************************************************************

** Student Name: <Jeffin Poovely>

** Student Number: <s3656024>

** Date of submission: <Fri, 13 Oct 2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/
#ifndef VM_OPTIONS_H
#define VM_OPTIONS_H

#include "vm_stock.h"

#define DENOMTEXTSIZE 14
#define INIT_ZERO 0
#define LINE_SIZE 500
#define MAX_ONE_DIGIT_NUMBER 9
#define COINTPRINTSIZE 20
#define BASE_TEN 10
#define DECIM_CONVERTOR 100.0
#define NAME_LENGTH 4
#define RETURN_TO_MENU 0
#define MAX_TWO_DIGIT_NUMBER 99
#define DIVIDE_BY_FIVE 0
Boolean systemInit(VmSystem * system);
void systemFree(VmSystem * system);
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName);
Boolean loadStock(VmSystem * system, const char * fileName);
Boolean loadCoins(VmSystem * system, const char * fileName);
Boolean saveStock(VmSystem * system);
Boolean saveCoins(VmSystem * system);

void displayItems(VmSystem * system);
void purchaseItem(VmSystem * system);
void saveAndExit(VmSystem * system);
void addItem(VmSystem * system);
void removeItem(VmSystem * system);
void errorCheckPrice(Price *tempPrice);
void displayCoins(VmSystem * system);
void resetStock(VmSystem * system);
void resetCoins(VmSystem * system);
void abortProgram(VmSystem * system);
void givingMoney(unsigned int productCost,Node * node,VmSystem *system);
int checkValidAmount(char *x);
void removeNewLine(char* x);

int differenceName,nameLength;

#endif
