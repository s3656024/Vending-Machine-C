/******************************************************************************

** Student Name: <Jeffin Poovely>

** Student Number: <s3656024>

** Date of submission: <Fri, 13 Oct 2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/
#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>
#include <math.h>

typedef enum boolean
{
    FALSE = 0,
    TRUE
} Boolean;

#define NEW_LINE_SPACE 1
#define NULL_SPACE 1

/**
 * This is used to compensate for the extra character spaces taken up by
 * the '\n' and '\0' when input is read through fgets().
 **/
#define EXTRA_SPACES (NEW_LINE_SPACE + NULL_SPACE)

#define EMPTY_STRING ""

/**
 * Call this function whenever you detect buffer overflow.
 **/
void readRestOfLine();

#endif
