//
// Created by Oleg on 12.07.2018.
//

#ifndef MYLIST_SORT_H
#define MYLIST_SORT_H

#include "list.h"

void swap(struct info_list *aList, int index1, int index2);

void bubbleSort(struct info_list *aList, bool (*cmp_func)(const struct list_node *, const struct list_node *));




#endif //MYLIST_SORT_H
