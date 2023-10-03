#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "priority_queue.h"
#include <ctype.h>


/*
 * Validate the given PriorityQueue for structural correctness.
 *
 * In order for this function to return true, the queue passed in must
 * meet the specification in the project handout precisely.  Every node
 * in the linked list and every pointer in the tails table must be
 * correct.
 *
 * pqueue: queue to validate
 *
 * Returns true if the queue is valid, false otherwise.
 */

bool pqueue_validate(PriorityQueue *pqueue) {
    if(pqueue == NULL){
        puts("Empty queue");
        return true;
    }
    int npriority = pqueue->nprios;
    if (pqueue->tails[npriority]){
        return false;
    }

    //An empty priority queue has head==NULL and every entry in tails is NULL.
    if (pqueue->head == NULL){
        for(int i=0; i<npriority; i++){
            if (pqueue->tails[i] != NULL){
                puts("Head is null but tails are not");
                return false;
            }
        }
    }

    if(pqueue->head->prev != NULL){
        puts("Head->prev is not NULL");
        return false;
    }

    PQNode *node = pqueue->head->next;
    while (node->next != NULL){
        if(!isdigit(node->value)){
            return false;
        }
        PQNode *tn = node;
        if(node->prev == NULL){
            puts("Non head node has NULL previous pointer");
            return false;
        }
        if(node->prev->next != tn){
            puts("node->prev->next does not equal node");
            return false;
        }
        if(node->next->prev != tn){
            puts("node->next->prev does not equal node");
            return false;
        }
        node = node->next; 
    }

    PQNode *tnode = pqueue->head;
    int pri = tnode->priority;
    //The priorities of the nodes in the list are sorted in non-decreasing order
    while (tnode->next != NULL){
        if(tnode->priority <= pri){
            pri = tnode->priority;
            tnode = tnode->next; 
        }else{
            puts("Not in non-decreasing order");
            return false;
        }
    }

    for (int i = 0; i < npriority; i++) {
        if(pqueue->tails[i] == NULL && pqueue->tails[i-1]->next->priority == i){
            printf("No priority %i but there is a node in the list with the priority\n", i);
        }
    }
    return true;
}
