#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "list.h"
#include <time.h>

/**
 * struct int_struct - data structure which will storage in list node.
 * @dataInt1: data
 * @dataInt2: data.
 *
 * This structure you can build on your own for your tasks or you can use simple data type.
 */
struct int_struct
{
    int dataInt1;
    int dataInt2;
};

//EXAMPLE FOR RULE FUNCTIONS
//This list very flexible. You can use it easy for any data structure
//but for successful using it you should implement some function which will necessary for work.

/**
 * compare_rule() - function for compare 2 nodes. Use for sort.
 * @a: first node for compare
 * @b: second node for compare
 *
 * Return:
 *  0  - a<b
 *  1  - a>b
 *
 * This function you can build on your own for your tasks.
 *
 */
bool compare_rule(const struct list_node *a, const struct list_node *b)
{
    struct int_struct *data1=a->data;
    struct int_struct *data2=b->data;

    return data1->dataInt1 > data2->dataInt1;
}

/**
 * init_rule() - function for initialization your structure.
 * @aNode: list node which we need to init.
 * @i1: data for initialization
 * @i2: data for initialization
 *
 * This function you can build on your own for your tasks.
 *
 */
void init_rule(struct list_node *aNode, int i1, int i2)
{
    struct int_struct *data=aNode->data;

    data->dataInt1=i1;
    data->dataInt2=i2;
}

/**
 * print_rule() - function for print data from your structure.
 * @aNode: list node which we will print
 *
 * This function you can build on your own for your tasks.
 *
 */
void print_rule(struct list_node *aNode)
{
    struct int_struct *data=aNode->data;
    printf("[%d, %d]\n", data->dataInt1, data->dataInt2);
}

/**
 * print_rule() - function for copy nodes. Information from old copy to new Use for slice and extend operations where we need to do it.
 * @old: list node information copy from
 * @new: list node information copy to
 *
 * This function you can build on your own for your tasks.
 *
 */
void copy_rule(const struct list_node *new, const struct list_node *old)
{
    struct int_struct *new1=new->data;
    struct int_struct *old1=old->data;

    new1->dataInt1=old1->dataInt1;
    new1->dataInt2=old1->dataInt2;
}

//good example for using basic functions
int main() {

    srand(time(NULL));

    //create list
    struct list *aList=createList;

    //create nodes and fill it into list
    struct list_node *intNode[5];
    for (int i = 0; i <5 ; ++i) {
        intNode[i]=createNode(struct int_struct);
        init_rule(intNode[i], rand()%100+1,rand()%10+1);
        add_to_tail_list(intNode[i], aList);
    }

    //traverse example
    //print list
    struct list_node *ptr=aList->head;
    for_each_list(ptr, aList)
    {
        //struct int_struct* data_from_struct=ptr->data;
        print_rule(ptr);
    }

    printf("\n\n");

    //slice and extend operations
    struct list *aList2=slice(aList, 0, 3, struct int_struct, copy_rule);
    extend(aList2, aList, struct int_struct, copy_rule);

    //sorting
    bubbleSort(aList2, compare_rule);

    //print result
    ptr=aList2->head;
    for_each_list(ptr, aList2)
    {
        print_rule(ptr);
    }

    //clear memory
    deleteList(aList);
    deleteList(aList2);

    return 0;
}