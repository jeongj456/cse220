#include <stdlib.h>
#include <stdbool.h>
#include "priority_queue.h"

/*
 * Create a new PriorityQueue structure and return it.
 *
 * The newly-created structure should have a NULL head, and every tail
 * pointer in its tails table should be NULL.
 *
 * nprios: The maximum number of priorities to support
 */
PriorityQueue *pqueue_init(int nprios) {
    if(nprios<0){
        return NULL;
    }
    PQNode *tails[nprios];
    struct PriorityQueue *pq = malloc(sizeof(struct PriorityQueue));
    pq->head = NULL;
    pq->tails = tails;
    pq->nprios = nprios;
    return pq;
}

/*
 * Free all structures associated with this priority queue, including their
 * queue structure itself.  Any access to pqueue after this function returns
 * should be considered invalid.
 *
 * pqueue: the queue to free
 */
void pqueue_free(PriorityQueue *pqueue) {
    PQNode *node = pqueue->head;
    while (node->next!=NULL){
        free(node);
        node=node->next;
    }
    free(node);
    free(pqueue);
}

/*
 * Insert a new node into a queue by priority and value.
 *
 * pqueue: the queue into which the new node should be inserted
 * value: the opaque value being inserted into the queue
 * priority: the priority at which this value is to be inserted
 */
void pqueue_insert(PriorityQueue *pqueue, int value, int priority) {
    PQNode *node = malloc(sizeof(struct PQNode));
    node->value = value;
    node->priority = priority;
    if (pqueue->head==NULL){
        pqueue->head = node;
    }else{
        PQNode *nextnode = pqueue->tails[priority]->next;
        node->prev = pqueue->tails[priority];
        node->next = nextnode;
        pqueue->tails[priority] = node; //***Do I need to delete previous
    }
}

/*
 * Return the head queue node without removing it.
 */
PQNode *pqueue_peek(PriorityQueue *pqueue) {
    return pqueue->head; 
}

/*
 * Remove and return the head queue node.
 */
PQNode *pqueue_get(PriorityQueue *pqueue) {
    PQNode *newhead = pqueue->head->next;
    PQNode *retval = pqueue->head;
    pqueue->head->next = NULL;
    pqueue->head = newhead;
    return retval;
}
