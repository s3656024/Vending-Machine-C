/******************************************************************************

** Student Name: <Jeffin Poovely>

** Student Number: <s3656024>

** Date of submission: <Fri, 13 Oct 2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/
#include "vm_options.h"
#include "vm.h"
#include <ctype.h>

Boolean systemInit(VmSystem * system)
{
/* setting the system to a safe state so there are no memory leaks */
    int i;
   system->itemList = malloc(sizeof(List));
    system->itemList->head = NULL;
    system->itemList->size = INIT_ZERO;
    system->coinFileName = NULL;
    system->stockFileName = NULL;
    for (i = INIT_ZERO; i < NUM_DENOMS; ++ i)
    {
        system->cashRegister[i].denom = i;
        system->cashRegister[i].count = INIT_ZERO;
    }

    return FALSE;
}

void systemFree(VmSystem * system)
{
/* going through every node that is created and destroying them all */
    Node *currentNode = system->itemList->head;
    Node *previousNode = NULL;
    while (currentNode != NULL)
    {
        previousNode = currentNode;
       currentNode =  currentNode->next;
        free(previousNode->data);
        free(previousNode);
    }
/* finally deleting the system itself */
    free(system->itemList);
}

Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName)
{
/* loads the stock and coin file */
    if (loadStock(system,stockFileName) &&
    loadCoins(system,coinsFileName))
    return TRUE;
    else return FALSE;
}

Boolean loadStock(VmSystem * system, const char * fileName)
{
    FILE *sf;
    char *priceLast, *stockLast;
    char c[LINE_SIZE + EXTRA_SPACES];
    Stock tempStock;
    systemInit(system);
    sf = fopen(fileName, "r");
    system->stockFileName = fileName;
    if (sf != NULL)
{
   while(fgets(c, sizeof(c),sf) != NULL)
   {
/* takes each line */
       strcpy(tempStock.id,strtok(c,STOCK_DELIM));
       strcpy(tempStock.name,strtok(NULL,STOCK_DELIM));
       strcpy(tempStock.desc,strtok(NULL,STOCK_DELIM));
       tempStock.price.dollars = (unsigned)strtol
               (strtok(NULL,"."),&priceLast, 10);
       tempStock.price.cents = (unsigned)strtol
               (strtok(NULL,STOCK_DELIM),&priceLast, 10);
       tempStock.onHand = (unsigned)strtol(strtok(NULL,EMPTY_STRING),&stockLast, 10);
/* splitting up the line and storing them into a temp storage so it can be moved to the 
linked list later on */
       addToList(system,&tempStock);
   }
    fclose(sf);
/* closing the file so there are no memory leaks */
    return TRUE;
}
        return FALSE;
}

Boolean loadCoins(VmSystem * system, const char * fileName)
{
    char *endPtr;
    char c[COINTPRINTSIZE];
    Denomination denom;
    FILE *cf = fopen("coins.dat","r");
    int cash;
    system->coinFileName = fileName;
    while (fgets(c, sizeof(c),cf)!= NULL)
    {
/* getting each coin line */
        cash = (int)strtol(strtok(c, COIN_DELIM),&endPtr,BASE_TEN);
        denom = convertIntToDenom(cash);
/*splitting it up so the count and denomination are seperate */
        system->cashRegister[denom].denom = denom;
        system->cashRegister[denom].count = (unsigned)
strtol(strtok(NULL,EMPTY_STRING),&endPtr,BASE_TEN);
/*storing them straight to the cash register */
    }
    fclose(cf);
    return FALSE;
}

Boolean saveStock(VmSystem * system)
{
/* saving the stock to the file */
    FILE *sf;
    Node *node = system->itemList->head;

    sf = fopen(system->stockFileName, "w");
    while (node != NULL)
    {
        fprintf(sf,"%s%s%s%s%s%s%u%s%u%s%u\n",node->data->id
        ,STOCK_DELIM,node->data->name,STOCK_DELIM,node->data->desc,STOCK_DELIM
        ,node->data->price.dollars,".",node->data->price.cents,STOCK_DELIM
        ,node->data->onHand);
        node = node->next;
/* goes through every node and just stores it into the file */
    }

    fclose(sf);
    return FALSE;
}

Boolean saveCoins(VmSystem * system)
{
/* stores every coin denomination */
    char fileData[COINTPRINTSIZE];
    int coin;
    int i;
    FILE *cf;
    cf = fopen(system->coinFileName,"w");
    for (i = INIT_ZERO; i < NUM_DENOMS; ++i) {
        coin = convertDenominToInt(system->cashRegister[i].denom);
        sprintf(fileData, "%u,%u\n",coin,system->cashRegister[i].count);
        fwrite(fileData,1,strlen(fileData),cf);
    }
    fclose(cf);
    return FALSE;
}

void displayItems(VmSystem * system)
{
    Node *node =system->itemList->head;
    int largestName = INIT_ZERO;
    while (node != NULL)
    {
/* finds the largest name and holds the length of it */
        if (largestName < strlen(node->data->name))
            largestName = (int)strlen(node->data->name) + 1;
        node = node->next;

    }
    nameLength = NAME_LENGTH;
    printf("ID    | Name %*c Available | Price\n",largestName - nameLength,'|');
    node = system->itemList->head;
    printf("------------------------------------------------\n");
    while ( node != NULL) {
        int differenceAvaiable = MAX_ONE_DIGIT_NUMBER;
        if (node->data->onHand > MAX_ONE_DIGIT_NUMBER)
            differenceAvaiable--;
        differenceName = largestName - (int) strlen(node->data->name);
        printf("%s | %s %*c %u %*c $ %u.%02u \n", node->data->id,
               node->data->name, differenceName, '|', node->data->onHand, differenceAvaiable,
               '|', node->data->price.dollars, node->data->price.cents);
/* use the difference calculated so it can be used here, the max difference is subtracted 
by the length of the current name to see how far the stock delim sign should be */
        node = node->next;
    }
    mainMenu(system);

}

void purchaseItem(VmSystem * system)
{
    Node *node;
    char tempID[ID_LEN + EXTRA_SPACES];
    unsigned productCost;
    printf("Please enter the id of the item you wish to purchase:");
    fgets(tempID, ID_LEN+ EXTRA_SPACES, stdin);
    if(tempID[strlen(tempID )-1] == '\n') {
        node = system->itemList->head;
        if (tempID[RETURN_TO_MENU] != '\n') {
            removeNewLine(tempID);
            while (node != NULL) {
                if (strcmp(tempID, node->data->id) == INIT_ZERO)
                    break;
                node = node->next;
/* finds the location of the node they are trying to purchase */
            }
            if (node != NULL) {
                printf("You have selected “%s : %s” This will "
                               "cost you $%u.%02u \n", node->data->name,
                       node->data->desc, node->data->price.dollars,
                       node->data->price.cents);


                productCost = node->data->price.dollars * (unsigned int) DECIM_CONVERTOR
                              + node->data->price.cents;
                givingMoney(productCost, node, system);
/* converts the dollars into cents */
            }
        }
        mainMenu(system);
    }
    else
    {
        printf("Invalid input try again");
        readRestOfLine();
        purchaseItem(system);
    }
}
void givingMoney(unsigned int productCost, Node * node, VmSystem *system)
{
    double priceLeft = productCost;
    int customerPaid;
    double change;
    char customerPrice[ID_LEN + EXTRA_SPACES];
    fgets(customerPrice, sizeof(customerPrice), stdin);
    printf("\n\nPlease hand over the money – type in the value of "
                   "each note/coin in cents.\n"
                   "Press enter on a new and empty line "
                   "to cancel this purchase:\n "
                   "You still need to give us $%u.%02u: ",
           node->data->price.dollars, node->data->price.cents);
if(customerPrice[strlen(customerPrice)-1] == '\n') {
    if (customerPrice[RETURN_TO_MENU] != '\n') {
        removeNewLine(customerPrice);
        customerPaid = checkValidAmount(customerPrice); 
/* checks if the coin given is a valid denomination of money */
        while (TRUE) {
            if (customerPaid != INIT_ZERO) {
                priceLeft = priceLeft - customerPaid;
                if (priceLeft <= INIT_ZERO) {
                    change = fabs(priceLeft) / DECIM_CONVERTOR;
                    if (checkChangePossible((int)change, system)) { /* checks if there is
enough change in the vending machine */
                        printf("Here is your item %s and your change of %.2f:\n", node->data->name, change);
                        exactchange(fabs(priceLeft), system); /* gives the 
actual currency they get back */
                        --node->data->onHand;
                        break;
                    } else {
                        printf("Sorry there isn't enough change in the Vending Machine\n\n");

/* if there isn’t enough change in the register, the program exits */
                        break;
                    }
                }
                addCoin(customerPaid, system);
 /* adds the coin the customer just paid with into the cash register */
            } else
                printf("this is not a valid denomination of money. Try again\n");
            printf("you still need to give %.2f: ", priceLeft / DECIM_CONVERTOR);
            fgets(customerPrice, ID_LEN + NULL_SPACE, stdin);
            if (customerPrice[RETURN_TO_MENU] == '\n')
                break;
            if(customerPrice[strlen(customerPrice)-1] != '\n') {
                readRestOfLine();
                customerPaid = 0;
            }else {
                removeNewLine(customerPrice);
                customerPaid = checkValidAmount(customerPrice);
            }
        }
    }
}
    else
{
    printf("Invalid Input Try Again\n");
    readRestOfLine();
    givingMoney((unsigned )priceLeft,node,system); 
/* goes back to the start of this function if it an invalid amount */
}
}
int checkValidAmount(char *x){
    char *endptr; /* goes through all the valid coins and sees if the user inputted value
is the same */
    int number = (int) strtol(x, &endptr, BASE_TEN);
    if (number == FIVE_C|| number == TEN_C || number == TWENTY_C ||
            number== FIFTY_C || number == ONE_D || number == TWO_D ||
            number == FIVE_D || number == TEN_D)
        return number;
    else
        return 0;
}
void removeNewLine(char* x)
{ 
/* removes the new line, so the character array can be compared */
    int i;
    for (i = INIT_ZERO; i < strlen(x);++i)
    if (x[i] == '\n')
        x[i] = '\0';
}

void saveAndExit(VmSystem * system)
{
 /* save all the stock and coins and then go on to free the whole system */
    saveStock(system);
    saveCoins(system);
    systemFree(system);
}


void addItem(VmSystem * system) {
    Node *node = system->itemList->head;
    char largestID[ID_LEN + NULL_SPACE];
    char newID[ID_LEN + NULL_SPACE];
    char *priceLast;
    int newIDLast = INIT_ZERO;
    Stock tempStock;
    Price tempPriceStore;
    char price[COINTPRINTSIZE + EXTRA_SPACES];
    memset(largestID, '\0', ID_LEN + NULL_SPACE);
    while (node != NULL) {
        if (strcmp(largestID, node->data->id) < INIT_ZERO)
            strcpy(largestID, node->data->id);
        node = node->next;
    } /* finding the largest current id in the system */
    newIDLast = (int)strtol(largestID + 1, &priceLast, BASE_TEN);
    newIDLast++;
/*converts it into an integer and adds 1 to it */
    printf("This new meal item will have the Item id of "
                   "I%04d.\n", newIDLast);
    sprintf(newID, "I%04d", newIDLast);
   while (TRUE) {
    printf("Enter the new Item Name:");
/* gets the user input for the item name, description and the price  */
    fgets(tempStock.name, NAME_LEN + NULL_SPACE, stdin);
       if(tempStock.name[0] == '\n')
       break;
       if( tempStock.name[strlen(tempStock.name)-1] != '\n')
       {
           readRestOfLine();
           printf("Invalid input try again");
           continue;
       }
    removeNewLine(tempStock.name);

    printf("Enter the item description:");
    fgets(tempStock.desc, DESC_LEN, stdin);
       if(tempStock.desc[0] == '\n')
           break;
       if( tempStock.desc[strlen(tempStock.desc )-1] != '\n')
       {
           readRestOfLine();
           printf("Invalid input try again");
           continue;
       }
    removeNewLine(tempStock.desc);

    printf("Enter the price for this item:");
    fgets(price, sizeof(price), stdin);
       if(price[0] == '\n')
           break;
        if( price[strlen(price )-1] != '\n')
        {
            readRestOfLine();
            printf("Invalid input try again");
            continue;
        }
           tempPriceStore.dollars = (unsigned int)
                   strtol(strtok(price, "."), &priceLast, BASE_TEN);
           tempPriceStore.cents = (unsigned int)
                   strtol(strtok(NULL, ""), &priceLast, BASE_TEN);
       errorCheckPrice(&tempPriceStore); /* checks if the price entered has any error,
such as it isn’t a divisor of 5 and then goes onto fix it */
       tempStock.price.dollars = tempPriceStore.dollars;
       tempStock.price.cents = tempPriceStore.cents;

           printf("This item “%s – %s” has now been added to "
                          "the menu.\n", tempStock.name, tempStock.desc);
           strcpy(tempStock.id, newID);
           addToList(system, &tempStock);
       break;
    }
    mainMenu(system);
}
void errorCheckPrice(Price *tempPrice)
{
/* rounds the value so t can be a remainder of 5 */
    while (tempPrice->cents % FIVE_C != DIVIDE_BY_FIVE && tempPrice->cents != MAX_ONE_DIGIT_NUMBER)
    {
        tempPrice->cents ++;
    }
    if(tempPrice->cents == MAX_TWO_DIGIT_NUMBER)
    {
        tempPrice->cents =DIVIDE_BY_FIVE;
        tempPrice->dollars++;
    }


}
void removeItem(VmSystem * system)
{
/* asks for the id of the node that needs to be removed */
    char deleteID[ID_LEN + EXTRA_SPACES];

    printf("Enter the item id of the item to remove from the menu:");
    fgets(deleteID,ID_LEN + EXTRA_SPACES,stdin);
    if(deleteID[strlen(deleteID)-1] =='\n') {
        if (deleteID[0] != '\n') {
            removeNewLine(deleteID);
            removeNode(system, deleteID);
        }
	printf("The item has been succefully deleted");
        mainMenu(system);
    }
    else
    {
        printf("Invalid input try again");
        readRestOfLine();
        removeItem(system);
    }
}

void displayCoins(VmSystem * system)
{
/* displays all the coins in the file */
    int difference;
    int i;
    char coin_print[COINTPRINTSIZE + EXTRA_SPACES];
    printf("Coin Summary\n");
    printf("-------------\n");
    printf("Denomination | Count\n\n");
    for ( i =INIT_ZERO; i < NUM_DENOMS;++i)
    {
        /*stores the string of the Denomination so it can be called later on  */
 convertDenomtoStr(i,coin_print);
        difference = (int)DENOMTEXTSIZE - strlen(coin_print);
        printf("%s%*s",coin_print,difference,"|");
        printf(" %u\n",system->cashRegister[i].count);
    }
    printf("\n\n\n");
    mainMenu(system);

}

void resetStock(VmSystem * system)
{
/* goes through every node and changes the value of the on hand */
  Node *node = system->itemList->head;
    while ( node != NULL)
    {
        node->data->onHand = DEFAULT_STOCK_LEVEL;
        node = node->next;
    }
    mainMenu(system);
}

void resetCoins(VmSystem * system)
{
/* goes through every coin in the register and changes the value to the default value*/
    int i;
    printf("Resetting all stocks to %d\n",DEFAULT_COIN_COUNT);
    for (i = INIT_ZERO; i < NUM_DENOMS;++i)
    {
        system->cashRegister[i].count = DEFAULT_COIN_COUNT;
    }
    mainMenu(system);
}


void abortProgram(VmSystem * system)
{
/* free the system and end the program*/
    systemFree(system);
}
