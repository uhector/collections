#include <stddef.h>

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct ListNode {
    void *data;
    struct ListNode *next;
    void (*destroy) (struct ListNode *);
} ListNode;

typedef struct LinkedList {
    size_t length, data_size;
    ListNode *head;
    void (*append)    (struct LinkedList *, void *),
         (*prepend)   (struct LinkedList *, void *),
         (*insert)    (struct LinkedList *, size_t, void *),
         (*delend)    (struct LinkedList *),
         (*delbegin)  (struct LinkedList *),
         (*destroy)   (struct LinkedList *);
} LinkedList;


ListNode *makeListNode(size_t data_size, void *data);
// ListNode operations
void ListNode_destroy(ListNode *self);

LinkedList *newLinkedList(size_t data_size);
// LinkedList operations
void LinkedList_append(LinkedList *self, void *data);
void LinkedList_prepend(LinkedList *self, void *data);
void LinkedList_insert(LinkedList *self, size_t index, void *data);
void LinkedList_delend(LinkedList *self);
void LinkedList_delbegin(LinkedList *self);
void LinkedList_destroy(LinkedList *self);

#endif