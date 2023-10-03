#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../src/priority_queue.h"

#define NPRIOS 5

int main(int argc, char *argv[]){
    PriorityQueue *pqueue = pqueue_init(NPRIOS);
    PQNode *node;

    if (pqueue == NULL) {
        puts("failed");
        return 1;
    }

    
    pqueue_insert(pqueue, 1, 0);
    pqueue_insert(pqueue, 2, 0);
    pqueue_insert(pqueue, 3, 1);
    pqueue_insert(pqueue, 4, 3);
    pqueue_insert(pqueue, 5, 3);
    pqueue_insert(pqueue, 6, 3);
    pqueue_insert(pqueue, 7, 0);
    pqueue_insert(pqueue, 8, 4);
    pqueue_insert(pqueue, 9, 5);
    pqueue_insert(pqueue, 10, 5);

    //Tests identify correct API functions

    //Tests for pqueue_insert()
    if(pqueue->tails[0]->value != 7){
        puts("Insertion function error");
        return 1;
    }
    if(pqueue->tails[3]->value != 6){
        puts("Insertion function error");
        return 1;
    }
    if(pqueue->tails[1]->value != 3){
        puts("Insertion function error");
        return 1;
    }

    //Tests pqueue_peek()
    PQNode *head_node = pqueue_peek(pqueue); 
    if (head_node->value != 1 && head_node->priority != 0){
        puts("Peek function does not return head node");
        return 1;
    }

    if (head_node->prev != NULL){
        puts("Head node previous does not equal NULL");
        return 1;
    }

    //Tests for pqueue_get()
    PQNode *oldhead = pqueue_get(pqueue);
    if(oldhead->value != 1 && oldhead->prev != 0){
        puts("Error with get function");
        return 1;
    }
    if(pqueue->head->value != 2 && pqueue->head->prev != 0){
        puts("Error with get function");
        return 1;
    }

    //Tests for pqueue_validate()
    if (pqueue_validate(pqueue) != true){
        puts("Error with validate function");
        return 1;
    }

    return 0;
}