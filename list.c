#include "list.h"
#include <stdio.h>
#include <stdlib.h>


//Definerer strukturen for en node
typedef struct node    //Slipper å kalle på struct hvergang og gir kallenavn til node
{
    void *data;       //Pointer til dataen(Void gir at den kan være hvilken som helst type)
    struct node *next; //Pointer til den neste noden i listen
}node_t;               //Nye navnet på struct noden


//Definerer strukturen for listen
typedef struct list
{
    node_t *head   //Pointer til første noden i listen
}list_t;           //Nye navnet på struct listen


list_t *list_create(void)
{
    list_t *list = (list_t*)malloc(sizeof(list_t)); //Allokere minne for lista
    if(list == NULL)    //Dersom den returner ingenting, har minne feilet
    {
        return NULL;
    }
    list->head = NULL;   //Starter tomt, så head pointer til NULL
    return list;
}

void list_addfirst(list_t *list, void *item)
{
    node_t *new_node =(node_t*)malloc(sizeof(node_t));
    if(new_node == NULL)
    {
        return NULL;
    }
    new_node -> data = item;
    new_node ->next = list -> head;
    list -> head = new_node;
}

void list_destroy(list_t *list)
{
    node_t *current = list->head;
    node_t *next_node;
    while (current != NULL)
    {
        next_node = current -> next;
        free(current);
        current = next_node;
    }
    free(list);
}


void list_addlast(list_t *list, void *item)
{
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if(new_node == NULL)
    {
        return NULL;
    new_node -> data = item;
    new_node -> next = NULL;

    if (list -> head == NULL)
    {
        list -> head = new_node;
    } else {
        node_t *current = list->head;
        while(current ->next != NULL)
        {
            current = current -> next;
         }
        current -> next = new_node;
        }
    
    }
}

void list_remove(list_t *list, void *item)
{
    if(list == NULL || list -> head == NULL){  //list == NULL sjekker om selve listen er NULL, mens list -> NULL sjekker om listen er tom
        return;
    }

    node_t *current = list ->head;
    node_t *previous = NULL;


}











// implement the functions from list.h here
