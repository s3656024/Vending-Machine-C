/******************************************************************************

** Student Name: <Jeffin Poovely>

** Student Number: <s3656024>

** Date of submission: <Fri, 13 Oct 2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/
#include "vm_stock.h"

/**
 * vm_stock.c this is the file where you will implement the
 * interface functions for managing the stock list.
 **/

/**
 * Some example functions:
 * create list, free list, create node, free node, insert node, etc...
 */

void addToList(VmSystem *system, Stock * stock)
{
    Node *newNode = malloc(sizeof(*newNode));
    newNode->data = malloc(sizeof(*newNode->data));
    memcpy(newNode->data, stock, sizeof(*stock));
    newNode->next = NULL;
    if(system->itemList->head == NULL) {
/*moving it to the head */
        system->itemList->head = newNode;
        system->itemList->size ++;
    }
    else findLocation(system->itemList, newNode);

}
void findLocation(List *list, Node *newNode)
{
    Node *previousNode = NULL;
    Node *currentNode = list->head;
    while (strcmp(currentNode->data->name, newNode->data->name) < 0)
    {
/* finding the correct location to add the node */
        if (currentNode->next == NULL)
            break;
        else
        {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
    }
     if (previousNode == NULL) /* it needs to be added to the head */
    {
/* making it the head*/
        newNode->next = list->head;
        list->head = newNode;
    }
    else if (currentNode == NULL)/*adding it to the end */ {
/*adding the node to the end of the list */
        currentNode->next =newNode;
    }
    else /* adding it to the center of the list*/{
/* adding it to the centre of the list*/
        previousNode->next = newNode;
        newNode->next = currentNode;
    }

    list->size++;
}


Boolean removeNode(VmSystem *system,char *deleteID)
{
    Node *currentNode = system->itemList->head;
    Node *previousNode = NULL;
    while (currentNode != NULL)
    {
/* finds the location of the node being removed */
        if (strcmp(currentNode->data->id, deleteID) == 0)
            break;
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (previousNode == NULL)
    {
/* removing the head */
        system->itemList->head  = currentNode->next;
        free(currentNode->data);
        free(currentNode);
        return TRUE;
    }
    else if (currentNode != NULL)
    {

        previousNode->next = currentNode->next;
        free(currentNode->data);
        free(currentNode);
        return TRUE;
    }
/*removing the end of the linked list */
else if (currentNode == NULL)
{
free(previousNode->data);
free(previousNode);
}
    return FALSE;

}
