/******************************************************************************

** Student Name: <Jeffin Poovely>

** Student Number: <s3656024>

** Date of submission: <Fri, 13 Oct 2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/
#include "vm_menu.h"


void initMenu(MenuItem * menu)
{
    strcpy(menu[DISPLAY_S_MENU].text, "1. Display Items");
    menu[DISPLAY_S_MENU].function = &displayItems;

    strcpy(menu[PURCHASE_MENU].text, "2. Purchase Items");
    menu[PURCHASE_MENU].function = &purchaseItem;

    strcpy(menu[SAVE_EXIT_MENU].text, "3. Save and Exit");
    menu[SAVE_EXIT_MENU].function = &saveAndExit;

    strcpy(menu[ADD_MENU].text, "4. Add Item");
    menu[ADD_MENU].function = &addItem;

    strcpy(menu[REMOVE_MENU].text, "5. Remove Item");
    menu[REMOVE_MENU].function = &removeItem;

    strcpy(menu[DISPLAY_C_MENU].text, "6. Display Coins");
    menu[DISPLAY_C_MENU].function = &displayCoins;

    strcpy(menu[RESET_S_MENU].text, "7. Reset Stock");
    menu[RESET_S_MENU].function = &resetStock;

    strcpy(menu[RESET_C_MENU].text, "8. Reset Coins");
    menu[RESET_C_MENU].function = &resetCoins;

    strcpy(menu[ABORT_MENU].text, "9. Abort Program");
    menu[ABORT_MENU].function = &abortProgram;

}

MenuFunction getMenuChoice(MenuItem * menu)
{
    char *endPtr;
    char choice[5];
    int i = INIT_ZERO;
    for(;i < ABORT_MENU; ++ i)
    {
        printf("%s",menu[i].text);
        printf("\n");
    }

    printf("Select your option (1-9): ");
    fgets(choice, sizeof(choice),stdin);

    if(choice[strlen(choice)-1] != '\n')
    {
        printf("Too many values entered. Try again\n\n");
        readRestOfLine();
    }
    else if (choice[0] != '\n') {
        removeNewLine(choice);
        i = (int) strtol(choice, &endPtr, BASE_TEN);
        return menu[--i].function;
    }
    return NULL;
}