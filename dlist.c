#include "dlist.h"
#include <stdlib.h>
#include <stdio.h>

//List creation and deletion

void dl_head_init(dl_head *head){
	dl_sentinel_init(&head->sentinel);
	head->size = 0;
	head->is_sorted = 0;
}

void dl_sentinel_init(dl_node *sentinel){
	sentinel->key = 0;
	sentinel->nxt = sentinel;
	sentinel->prv = sentinel;
}

dl_node* dl_node_create(int node_key){
	dl_node *node = (dl_node*) malloc(sizeof(dl_node));
	node->key = node_key;
	node->nxt = (node->prv = NULL);
	return(node);
}

void dl_list_delete(dl_head *head){
	dl_node *node = head->sentinel.nxt;

	//jump to nxt deleting current node
	while(node->key){
		node = node->nxt;
		free(node->prv);
	}
	head->size = 0;
	return;
}
//

//Add and remove functions

void _dl_list_add_after(dl_node *destination ,dl_node *new){
	dl_node *end = destination->nxt;
	destination->nxt = new;
	new->prv = destination;
	new->nxt = end;
	end->prv = new;
	return;
}

void dl_list_append(dl_head *head ,dl_node *new){
	head->size++;
	head->is_sorted = 0;
	_dl_list_add_after(head->sentinel.prv,new);
}

void dl_list_prepend(dl_head *head ,dl_node *new){
	head->is_sorted =0;
	head->size++;
	_dl_list_add_after(&head->sentinel,new);
}

dl_node* _dl_node_detach_byaddress(dl_node *detachable){
	dl_node *prv = detachable->prv ,*nxt =detachable->nxt;
	prv->nxt = nxt;
	nxt->prv = prv;
	detachable->nxt = (detachable->prv = NULL);
	return(detachable);
}

dl_node* dl_list_pop(dl_head *head){
	head->size--;
	return(_dl_node_detach_byaddress(head->sentinel.prv));
}

dl_node* dl_list_pop0(dl_head *head){
	head->size--;
	return(_dl_node_detach_byaddress(head->sentinel.nxt));
}
//

void dl_list_node_swap(dl_node *node1 ,dl_node *node2){
	if(node1 == node2){
		return;
	}

	dl_node *prev1 = node1->prv ,*prev2 = node2->prv;
	
	if(node2->nxt == node1 || node1->nxt == node2){
		if(node1->nxt == node2){
			prev2=node1;
			node1 = node2;
			node2 = prev2;
			prev2 =prev1;
		}
		_dl_node_detach_byaddress(node1);
		_dl_list_add_after(prev2,node1);
		_dl_node_detach_byaddress(node2);
		_dl_list_add_after(node1,node2);
		return;
	}

	_dl_node_detach_byaddress(node1);
	_dl_list_add_after(prev2,node1);
	_dl_node_detach_byaddress(node2);
	_dl_list_add_after(prev1,node2);

	return;
}

void dl_list_print(dl_head *head){
	dl_node *curr = head->sentinel.nxt;
	for(;curr!= &head->sentinel;curr =curr->nxt){
		printf("%d ",curr->key);
	}
	putchar('\n');
	return;
}

void dl_list_print_reverse(dl_head *head){
	dl_node *curr = head->sentinel.prv;
	for(;curr != &head->sentinel;curr =curr->prv){
		printf("%d ",curr->key);
	}
	putchar('\n');
	return;	
}


void dl_list_print_partition(dl_node *start ,dl_node *end){
	for(;start!=end ;start =start->nxt){
		printf("%d ",start->key);
	}
	printf("%d \n",start->key);//I put an extra space
	
}

unsigned dl_list_size_partition(dl_node *left,dl_node *right){
	unsigned i;
	for(i=1;left != right ;left = left->nxt ,i++);
	return(i);
}

dl_node* dl_node_nxt(dl_node *node,unsigned steps){
	for(;steps;steps--,node =node->nxt);
	return(node);
}