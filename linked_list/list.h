
#include <stdlib.h>

#ifndef MYLIST_LIST_H
#define MYLIST_LIST_H

/**
 * struct list_node - node for list.
 * @data: pointer for data in this node. It can be any data structure or simple data types.
 * @next: link to next node.
 * @prev: link to prev node.
 *
 * Base node for list. Every node storage data which user need.
 *
 */
struct list_node
{
    void *data;
    struct list_node *next;
    struct list_node *prev;
};

/**
 * struct list - main structure for list
 * @head: pointer on head of list(first node in list)
 * @size: count of elements in list.
 *
 * This a main structure for list which has all information for control and using list.
 *
 */
struct list
{
    struct list_node *head;
    int size;
};

/**
 * INIT_LIST() - function for initialization list(set his param in base)
 * @aList: list which we will to init
 *
 */
void INIT_LIST(struct list *aList);

/**
 * INIT_ENTRY_LINKS() - function for initialization node links in NULL
 * @entry: node which we will to init
 *
 */
void INIT_ENTRY_LINKS(struct list_node *entry);

/**
 * add_to_list_at_index() - function for add node to list at any index from 0 to size-1.
 * @new: node which we will add to list
 * @aList: list in which we want to add new node
 * @index: index in list where we want to add new node
 *
 *
 */
void add_to_list_at_index(struct list_node *new, struct list *aList, int index);

/**
 * add_to_tail_list() - function for add node in the end of list.
 * @new: node which we will add to list
 * @aList: list in which we want to add new node
 *
 *
 */
void add_to_tail_list(struct list_node *new, struct list *aList);

/**
 * add_to_tail_list() - function for add node at begin of list.
 * @new: node which we will add to list
 * @aList: list in which we want to add new node
 *
 *
 */
void add_to_head_list(struct list_node *new, struct list *aList);

/**
 * delete_from_list_at_index() - function for delete node in list at any index from 0 to size-1.
 * @aList: list from which we want to delete node
 * @index: index in list where we want to delete node
 *
 *
 */
void delete_from_list_at_index(struct list *aList, int index);

/**
 * delete_node_from_list() - function for delete node from list.
 * @entry: node which we will delete
 * @aList: list from which we want to delete node
 *
 *
 */
void delete_node_from_list(struct list_node *entry, struct list *aList);

/**
 * clear_list() - function for clearing list from nodes. After using this function you get empty list.
 * @aList: list which we want to clear
 *
 *
 */
void clear_list(struct list *aList);

/**
 * revesre_list() - function for reverse list. After using this function you get reverse(upside-down) list.
 * @aList: list which we want to reverse
 *
 *
 */
void revesre_list(struct list *aList);

/**
 * count_of_entry_in_list() - function for showing how many elements in list.
 * @aList: your list
 *
 * Return:
 *  count of elements   -  OK
 *  -1                  -  wrong list(NULL)
 */
int count_of_entry_in_list(struct list *aList);

/**
 * copy_part_of_list_to_new_List() - function for copy part of list to new List.
 * @newList:  new empty list where will copy list for copy
 * @copyList: list from which will copy data
 * @index1: index from which begin copy nodes
 * @index2: till thist index will copy nodes
 * @copy_func: rule for copy. User can write it for every structure
 *
 *
 */
void copy_part_of_list_to_new_List(struct list *newList, struct list *copyList, int index1, int index2,
                                   void (*copy_func)(const struct list_node *, const struct list_node *));
/**
 * deleteList() - function for delete list.
 * @aList: list which we want to delete
 *
 * After using this function you free all memory which has allocated on nodes and list.
 * You should use it after end of using list. It very important for avoid memory liquid
 */
void deleteList(struct list *aList);


//loop for bypassing list
#define for_each_list(ptr, list) \
    for (int i=0; i<list->size; i++, ptr=ptr->next)

//loop for bypassing list
#define for_each_list_i(i,ptr, list) \
    for (i=0, ptr=list->head; i<list->size; i++, ptr=ptr->next)

/**
 * createNode() - function for creating new node.
 * @type: data type which will storage in this node
 *
 * This function allocate new memory for node. Don't forget delete it after using if you don'y want memory liquid.
 * Return pointer on new node.
 *
 * Return:
 *  list_node *          -  OK
 *  NULL                 -  if program couldn't allocate memory
 */
#define createNode(type)\
    ({\
    struct list_node *tmp=(struct list_node *)malloc(sizeof(struct list_node));\
    if(tmp!=NULL) INIT_ENTRY_LINKS(tmp);\
    type *dataT=(type *)malloc(sizeof(type));\
    tmp->data=dataT;\
    tmp;\
})

/**
 * createList - function for creating new list.
 *
 * This function allocate new memory for list. Don't forget delete it after using if you don'y want memory liquid.
 * Return pointer on new list.
 *
 * Return:
 *  list_node *          -  OK
 *  NULL                 -  if program couldn't allocate memory
 */
#define createList\
    ({\
    struct list *tmp=(struct list *)malloc(sizeof(struct list));\
    if(tmp!=NULL) INIT_LIST(tmp);\
    tmp;\
})

/**
 * deleteNode() - function for delete node.
 * @node: list which we want to delete
 *
 * This function free memory which allocated for node
 *
 */
#define deleteNode(node)\
    {\
    free(node->data);\
    free(node);\
}

/**
 * set_links_at_index() - function for set list_node pointer at index which you need
 * @ptr: pointer list_node. It must be initialized at first node in list
 * @index: index on which you need set list_node pointer
 *
 *
 */
#define set_links_at_index(ptr, index)\
    {\
        for (int i = 1; i <=index; ++i) {\
        ptr=ptr->next;\
        }\
    }

/**
 * slice() - function for creating new list as copy another list from a to b node.
 * @aList: list from we will copy
 * @a: index from which begin copy nodes
 * @b: till this index will copy nodes
 * @type: data type of data in nodes which we will copy
 * @copy_func: rule for copy. User can write it for every structure
 *
 *
 * Return:
 *  list *               -  OK
 *  NULL                 -  if program couldn't allocate memory
 */
#define slice(aList, a, b, type, copy_func)\
({\
    struct list *newList=createList;\
    struct list_node *intNode[b-a+1];\
    for (int i = 0; i <b-a+1 ; ++i) {\
        intNode[i]=createNode(type);\
        add_to_tail_list(intNode[i], newList);\
    }\
    copy_part_of_list_to_new_List(newList, aList, a, b, copy_func);\
    newList;\
})

/**
 * extend() - function for adding copy of another list to the end of list which we want.
 * @copyList: list from which we will copy
 * @oldList: list at the end of which we will copy @copyList
 * @type: data type of data in nodes which we will copy
 * @copy_func: rule for copy. User can write it for every structure
 *
 */
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

#endif //MYLIST_LIST_H
