#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "dlist.h"

void read_list(dl_head *listhead){
	dl_node *curr;
	int num;
	
	scanf("%d",&num);
	while(num >= 0){
		curr = dl_node_create(num);
		dl_list_append(listhead,curr);
		scanf("%d",&num);
	}
	return;
}

void dl_list_insertion_sort(dl_head *head){

	dl_node *curr = head->sentinel.nxt->nxt;
	dl_node *i,*tmp;
	unsigned j=1;

	for(;curr != &head->sentinel ;curr =curr->nxt,j++){

		for(i=curr->prv ;i->nxt != &head->sentinel ;i =i->prv){
			if(i->key<=curr->key){
				tmp = curr->nxt;
				_dl_node_detach_byaddress(curr);
				_dl_list_add_after(i,curr);
				curr = tmp->prv;
				break;
			}
		}

	}

	head->is_sorted =1;
	return;	
}

int main(void){
	
	
	dl_head head;
	dl_head_init(&head);
	read_list(&head);
	dl_list_insertion_sort(&head);
	dl_node *tmp;
	
	tree_node *curr,*root = NULL;
	
	while(head.size){
		tmp = dl_list_pop0(&head);
		curr = node_create();
		curr->key = tmp->key;
		add2_avl_tree(&root,curr);
		free(tmp);
	}
	
	/*
	int key;
	scanf("%d",&key);
	while(key>=0){
		curr = node_create();
		curr->key = key;
		add2_avl_tree(&root,curr);
		scanf("%d",&key);
	}
	*/
	preorder_print(root);
	putchar('\n');
	tree_delete(root);
	return(0);
}

