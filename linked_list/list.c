//
// Created by Oleg on 09.07.2018.
//

#include <stdio.h>

#include "list.h"

void add_to_list_between_entry(struct list_node *new, struct list_node *entry1, struct list_node *entry2);
void add_first_element_to_list(struct list_node *new, struct info_list *);
void add_second_element(struct list_node *new, struct list_node *head);
void delete_entry(struct list_node *entry);


void INIT_LIST(struct info_list *aList)
{
    aList->head=NULL;
    aList->size=0;
}

void INIT_ENTRY_LINKS(struct list_node *entry)
{
    entry->next=entry;
    entry->prev=entry;
}

void add_to_list_at_index(struct list_node *new, struct info_list *aList, int index)
{
    if(aList->size<index || index<0) {printf("Error: Wrong index, max index is %d\n", aList->size); return;}

    if(aList->size==0) {add_first_element_to_list(new, aList); return;}

    if(index==0)
    {
        add_to_head_list(new, aList);
        return;

    } else if(index==aList->size)
    {
        add_to_tail_list(new, aList);
        return;
    }

    struct list_node *current=aList->head;

    for (int i = 1; i <=index ; ++i) {
        current=current->next;
    }
    add_to_list_between_entry(new, current->prev, current);
    aList->size++;

}

void add_to_head_list(struct list_node *new, struct info_list *aList)
{
    if(aList->size==0) {add_first_element_to_list(new, aList); return;}

    aList->head->next==aList->head? add_second_element(aList->head, new) : add_to_list_between_entry(new, aList->head->prev, aList->head);
    aList->head=new;
    aList->size++;
}

void add_to_tail_list(struct list_node *new, struct info_list *aList)
{
    if(aList->size==0) {add_first_element_to_list(new, aList); return;}

    aList->head->next==aList->head ? add_second_element(new, aList->head) : add_to_list_between_entry(new, aList->head->prev, aList->head);
    aList->size++;
}

void delete_from_list_at_index(struct info_list *aList, int index)
{
    if(aList->size==0) {printf("Error: You can't delete entry from empty list.\n"); return;}

    if(index<0 || aList->size-1<index) {printf("Error: Wrong index, max index is %d.\n", aList->size-1); return;}

    if(aList->size==1)
    {
        aList->head=NULL;
        aList->size--;
        return;
    }

    struct list_node *current=aList->head;

    if(index==0)
    {
        aList->head=aList->head->next;
    }

    for (int i = 1; i <=index ; ++i) {
        current=current->next;
    }
    delete_entry(current);
    aList->size--;
}

void delete_node_from_list(struct list_node *entry, struct info_list *aList)
{
    if(aList->size==0) {printf("Error: You can't delete entry from empty list.\n"); return;}

    if(aList->size==1)
    {
        aList->head=NULL;
        aList->size--;
        return;
    }

    if(aList->head==entry)
    {
        aList->head=entry->next;
    }

    delete_entry(entry);
    aList->size--;

}

void clear_list(struct info_list *aList)
{
    if(aList->size==0){ printf("Error: U can't clear empty list.\n"); return;}

    if(aList->size==1) {aList->head=NULL; return;}

    struct list_node *current=aList->head;
    struct list_node *for_delete;

    for (int i = 0; i < aList->size; ++i) {
        for_delete=current;
        current=current->next;
        INIT_ENTRY_LINKS(for_delete);
    }
    INIT_LIST(aList);
}

void revesre_list(struct info_list *aList)
{
    if(aList->size==0){printf("Error: U can't reverse empty list.\n"); return;}

    if(aList->size==1) {printf("Error: U can't reverse list with one element.\n"); return;}



    struct list_node *current=aList->head;
    struct list_node *for_reverse;
    struct list_node *tmp;

    aList->head=aList->head->prev;

    for (int i = 0; i <aList->size ; ++i) {

        for_reverse=current;
        current=current->next;

        tmp=for_reverse->next;
        for_reverse->next=for_reverse->prev;
        for_reverse->prev=tmp;
    }


}

int count_of_entry_in_list(struct info_list *aList)
{
    return aList->size;
}


//_____________________________

void delete_entry(struct list_node *entry)
{
    if(entry->next!=entry || entry->next!=NULL)
    {
        entry->next->prev=entry->prev;
        entry->prev->next=entry->next;
        INIT_ENTRY_LINKS(entry);
    }

}

void add_second_element(struct list_node *new, struct list_node *head)
{
    head->next=new;
    head->prev=new;
    new->prev=head;
    new->next=head;
}

void add_to_list_between_entry(struct list_node *new, struct list_node *entry1, struct list_node *entry2)
{
    entry1->next=new;
    new->prev=entry1;
    new->next=entry2;
    entry2->prev=new;
}

void add_first_element_to_list(struct list_node *new, struct info_list *aList)
{
    if(new->prev!=new || new->next!=new) INIT_ENTRY_LINKS(new);
    aList->head=new;
    aList->size++;
}


void copy_to_new_List(struct info_list* newList, struct info_list* copyList, int index1, int index2, void (*copy_func)(const struct list_node *, const struct list_node *))
{

    if(newList==NULL || copyList==NULL) return;
    if(index2>=copyList->size) return;
    if(index1>index2) return;
    if(index1<0 || index2<0) return;
    if(newList->size>copyList->size) return;
    if(index2-index1+1>newList->size) return;

    struct list_node *newNodes=newList->head;

    struct list_node *copyNodes=copyList->head;
    set_links_at_index(copyNodes, index1);

    for (int j = 0; j < index2-index1+1; ++j) {
        copy_func(newNodes, copyNodes);
        newNodes=newNodes->next;
        copyNodes=copyNodes->next;
    }
}

void deleteList(struct info_list *aList)
{
    struct list_node *current=aList->head;
    struct list_node *next;
    for (int i = 0; i <aList->size ; ++i) {
        next=current->next;
        delete_node_from_list(current, aList);
        current=next;
    }
    free(aList);
}