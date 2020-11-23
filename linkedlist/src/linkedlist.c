#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../include/linkedlist.h"

static struct ListNode *makeListNode(size_t data_size, void *data)
{
    struct ListNode *node;
    node = malloc(sizeof(ListNode));
    node->data = malloc(sizeof(data_size));
    node->next = NULL;

    memcpy(node->data, data, sizeof(data));
    
    return node;
}

void append(struct LinkedList *self, void *data)
{
    struct ListNode *node;
    node = makeListNode(self->data_size, data);
    
    if (self->head == NULL) {
        self->head = node;
    } else {
        struct ListNode *last_node;
        last_node = self->head;

        while (last_node->next != NULL) {
            last_node = last_node->next;
        }

        last_node->next = node;
    }
}

void prepend(struct LinkedList *self, void *data)
{
    struct ListNode *node;
    node = makeListNode(self->data_size, data);
    
    if (self->head == NULL) {
        self->head = node;
    } else {
        struct ListNode *list_head;
        list_head = self->head;

        self->head = node;
        node->next = list_head;
    }
}

void insert(struct LinkedList *self, size_t index, void *data)
{
    if (index == 0 && self->head != NULL) {
        self->prepend(self, data);
    } else if (index == self->length) {
        self->append(self, data);
    } else if (index > self->length) {
        // handle this pls :c
    } else {
        struct ListNode *node, *previous_node, *next_node;
        node = makeListNode(self->data_size, data);
        previous_node = self->head;

        size_t count = 0;
        while (count < index) {
            previous_node = previous_node->next;
            count ++;
        }

        next_node = previous_node->next;

        previous_node->next = node;
        node->next = next_node;
    }
}

struct LinkedList *newLinkedList(size_t data_size)
{
    struct LinkedList *list;
    list = malloc(sizeof(struct LinkedList));
    list->head = NULL;
    list->append = &append;
    list->prepend = &prepend;
    list->insert = &insert;

    return list;
}