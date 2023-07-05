#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

#include "dlist.h"

void read_list(dl_head *head){
	int key=1;
	scanf("%d",&key);
	while(key>=0){
		dl_list_append(head,dl_node_create(key));
		scanf("%d",&key);
	}

}


int main(int argc,char *argv[]){

	if(argv[1] == NULL || atoi(argv[1]) < 1  || 6 < atoi(argv[1]) ){
		printf("Invalid argument\n");
		return(0);
	}

	if( (atoi(argv[1]) ==5 || atoi(argv[1]) ==6) && (argv[2] == NULL || (atoi(argv[2])!=1 && atoi(argv[2])!=2 && atoi(argv[2])!=4 && atoi(argv[2])!=8 && atoi(argv[2])!=16) ) ){
		printf("Invalid argument\n");
		return(0);
	}

	dl_head head;
	dl_head_init(&head);
	read_list(&head);

	dl_list_print(&head);
	putchar('\n');

	
	switch(atoi(argv[1])){
		case 1:
			dl_list_insertion_sort(&head);
			break;
		case 2:
			dl_list_selection_sort(&head);
			break;
		case 3:
			dl_list_quick_sort(&head);
 			break;
		case 4:
			dl_list_merge_sort(&head);
			break;
		case 5:
			dl_list_radix_sort_msd(&head,atoi(argv[2]));
			break;
		case 6:
			dl_list_radix_sort_lsd(&head,atoi(argv[2]));
			break;
		default:
			break;
	}

	putchar('\n');
	dl_list_print(&head);

	dl_list_delete(&head);

	return(0);
}
