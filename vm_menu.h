/******************************************************************************

** Student Name: <Jeffin Poovely>

** Student Number: <s3656024>

** Date of submission: <Fri, 13 Oct 2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/
#ifndef VM_MENU_H
#define VM_MENU_H

#include "vm_options.h"

/**
 * The maximum length of a menu item's text.
 **/
#define MENU_NAME_LEN 50

#define DISPLAY_S_MENU 0
#define PURCHASE_MENU 1
#define SAVE_EXIT_MENU 2
#define ADD_MENU 3
#define REMOVE_MENU 4
#define DISPLAY_C_MENU 5
#define RESET_S_MENU 6
#define RESET_C_MENU 7
#define ABORT_MENU 8

/**
 * Represents a function that can be selected from the list of
 * menu_functions - creates a new type called a menu_function.
 */
typedef void (*MenuFunction)(VmSystem *);

/**
 * Represents a menu item to be displayed and executed in the program.
 **/
typedef struct menu_item
{
    char text[MENU_NAME_LEN + NULL_SPACE];
    MenuFunction function;
} MenuItem;

void initMenu(MenuItem * menu);
MenuFunction getMenuChoice(MenuItem * menu);

#endif
