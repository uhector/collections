#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>


typedef struct _Node _Node;

typedef struct _LinkedList {
    /* Properties */
    size_t length, data_size;
    _Node *head;
    /* Methods */
    void  *(*index)        (struct _LinkedList *, size_t index);
    
    size_t (*append)       (struct _LinkedList *, void *),
           (*prepend)      (struct _LinkedList *, void *),
           (*insert)       (struct _LinkedList *, size_t, void *),
           (*delete_begin) (struct _LinkedList *),
           (*delete_end)   (struct _LinkedList *);
    
    void   (*destroy)      (struct _LinkedList *);
} LinkedList;

extern LinkedList *new_LinkedList(size_t data_size);


#endif
