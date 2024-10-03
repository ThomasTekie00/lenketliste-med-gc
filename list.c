#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/*Inspirasjon fra https://www.geeksforgeeks.org/singly-linked-list-tutorial/#node-definition */
//Definerer strukturen for en node
typedef struct node    //Slipper å kalle på struct hvergang og gir kallenavn til node
{
    void *data;       //Pointer til dataen(Void gir at den kan være hvilken som helst type)
    struct node *next; //Pointer til den neste noden i listen
}node_t;               //Nye navnet på struct noden




//Definerer strukturen for listen
typedef struct list
{
    node_t *head;   //Pointer til første noden i listen
    node_t *tail;  //Pointer til siste noden i listen

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
    list->tail = NULL;   //starter tomt, så tail peker til NULL

  
  
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
        list -> tail = new_node;   //Siden det er første og siste noden, så settes tail til den nye noden
     
     } else {
        list->tail->next = new_node;  // Oppdater tail til å peke på den nye noden
        list->tail = new_node;        // Oppdater tail til å være den nye noden
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
    if (list == NULL || list -> head == NULL) //Sjekker om listen er NULL eller tom
    {
        return 0;
    }
    int teller = 0;                          //Teller for å finne antall noder
    node_t *current = list -> head;          //Starter med første node

    while (current != NULL)                  //Går gjennom listen av noder
    {
        teller++;                            //Øker teller fpor hver node
        current = current -> next;           //Fortsetter til neste node
    }
    
    return teller;                           //Returnere antall noder
} 


/*Pointer til lsiten som iterer over */
typedef struct list_iterator{
    list_t* list;                       //Pointer til listen som itereres over
    struct node* current;               //Pointer til noden som pointes på i listen som itereren pointer på
} list_iterator_t;











list_iterator_t *list_createiterator(list_t *list)     //Lager iterator
{
    if (list == NULL || list ->head == NULL)           //Sjekker om listen er tom elelr NULL
    {
        return NULL;
    }

    list_iterator_t *iter = (list_iterator_t*)malloc(sizeof(list_iterator_t));
    if (iter == NULL)
    {
        return NULL;
    }
    iter -> list = list;              //Kobler iteratoren til listen
    iter -> current = list -> head;   //Starter med første node i listen
    return iter;                      //Returnere iteratoren


}







void list_destroyiterator(list_iterator_t *iter)
{
    if(iter != NULL)         //Sjekker om iteratoren ikke er NULL
    {
        free(iter);          //Slipper minnet til iteratoren
    } 
}




void *list_next(list_iterator_t *iter)
{
    if (iter == NULL || iter -> current == NULL)
    {
        return NULL;                   //Returnere NULL hvis det er siste node eller om iteratoren er NULL
    }
    /*Void så datatypen kan være hva som helst*/
    void *data = iter -> current -> data;      //Henter dataen fra noden som pointes på

    iter -> current = iter -> current -> next;  //Går videre til neste node

    return data;
}




void list_resetiterator(list_iterator_t *iter)
{
    if (iter != NULL && iter -> list != NULL)     //Sjekker om iteratoren og listen ikke er NULL, begge må være gyldige for å resette
    {
        iter -> current = iter -> list -> head;  //Går tilbake til første node ved å sette noden som pointes på til første node
    }

    
}



