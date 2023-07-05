#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"
#include "tree.h"

void read_list(dl_head *listhead){
	dl_node *curr;
	int num;
	
	scanf("%d",&num);
	while(num > 0){
		curr = dl_node_create(num);
		dl_list_append(listhead,curr);
		scanf("%d",&num);
	}
	return;
}

int main(void){

	dl_head head;
	dl_head_init(&head);
	read_list(&head);
	unsigned array[head.size];
	unsigned i,size = head.size;
	dl_node *tmp;

	//construct pre-order array from list (and deleting the list)
	for(i=0;head.size;i++){
		tmp = dl_list_pop0(&head);
		array[i] = tmp->key;
		free(tmp);
	}
	//

	printf("Enter integer: ");
	scanf("%d",&i);

	//construct tree and search node in it
	tree_node *searched_node,*root = preorder_to_tree(array,size);
	searched_node = search_bst(root,i);
	//
	
	if(searched_node == NULL){
		printf("%d not found!\n",i);
		return(0);
	}

	i = tree_node_lvl_calc(searched_node);
	printf("\nIntegers in level %u are: ",i-1);
	tree_to_levelorder_lvl_print(root,i);
	putchar('\n');
	
	tree_delete(root);
	return(0);
}