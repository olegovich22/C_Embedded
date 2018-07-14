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

<code>
struct list_node<br>
{<br>
    void *data;<br>
    struct list_node *next;<br>
    struct list_node *prev;<br>
};
</code>


