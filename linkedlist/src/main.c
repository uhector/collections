#include <stdio.h>

#include "../include/linkedlist.h"

int main(void)
{
    struct LinkedList *list;
    list = newLinkedList(sizeof(int));
    
    for (int i = 1; i <= 10; i++) {
        list->prepend(list, &i);
        printf("%d\n", *(int *)list->head->data);
    }
}