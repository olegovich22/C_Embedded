# Linked List

## What can you do

* add_to_list_at_index(struct list_node *new, struct list *aList, int index); - function for add node to list at any index from 0 to size-1.

* add_to_tail_list(struct list_node *new, struct list *aList); - function for add node in the end of list.

* add_to_head_list(struct list_node *new, struct list *aList); - function for add node at begin of list.

* delete_from_list_at_index(struct list *aList, int index); - function for delete node in list at any index from 0 to size-1.

* delete_node_from_list(struct list_node *entry, struct list *aList); - function for delete node from list.

* clear_list(struct list *aList); - function for clearing list from nodes. After using this function you get empty list.

* revesre_list(struct list *aList); - function for reverse list. After using this function you get reverse(upside-down) list.

* count_of_entry_in_list(struct list *aList); - function for showing how many elements in list.

* slice(aList, a, b, type, copy_func)\ - function for creating new list as copy another list from a to b node.

* extend(oldList, copyList, type, copy_func) - function for adding copy of another list to the end of list which we want.

* bubbleSort(struct list *aList, bool (*cmp_func)(const struct list_node *, const struct list_node *)) - function for sort list

## Rule functions

This list for using by all data type, from int till big and hard structures. But for some operations for example compare, print or init, impossible write universal function. That's why exists rule functions.

### Example. How implement.

Node struct

<code>
struct list_node
{
    void *data;
    struct list_node *next;
    struct list_node *prev;
};
</code>


