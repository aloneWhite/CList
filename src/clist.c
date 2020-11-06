#include "clist.h"
#include <stdlib.h>

#define calloc calloc
#define free   free

static int clist_is_empty(clist_t* l)
{
    if(!l || !l->head || !l->tail) {
        return 1;
    } else {
        return 0;
    }
}

clist_t* clist_new(val_free_t val_free)
{
    clist_t* l = NULL;

    l = calloc(1, sizeof(clist_t));
    if(l && val_free) {
        l->val_free = val_free;
    }

    return l;
}

void clist_free(clist_t* l)
{
    clist_node_t* p = NULL, *q = NULL;

    if(!l) {
        return;
    }

    p = l->head;
    while(p) {
        q = p->next;
        if(l->val_free) {
            l->val_free(p->val);
        }

        free(p);
        p = q;
    }

    free(l);
    return;
}

int clist_lpush(clist_t* l, void* val)
{
    clist_node_t* node = NULL;

    if(!l || !val) {
        return CLIST_E_INVALID_PARAM;
    }

    node = calloc(1, sizeof(clist_node_t));
    if(!node) {
        return CLIST_E_OUT_OF_MEMORY;
    }

    node->val = val;
    node->next = l->head;
    if(l->head) {
        l->head->prev = node;
    }

    l->head = node;
    if(!l->tail) {
        l->tail = node;
    }

    l->count++;
    return CLIST_OK;
}

int clist_rpush(clist_t* l, void* val)
{
    clist_node_t* node = NULL;

    if(!l || !val) {
        return CLIST_E_INVALID_PARAM;
    }

    node = calloc(1, sizeof(clist_node_t));
    if(!node) {
        return CLIST_E_OUT_OF_MEMORY;
    }

    node->val = val;
    node->prev = l->tail;
    if(l->tail) {
        l->tail->next = node;
    }

    l->tail = node;
    if(!l->head) {
        l->head = node;
    }

    l->count++;
    return CLIST_OK;
}

#define CLIST_HEAD 1
#define CLIST_TAIL 2
static void* clist_pop(clist_t* l, int flag)
{
    clist_node_t* node = NULL;
    void* val = NULL;

    if(clist_is_empty(l)) {
        return NULL;
    }

    if(flag == CLIST_HEAD) {
        node = l->head;
    } else if(flag == CLIST_TAIL) {
        node = l->tail;
    }
    
    if(!node) {
        return NULL;
    }

    if(node->next) {
        node->next->prev = node->prev;
    } else {
        l->tail = node->prev;
    }

    if(node->prev) {
        node->prev->next = node->next;
    } else {
        l->head = node->next;
    }

    val = node->val;
    l->count--;
    free(node);

    return val;
}

void* clist_lpop(clist_t* l)
{
    return clist_pop(l, CLIST_HEAD);
}

void* clist_rpop(clist_t* l)
{
    return clist_pop(l, CLIST_TAIL);
}

int clist_count(clist_t* l)
{
    if(clist_is_empty(l)) {
        return 0;
    }

    return l->count;
}

void* clist_find(clist_t* l, int index)
{
    int i = 0;
    void* val = NULL;
    clist_node_t* pnode = NULL;

    if(clist_is_empty(l) || index < 0) {
        return 0;
    }

    if(clist_is_empty(l)) {
        return NULL;
    }

    pnode = l->head;
    while(pnode) {
        if(i == index) {
            break;
        }
        pnode = pnode->next;
        i++;
    }

    return pnode->val;
}