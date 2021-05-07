#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"


/*  Node  */
typedef struct _Node {
    void *data;
    struct _Node *next;
    void (*destroy)(struct _Node *);
} _Node;


/*  Node methods  */
static void _Node_destroy(_Node *node)
{
    node->next = NULL;
    node->destroy = NULL;

    if (node->data != NULL)
    {
        free(node->data);
    }
   
    free(node);
}

static _Node *_new_Node(size_t data_size, void *data)
{
    _Node *node;

    if ((node = malloc(sizeof(_Node))) == NULL)
    {
        return NULL;
    }
    
    /* Methods */
    node->destroy = &_Node_destroy;
    
    /* Properties */
    if ((node->data = malloc(data_size)) == NULL)
    {
        node->destroy(node);
        return NULL;
    }

    node->next = NULL;
    memcpy(node->data, data, sizeof(data));
    
    return node;
}


/*  LinkedList methods  */
static void *_LinkedList_index(LinkedList *self, size_t index)
{
    _Node *node;

    if ((node = self->head) == NULL || index >= self->length)
    {
        return NULL;
    }

    for (size_t i = 1; i <= index; i++)
    {
        node = node->next;
    }

    return node->data;
}

static size_t _LinkedList_prepend(LinkedList *self, void *data)
{
    _Node *node;

    if ((node = _new_Node(self->data_size, data)) == NULL)
    {
        /* Error */
        return 0;
    }
    
    if (self->head == NULL)
    {
        self->head = node;
    }
    else
    {
        _Node *old_head = self->head;

        self->head       = node;
        self->head->next = old_head;
    }

    return self->length++;
}

static size_t _LinkedList_append(LinkedList *self, void *data)
{
    _Node *node;

    if ((node = _new_Node(self->data_size, data)) == NULL)
    {
        /* Error */
        return 0;
    }
    
    if (self->head == NULL)
    {
        self->head = node;
    }
    else
    {
        _Node *last_node = self->head;

        while (last_node->next != NULL) {
            last_node = last_node->next;
        }

        last_node->next = node;
    }

    return self->length++;
}

static size_t _LinkedList_insert(LinkedList *self, size_t index, void *data)
{
    if (index == 0)
    {
        return _LinkedList_prepend(self, data);
    }
    else if (index >= self->length)
    {
        return _LinkedList_append(self, data);
    }

    _Node *node, *previous_node, *next_node;

    if ((node = _new_Node(self->data_size, data)) == NULL)
    {
        /* Error */
        return 0;
    }

    previous_node = self->head;

    for (size_t i = 1; i < index; i++)
    {
        previous_node = previous_node->next;
    }

    next_node           = previous_node->next;
    previous_node->next = node;
    node->next          = next_node;

    return self->length++;
}

static size_t _LinkedList_delete_begin(LinkedList *self)
{
    if (self->length == 0)
    {
        return 0;
    }

    _Node *head_node = self->head;

    if (head_node->next == NULL)
    {
            head_node->destroy(head_node);
            self->head = NULL;
    }
    else
    {
        self->head = head_node->next;
        head_node->destroy(head_node);
    }

    return self->length--;
}

static size_t _LinkedList_delete_end(LinkedList *self)
{
    if (self->length == 0) {
        return self->length;
    }
    else if (self->length == 1)
    {
        _Node *node = self->head;
        node->destroy(node);
        
        self->head = NULL;
    }
    else
    {
        _Node *previous_node, *last_node;

        previous_node = self->head;
        last_node     = previous_node->next;

        while (last_node->next != NULL)
        {
            previous_node = last_node;
            last_node = previous_node->next;
        }

        last_node->destroy(last_node);

        previous_node->next = NULL;
    }

    return self->length--;
}

static void _LinkedList_destroy(LinkedList *self)
{
    while (self->length != 0)
    {
        self->delete_end(self);
    }

    /* Properties */
    self->length       = 0;
    self->data_size    = 0;
    self->head         = NULL;
    /* Methods */
    self->index        = NULL;
    self->append       = NULL;
    self->prepend      = NULL;
    self->insert       = NULL;
    self->delete_end   = NULL;
    self->delete_begin = NULL;
    self->destroy      = NULL;

    free(self);
}

static LinkedList *_LinkedList_init(size_t data_size)
{
    LinkedList *list;
    
    if ((list = malloc(sizeof(LinkedList))) == NULL)
    {
        return NULL;
    }

    /* Properties */
    list->length       = 0;
    list->data_size    = data_size;
    list->head         = NULL;
    /* Methods */
    list->index        = &_LinkedList_index;
    list->prepend      = &_LinkedList_prepend;
    list->append       = &_LinkedList_append;
    list->insert       = &_LinkedList_insert;
    list->delete_end   = &_LinkedList_delete_end;
    list->delete_begin = &_LinkedList_delete_begin;
    list->destroy      = &_LinkedList_destroy;

    return list;
}

LinkedList *new_LinkedList(size_t data_size)
{
    return _LinkedList_init(data_size);
}
