#include <stdio.h>

#include "../include/linkedlist.h"

int main(void)
{
    LinkedList *int_list;
    int_list = newLinkedList(sizeof(int));
    
    for (int i = 1; i <= 10; i++) {
        int_list->append(int_list, &i);
    }

    int_list->destroy(int_list);
}