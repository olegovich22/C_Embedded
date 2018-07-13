#include "sort.h"
#include "list.h"

void swap(struct info_list *aList, int index1, int index2)
{
    if(index1>index2)
    {
        int tmp=index1;
        index1=index2;
        index2=tmp;
    }

    struct list_node *tmpNext;
    struct list_node *tmpPrev;

    struct list_node *entry1=aList->head;
    struct list_node *entry2=aList->head;


    for (int i = 0; i <=index2; ++i) {
        if(i<index1) entry1=entry1->next;
        if(i<index2) entry2=entry2->next;
    }

    if(index1 == 0) aList->head=entry2;


    if((index2-index1)==1)
    {
        tmpNext=entry2->next;
        tmpPrev=entry1->prev;

        tmpPrev->next=entry2;
        entry2->prev=tmpPrev;
        entry2->next=entry1;
        entry1->prev=entry2;
        entry1->next=tmpNext;
        tmpNext->prev=entry1;

    } else{
        tmpNext=entry2->next;
        tmpPrev=entry2->prev;

        entry1->prev->next=entry2;
        entry2->prev=entry1->prev->next;

        entry2->next=entry1->next;
        entry1->next->prev=entry2;

        tmpPrev->next=entry1;
        entry1->prev=tmpPrev;

        entry1->next=tmpNext;
        tmpNext->prev=entry1;
    }


}

void bubbleSort(struct info_list *aList, bool (*cmp_func)(const struct list_node *, const struct list_node *))
{
    for (int theOut = aList->size - 1; theOut > 1; theOut --)
    {
        for (int theIn = 0; theIn < theOut; theIn ++)
        {
            struct list_node* node1=aList->head;
            struct list_node* node2=aList->head;
            set_links_at_index(node1, theIn);
            set_links_at_index(node2, theIn+1);

            if (cmp_func(node1, node2))
            {
                swap(aList, theIn, theIn+1);
            }
        }
    }

}