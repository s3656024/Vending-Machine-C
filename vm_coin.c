/******************************************************************************

** Student Name: <Jeffin Poovely>

** Student Number: <s3656024>

** Date of submission: <Fri, 13 Oct 2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/
#include "vm_coin.h"

/**
 * Implement functions here for managing coins and the
 * "cash register" contained in the VmSystem struct.
 **/

/**
 * Some example functions:
 * init coins array, insert coin, change coin count for Denomination,
 * convert Denomination to coin value, deducting coins from register, etc...
 */
Boolean exactchange (double change, VmSystem * system)
{
/* giving change to the customer, it starts off at the highest denomination and goes downward so the highest denomination will be used first, the location of the denomination
is checked in the cash register and then decreased */
    int cashPosition = CHANGE;
    while (change != CHANGE)
    {
    if (change >= TEN_D &&
            system->cashRegister[findDenomLocation(TEN_D,system)].count > ZERO_COINS)
    {
        printf("$10");
        change = change - TEN_D;
        cashPosition = findDenomLocation(TEN_D,system);
        system->cashRegister[cashPosition].count--;
    }
        else if (change >= FIVE_D &&
                 system->cashRegister[findDenomLocation(FIVE_D,system)].count > ZERO_COINS)
    {
        printf("$5");
        change = change - FIVE_D;
        cashPosition = findDenomLocation(FIVE_D,system);
        system->cashRegister[cashPosition].count--;
    }
    else if (change >= TWO_D&&
             system->cashRegister[findDenomLocation(TWO_D,system)].count > ZERO_COINS)
    {
        printf("$2");
        change = change - TWO_D;
       cashPosition =  findDenomLocation(TWO_D,system);
        system->cashRegister[cashPosition].count--;
    }
    else if (change >= ONE_D&&
             system->cashRegister[findDenomLocation(ONE_D,system)].count > ZERO_COINS)
    {
        printf("$1");
        change = change - ONE_D;
        cashPosition =  findDenomLocation(ONE_D,system);
        system->cashRegister[cashPosition].count--;
    }
    else if (change >= FIFTY_C&&
             system->cashRegister[findDenomLocation(FIFTY_C,system)].count > ZERO_COINS)
    {
        printf("50c");
        change = change - FIFTY_C;
        cashPosition =   findDenomLocation(FIFTY_C,system);
        system->cashRegister[cashPosition].count--;
    }
    else if (change >= TWENTY_C&&
             system->cashRegister[findDenomLocation(TWENTY_CENTS,system)].count > ZERO_COINS)
    {
        printf("20c");
        change = change - TWENTY_C;
        cashPosition =   findDenomLocation(TWENTY_C,system);
        system->cashRegister[cashPosition].count--;
    }
    else if (change >= TEN_C&&
             system->cashRegister[findDenomLocation(TEN_C,system)].count > ZERO_COINS)
    {
        printf("10c");
        change = change - TEN_C;
        cashPosition =  findDenomLocation(TEN_C,system);
        system->cashRegister[cashPosition].count--;
    }
    else if (change >= FIVE_C&&
             system->cashRegister[findDenomLocation(FIVE_C,system)].count > ZERO_COINS)
    {
        printf("5c");
        change = change - FIVE_C;
        cashPosition =  findDenomLocation(FIVE_C,system);
        system->cashRegister[cashPosition].count--;
    }
        else if (system->cashRegister[cashPosition].count == 0)
            break;
        printf(",");
    }
    if (change > 0)
    {
        return FALSE;
    }
    else
        return TRUE;
}
Boolean checkChangePossible(int change,VmSystem *system)
{/* when the purchase item is invoked, this is to find out if there is enough change 
in the cash resgister to complete the purchase */
    int i;
    int total = 0 ;
    int denomConverted;

    for (i =0; i <NUM_DENOMS; ++i)
    {
        denomConverted = convertDenominToInt(system->cashRegister[i].denom);
        denomConverted = denomConverted * system->cashRegister[i].count;
       total = total + denomConverted;
    }
    if (total > change)
        return TRUE;
    else
        return FALSE;
}
int findDenomLocation(int amount,VmSystem *system)
{
/*finding the location of a certain denomination in the cash register to reduce/increase
the amount of */
    int i;
    for (i = ZERO_COINS; i < NUM_DENOMS;++i)
    {
        if(convertDenominToInt(system->cashRegister[i].denom) == amount)
            return i;
    }
    return -1;
}
int convertDenominToInt (Denomination denom)
{
/* to calculate what each denomination represents */
    if (denom == FIVE_CENTS)
        return FIVE_C;
    else if (denom == TEN_CENTS)
        return TEN_C;
    else if ( denom == TWENTY_CENTS)
        return TWENTY_C;
    else if ( denom == FIFTY_CENTS)
        return FIFTY_C;
    else if (denom == ONE_DOLLAR)
        return ONE_D;
    else if (denom == TWO_DOLLARS)
        return TWO_D;
    else if (denom == FIVE_DOLLARS)
        return FIVE_D;
    else
        return TEN_D;
}
Denomination convertIntToDenom (int cash)
{
/* to calculate where in the cash register should the value be stored */
    if ( cash == FIVE_C)
        return FIVE_CENTS;
    else if (cash == TEN_C)
        return TEN_CENTS;
    else if ( cash == TWENTY_C)
        return TWENTY_CENTS;
    else if ( cash == FIFTY_C)
        return FIFTY_CENTS;
    else if (cash == ONE_D)
        return ONE_DOLLAR;
    else if (cash == TWO_D)
        return TWO_DOLLARS;
    else if (cash == FIVE_D)
        return FIVE_DOLLARS;
    else
        return TEN_DOLLARS;
}

void convertDenomtoStr (Denomination cash, char* coin)
{
/* convert the Denomination to a String */
    if ( cash == FIVE_CENTS)
        strcpy(coin,"5 cents");
    else if (cash == TEN_CENTS)
        strcpy(coin,"10 cents");
    else if ( cash == TWENTY_CENTS)
        strcpy(coin,"20 cents");
    else if ( cash == FIFTY_CENTS)
        strcpy(coin,"50 cents");
    else if (cash == ONE_DOLLAR)
        strcpy(coin,"1 dollar");
    else if (cash == TWO_DOLLARS)
        strcpy(coin,"2 dollars");
    else if (cash == FIVE_DOLLARS)
        strcpy(coin,"5 dollars");
    else
        strcpy(coin,"10 dollars");
}

void addCoin (int coin,VmSystem *system)
{
/* once the user puts a coin into the vending machine, add it into the system */
    int i;
    Denomination denom = convertIntToDenom(coin);

    for (i = ZERO_COINS;i <NUM_DENOMS;++i)
    {
        if(system->cashRegister[i].denom == denom)
            system->cashRegister[i].count++;
    }
}
