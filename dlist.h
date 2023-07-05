#ifndef __DLIST_H_
#define __DLIST_H_

//double linked list with sentinel (circled)
//This data structure features fifo and stack capabilities

struct double_linked_list_node{
	unsigned key;
	struct double_linked_list_node *prv;
	struct double_linked_list_node *nxt;
};
typedef struct double_linked_list_node dl_node;

struct double_linked_list_head{
	struct double_linked_list_node sentinel;
	/*An extreme implementation for many heads and limited storage (maybe for many but short lists)
	//most significant digit determines if the list is sorted or not (1=sorted), the rest determine the size
	int coredata; //basically is_sorted and size
	*/
	unsigned size;
	char is_sorted;
	//any other list info
};
typedef struct double_linked_list_head dl_head;

/*
unsigned dl_coredata_size(int coredata);

unsigned dl_coredata_is_sorted(int coredata);

int dl_coredata_add2size(int *coredata);
*/

//List creation and deletion
void dl_head_init(dl_head *head);

void dl_sentinel_init(dl_node *sentinel);

dl_node* dl_node_create(int node_key);

void dl_list_delete(dl_head *head);
//

//Add and remove functions
void _dl_list_add_after(dl_node *destination ,dl_node *new);

void dl_list_append(dl_head *head ,dl_node *new);

void dl_list_prepend(dl_head *head ,dl_node *new);

dl_node* _dl_node_detach_byaddress(dl_node *target);

dl_node* dl_list_pop(dl_head *head);

dl_node* dl_list_pop0(dl_head *head);

//

void dl_list_node_swap(dl_node *node1 ,dl_node *node2);

void dl_list_print(dl_head *head);

void dl_list_print_reverse(dl_head *head);

void dl_list_print_partition(dl_node *start ,dl_node *end);

unsigned dl_list_size_partition(dl_node *left,dl_node *right);

dl_node* dl_node_nxt(dl_node *node,unsigned steps);


#endif