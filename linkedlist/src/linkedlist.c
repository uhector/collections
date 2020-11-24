#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../include/linkedlist.h"

void ListNode_destroy(ListNode *node)
{
    node->next = NULL;
    node->destroy = NULL;
    free(node->data);
    free(node);
}

ListNode *newListNode(size_t data_size, void *data)
{
    ListNode *node;
    node = malloc(sizeof(ListNode));
    node->data = malloc(data_size);
    node->next = NULL;
    // operations
    node->destroy = &ListNode_destroy;

    memcpy(node->data, data, sizeof(data));
    
    return node;
}

void LinkedList_append(LinkedList *self, void *data)
{
    ListNode *node;
    node = newListNode(self->data_size, data);
    
    if (self->head == NULL) {
        self->head = node;
    } else {
        ListNode *last_node;
        last_node = self->head;

        while (last_node->next != NULL) {
            last_node = last_node->next;
        }

        last_node->next = node;
    }

    self->length++;
}

void LinkedList_prepend(LinkedList *self, void *data)
{
    ListNode *node;
    node = newListNode(self->data_size, data);
    
    if (self->head == NULL) {
        self->head = node;
    } else {
        ListNode *list_head;
        list_head = self->head;

        self->head = node;
        node->next = list_head;
    }

    self->length++;
}

void LinkedList_insert(LinkedList *self, size_t index, void *data)
{
    if (index == 0) {
        self->prepend(self, data);
    } else if (index == self->length) {
        self->append(self, data);
    } else if (index > self->length) {
        // handle this pls :c
    } else {
        ListNode *node, *previous_node, *next_node;
        node = newListNode(self->data_size, data);
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

    self->length++;
}

void LinkedList_delend(LinkedList *self)
{
    if (self->head == NULL) {
        // handle this pls :c
    } else {
        if (self->length == 1) {
            ListNode *list_head;
            list_head = self->head;
            list_head->destroy(list_head);

            self->head = NULL;
        } else {
            ListNode *previous_node, *last_node;
            previous_node = self->head;
            last_node = previous_node->next;

            while (last_node->next != NULL) {
                previous_node = last_node;
                last_node = last_node->next;
            }

            last_node->destroy(last_node);
            previous_node->next = NULL;
        }

        self->length--;
    }
}

void LinkedList_delbegin(LinkedList *self)
{
    if (self->head == NULL) {
        // handle this pls :c
    } else {
        ListNode *head_node;
        head_node = self->head;

        if (head_node->next == NULL) {
            head_node->destroy(head_node);
            self->head = NULL;
        } else {
            self->head = head_node->next;
            head_node->destroy(head_node);
        }

        self->length--;
    }
}

void LinkedList_destroy(LinkedList *self)
{
    while (self->length != 0) {
        self->delend(self);
    }

    // properties
    self->length     = 0;
    self->data_size  = 0;
    self->head       = NULL;
    // operations
    self->append     = NULL;
    self->prepend    = NULL;
    self->insert     = NULL;
    self->delend     = NULL;
    self->delbegin   = NULL;
    self->destroy    = NULL;

    free(self);
}

LinkedList *newLinkedList(size_t data_size)
{
    LinkedList *list;
    list = malloc(sizeof(LinkedList));
    // properties
    list->length     = 0;
    list->data_size  = data_size;
    list->head       = NULL;
    // operations
    list->append     = &LinkedList_append;
    list->prepend    = &LinkedList_prepend;
    list->insert     = &LinkedList_insert;
    list->delend     = &LinkedList_delend;
    list->delbegin   = &LinkedList_delbegin;
    list->destroy    = &LinkedList_destroy;

    return list;
}