/******************************************************************************

** Student Name: <Jeffin Poovely>

** Student Number: <s3656024>

** Date of submission: <Fri, 13 Oct 2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/
#include "vm.h"
void mainMenu(VmSystem * system){
    char choice[1 + EXTRA_SPACES];
    printf("Main Menu:\n");
    printf("1. Display Items\n");
    printf("2. Purchase Items\n");
    printf("3. Save and Exit\n");
    printf("Administrator Mode Only \n");
    printf("4.Add Item\n");
    printf("5.Remove Item\n");
    printf("6.Display Coins\n");
    printf("7.Reset Stock\n");
    printf("8.Reset Coins\n");
    printf("9.Abort Program\n");
    printf("Select your option (1-9): ");
    fgets(choice, 1 + EXTRA_SPACES, stdin);
    if ( choice[1] != '\n' && choice[0] != '\n')
{        readRestOfLine();
	mainMenu(system);
}
else{
    switch(choice[0])
    {
        case '1':
            displayItems(system);
            break;
        case '2':
            purchaseItem(system);
            break;
        case '3':
            saveAndExit(system);
            break;
        case '4':
            addItem(system);
            break;
        case '5':
            removeItem(system);
            break;
        case '6':
            displayCoins(system);
            break;
        case '7':
            resetStock(system);
            break;
        case '8':
            resetCoins(system);
            break;
        case '9':
            abortProgram(system);
    }
}

}

int main(int argc, char ** argv)
{
    VmSystem *vmHead= malloc(sizeof(VmSystem));
    char sFileName[MAX_FILE_NAME];
    char cFileName[MAX_FILE_NAME];
  /*  char cFileName[MAX_FILE_NAME]; */
if (argc >3  || argc <  1)
{
/* check if the right amount of argc arguments are entered */ 
    printf("Too many arguments have been entered\n");
    systemFree(vmHead);
}
else
{ 
/* copy the file names into a String */
    strcpy(sFileName,argv[1]);
    strcpy(cFileName,argv[2]);
    loadData(vmHead,sFileName,cFileName);
    mainMenu(vmHead);
}
    free(vmHead);
    printf("Goodbye. \n\n");
    return EXIT_SUCCESS;
}
