#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "list.h"

struct intO
{
    int dataInt;
    int data2;
};

bool SCompare(const struct list_node * a, const struct list_node * b)
{
    bool o=0;
    struct intO *data1=a->data;
    struct intO *data2=b->data;

    if(data1->dataInt<data2->dataInt)
    {
        o=1;
    }
    return o;
}

void init_rule(struct intO *s, int data, int data2)
{
    s->dataInt=data;
    s->data2=data2;
}

void print_rule(struct intO *s)
{
    printf("[%d, %d]\n", s->dataInt, s->data2);
}

void copyFun(const struct list_node *new, const struct list_node *old)
{
    struct intO *new1=new->data;
    struct intO *old1=old->data;

    new1->dataInt=old1->dataInt;
    new1->data2=old1->data2;
}

int main() {

    struct info_list *aList=createList(1);

    struct list_node *intNode[5];

    for (int i = 0; i <5 ; ++i) {
        intNode[i]=createNode(struct intO);

        init_rule(intNode[i]->data, i,i);

        add_to_tail_list(intNode[i], aList);

    }

    struct list_node *ptr=aList->head;
    for_each_list(ptr, aList)
    {
        print_rule(ptr->data);
    }
    printf("\n\n");

    struct info_list *aList2=slice(aList, 0, 3, struct intO, copyFun);
    extend(aList2, aList, struct intO, copyFun);
    ptr=aList2->head;
    for_each_list(ptr, aList2)
    {
        print_rule(ptr->data);
    }

    deleteList(aList);
    deleteList(aList2);

    return 0;
}