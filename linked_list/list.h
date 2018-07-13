//
// Created by Oleg on 09.07.2018.
//
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef MYLIST_LIST_H
#define MYLIST_LIST_H

//#define NULL (void *)0


struct list_node
{
    void *data;
    struct list_node *next;
    struct list_node *prev;
};

struct info_list
{
    struct list_node *head;
    int size;
};

#define list_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define for_each_list(ptr, list) \
    for (int i=0; i<list->size; i++, ptr=ptr->next)

#define for_each_list_i(i,ptr, list) \
    for (i=0, ptr=list->head; i<list->size; i++, ptr=ptr->next)

void INIT_LIST(struct info_list *); //done

void INIT_ENTRY_LINKS(struct list_node *entry); //done

void add_to_list_at_index(struct list_node *new, struct info_list *, int index); //done

void add_to_tail_list(struct list_node *new, struct info_list *);//done

void add_to_head_list(struct list_node *new, struct info_list *);//done

void delete_from_list_at_index(struct info_list *, int index); //done

void delete_node_from_list(struct list_node *entry, struct info_list *);//done

void clear_list(struct info_list *);//done

void revesre_list(struct info_list *);//done

int count_of_entry_in_list(struct info_list *);//done

void copy_to_new_List(struct info_list* newList, struct info_list* copyList, int index1, int index2, void (*copy_func)(const struct list_node *, const struct list_node *));
void copy_to_tail_old_List(struct info_list* newList, struct info_list* copyList, void (*copy_func)(const struct list_node *, const struct list_node *));


#define createNode(type)\
    ({\
    struct list_node *tmp=(struct list_node *)malloc(sizeof(struct list_node));\
    if(tmp!=NULL) INIT_ENTRY_LINKS(tmp);\
    type *dataT=(type *)malloc(sizeof(type));\
    tmp->data=dataT;\
    tmp;\
})
#define createList(count)\
    ({\
    struct info_list *tmp=(struct info_list *)malloc(count*sizeof(struct info_list));\
    if(tmp!=NULL) INIT_LIST(tmp);\
    tmp;\
})

#define deleteNode(node)\
    {\
    free(node->data);\
    free(node);\
}



#define set_links_at_index(ptr, index)\
    {\
        for (int i = 1; i <=index; ++i) {\
        ptr=ptr->next;\
        }\
    }

#define slice(aList, a, b, type, copy_func)\
({\
    struct info_list *newList=createList(1);\
    struct list_node *intNode[b-a+1];\
    for (int i = 0; i <b-a+1 ; ++i) {\
        intNode[i]=createNode(type);\
        add_to_tail_list(intNode[i], newList);\
    }\
    copy_to_new_List(newList, aList, a, b, copy_func);\
    newList;\
})


#define extend(oldList, copyList, type, copy_func)\
{\
    if(oldList==NULL || copyList==NULL) return 0;\
    struct list_node *intNode[copyList->size];\
    for(int i=0; i<copyList->size; i++)\
    {   \
        intNode[i]=createNode(type);\
        add_to_tail_list(intNode[i], oldList);\
    }\
    \
    struct list_node *oldNodes=oldList->head;\
    set_links_at_index(oldNodes, oldList->size-copyList->size);\
    struct list_node *copyNodes=copyList->head;\
    \
    for (int j = 0; j < copyList->size; ++j) {\
        copy_func(oldNodes, copyNodes);\
        oldNodes=oldNodes->next;\
        copyNodes=copyNodes->next;\
    }\
}

void deleteList(struct info_list *aList);

#endif //MYLIST_LIST_H
