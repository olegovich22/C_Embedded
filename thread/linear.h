
struct info_for_thread
{
	int *arr;
	int first;
	int last;
	int key;
};

int fill_arr_random(int *arr, int size);

int linear_search(int *arr, int first_index, int last_index, int key);
int linear_search2(int *arr, int first_index, int last_index, int key);

int linear_search_thread(int *arr, int size, int a_key, int count_threads);
