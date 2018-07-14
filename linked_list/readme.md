# Linked List

## What can you do

* <b>add_to_list_at_index()</b> - function for add node to list at any index from 0 to size-1.

* <b>add_to_tail_list()</b> - function for add node in the end of list.

* <b>add_to_head_list()</b> - function for add node at begin of list.

* <b>delete_from_list_at_index()</b> - function for delete node in list at any index from 0 to size-1.

* <b>delete_node_from_list()</b> - function for delete node from list.

* <b>clear_list()</b> - function for clearing list from nodes. After using this function you get empty list.

* <b>revesre_list()</b> - function for reverse list. After using this function you get reverse(upside-down) list.

* <b>count_of_entry_in_list()</b> - function for showing how many elements in list.

* <b>slice()</b> - function for creating new list as copy another list from a to b node.

* <b>extend()</b> - function for adding copy of another list to the end of list which we want.

* <b>bubbleSort()</b> - function for sort list

## Rule functions

This list for using by all data type, from int till big and hard structures. But for some operations for example compare, print or init, impossible write universal function. That's why exists rule functions.

### Example. How implement.

Node struct

```C
struct list_node
{
    void *data;
    struct list_node *next;
    struct list_node *prev;
};
```
Data struct
```C
struct int_struct
{
    int dataInt1;
    int dataInt2;
};
```
And example

```C
//compare_rule() - function for compare 2 nodes. Use for sort.
bool compare_rule(const struct list_node *a, const struct list_node *b)
{
    struct int_struct *data1=a->data;
    struct int_struct *data2=b->data;

    return data1->dataInt1 > data2->dataInt1;
}

//function for initialization your structure.
void init_rule(struct list_node *aNode, int i1, int i2)
{
    struct int_struct *data=aNode->data;

    data->dataInt1=i1;
    data->dataInt2=i2;
}

//function for print data from your structure.
void print_rule(struct list_node *aNode)
{
    struct int_struct *data=aNode->data;
    printf("[%d, %d]\n", data->dataInt1, data->dataInt2);
}

//function for copy nodes. Information from old copy to new Use for slice and extend operations where we need to do it.
void copy_rule(const struct list_node *new, const struct list_node *old)
{
    struct int_struct *new1=new->data;
    struct int_struct *old1=old->data;

    new1->dataInt1=old1->dataInt1;
    new1->dataInt2=old1->dataInt2;
}

```



