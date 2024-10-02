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

//funksjon for å lage en ny liste
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
        return;
    }

    new_node -> data = item;                     //Setter dataen i den nye noden til item
    new_node ->next = list -> head;             //Kobler den til gamle head, slik at den blir den første noden
    list -> head = new_node;                   //Oppdaterer listen slik at den nye noden blir den første
}

void list_destroy(list_t *list)
{
    node_t *current = list->head;         //Starter med å pointe til første node
    node_t *next_node;                   //Lager en pointer for neste node
    while (current != NULL)             //Går gjennom hver node i listen
    {
        next_node = current -> next;          //Lagrer pointeren til neste node
        free(current);                        //Blir kvitt minnet til noden som pointes på
        current = next_node;                 //Går fra noden som pointes på til neste node
    } 
    free(list);                             //Blir kvitt minnet til listen
}


void list_addlast(list_t *list, void *item)
{
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if(new_node == NULL || list -> head == NULL) 
    {
        return;
    }

    new_node -> data = item;
    new_node -> next = NULL;         //Siden det er siste noden, så settes neste til NULL(Ingenting etter)

    if (list -> head == NULL)       //Om listen er tom
    {
        list -> head = new_node;   //Så settes neste node til den nye og første noden
    } else {
        node_t *current = list->head;    //Om listen ikke er tom, så startes det på første noden
        
        while(current ->next != NULL)     //Finne siste noden i lista
        {
            current = current -> next;  //Fortsetter til neste node
         }
        current -> next = new_node;  //Kobler den siste noden til den nye
        }
    
    
}

void list_remove(list_t *list, void *item)
{
    if(list == NULL || list -> head == NULL){  //list == NULL sjekker om selve listen er NULL, mens list -> NULL sjekker om listen er tom
        return;
    }

    node_t *current = list ->head;          //Start med første node
    node_t *previous = NULL;                //Pointer til forrige node

    while (current != NULL)                //Går gjennom listen
    {
        if (current -> data == item)       //Finner noden med riktig data
        {
            if (previous == NULL) {          //Om noden er den første, om det er den første = NULL
                list->head = current->next;  //Oppdatere head til neste node, 1->2->3 blir 2->3
                
            } else {
                previous->next = current->next;   //Om noden ikke er den første, så kobler den forrige til neste
            
            }
            free(current);                     //Frigjør minnet til noden som ble fjernet
            return;                            //Avslutter 
        }
        previous = current;                   //Oppdatere slik at 2->3 blir 1->2
        current = current->next;              //Flytt current til neste node 
    }
    
}

int list_size(list_t *list)
{
    if (list == NULL || list -> head == NULL)
    {
        return 0;
    }
    int teller = 0;
    node_t *current = list -> head;

    while (current != NULL)
    {
        teller++;
        current = current -> next;
    }
    
    return teller;
}

typedef struct list_iterator{
    list_t* list;
    struct node* current;
} list_iterator_t;

list_iterator_t *list_createiterator(list_t *list)
{
    if (list == NULL || list ->head == NULL)
    {
        return NULL;
    }

    list_iterator_t *iter = (list_iterator_t*)malloc(sizeof(list_iterator_t));
    if (iter == NULL)
    {
        return NULL;
    }
    iter -> list = list;
    iter -> current = list -> head;
    return iter;


}

void list_destroyiterator(list_iterator_t *iter)
{
    if(iter != NULL)
    {
        free(iter);
    }
}

void *list_next(list_iterator_t *iter)
{
    if (iter == NULL || iter -> current == NULL)
    {
        return NULL;
    }
    void *data = iter -> current -> data;

    iter -> current = iter -> current -> next;

    return data;
}

void list_resetiterator(list_iterator_t *iter)
{
    if (iter != NULL && iter -> list != NULL)
    {
        iter -> current = iter -> list -> head;
    }

    
}



// implement the functions from list.h here
