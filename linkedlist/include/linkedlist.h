#include <stddef.h>

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

static struct ListNode {
    void *data;
    struct ListNode *next;
} ListNode;

static struct LinkedList {
    size_t length, data_size;
    struct ListNode *head;
    void (*append)   (struct LinkedList *, void *),
         (*prepend)  (struct LinkedList *, void *),
         (*insert)   (struct LinkedList *, size_t, void *);
} LinkedList;


static struct ListNode *makeListNode(size_t data_size, void *data);

struct LinkedList *newLinkedList(size_t data_size);
// Linked List operations
void append(struct LinkedList *self, void *data);
void prepend(struct LinkedList *self, void *data);
void insert(struct LinkedList *self, size_t index, void *data);

#endif