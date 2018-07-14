
#ifndef MYLIST_SORT_H
#define MYLIST_SORT_H

#include "list.h"
#include <stdbool.h>

/**
 * bubbleSort() - function for sort list
 * @aList: list which we will sort
 * @cmp_func: function for compare elements. This function can wright user for any data structures
 *
 */
void bubbleSort(struct list *aList, bool (*cmp_func)(const struct list_node *, const struct list_node *));


#endif //MYLIST_SORT_H
