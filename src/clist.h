#ifndef __CLIST_H__
#define __CLIST_H__

// a callback function to free the "val" in node.
typedef void (*val_free_t)(void* val);

typedef struct clist_node_st clist_node_t;
typedef struct clist_st clist_t;

struct clist_node_st {
    void* val;
    clist_node_t* prev;
    clist_node_t* next;
};

struct clist_st {
    clist_node_t* head;
    clist_node_t* tail;
    
    val_free_t val_free;
    int count;
};

clist_t* clist_new(val_free_t val_free);
void clist_free(clist_t* l);

int clist_lpush(clist_t* l, void* val);
int clist_rpush(clist_t* l, void* val);
void* clist_lpop(clist_t* l);
void* clist_rpop(clist_t* l);
int clist_count(clist_t* l);
void* clist_find(clist_t* l, int index);

#define CLIST_OK					0
#define CLIST_E_INVALID_PARAM		-1
#define CLIST_E_OUT_OF_MEMORY		-2
#define CLIST_E_OUT_OF_INDEX		-3

#endif