#include "sort.h"


unsigned extract_digit_msb(unsigned num ,const unsigned DIGIT_LENGTH ,const unsigned LVL){
	num >>= 8*sizeof(num) - DIGIT_LENGTH*(LVL+1) ;
	//num >>=DIGIT_LENGTH*LVL;
	unsigned i,res=0;
	for(i=1 ;i< pow(2,DIGIT_LENGTH) ;i<<=1){
		res = res | (num&i);
	}
	return(res);
}

unsigned extract_digit_lsb(unsigned num ,const unsigned DIGIT_LENGTH ,const unsigned LVL){
	num >>=DIGIT_LENGTH*LVL;
	unsigned i,res=0;
	for(i=1 ;i< pow(2,DIGIT_LENGTH) ;i<<=1){
		res = res | (num&i);
	}
	return(res);
}

void num2binary_print(unsigned num, unsigned short digits){
    unsigned short i = 8*sizeof(num) - digits ;
    num <<=i;

    for(i=digits ;i ;i--,num<<=1){
        printf("%d",num&0x80000000?1:0);
    }

}

void _dl_list_print_lsd(dl_head *head,const unsigned DIGIT_LENGTH ,unsigned lvl){
	unsigned digit;
	dl_node *curr = head->sentinel.nxt;
	for(;curr!= &head->sentinel;curr =curr->nxt){
		printf("%d(",curr->key);
		digit = extract_digit_lsb(curr->key,DIGIT_LENGTH,lvl);
		num2binary_print(digit,DIGIT_LENGTH);
		printf(") ");
	}
	putchar('\n');
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
		printf(" [%d]: ",j);
		dl_list_print(head);
	}

	head->is_sorted =1;
	return;	
}

void dl_list_selection_sort(dl_head *head){
	dl_node *curr = head->sentinel.nxt;//unsorted array pointer
	dl_node *i,*min;
	unsigned j=1;


	for(;curr != head->sentinel.prv ;curr =curr->nxt,j++){
		//printf("-%d-",curr->key);

		
		//find min in unsorted array
		for(i =curr,min =curr; i != &head->sentinel ;i = i->nxt){
			if(i->key < min->key){
				min = i;
			}
		}

		//swap it with the first pos of unsorted array
		if(min != curr){
			dl_list_node_swap(min,curr);
			curr = min;
		}

		printf(" [%d]: ",j);
		dl_list_print(head);
	}
	
	head->is_sorted=1;
}


void dl_list_quick_sort(dl_head *head){
	_dl_list_quick_sort(head->sentinel.nxt,head->sentinel.prv,0);
	head->is_sorted=1;
}

void _dl_list_quick_sort(dl_node *start ,dl_node* end ,unsigned lvl){
	//Just a node
	if(start == end ){
		return;
	}
	//

	dl_node *i =start , *j =end,*tmp ;
	unsigned a;
	dl_node *before_start =start->prv;
	dl_node *after_end = end->nxt;

	//Printing for entering
	for(a=0 ;a<lvl ;a++){
		printf("== ");
	}
	printf("[%d >] ",lvl);
	dl_list_print_partition(start,end);
	//

	while(1){
		for(;i->key<end->key && i!=j ;i =i->nxt);
		if(i==j){
			break;
		}
		for(;j->key>=end->key && i!=j ;j =j->prv);
		if(i==j){
			break;
		}

		dl_list_node_swap(i,j);
		tmp =i;
		i = j;
		j = tmp;


	}
	//printf("\n-%d- -%d-\n",i->key,end->key);
	dl_list_node_swap(i,end);
	
	//fix pointers after swaping
	i = end;
	start = before_start->nxt;
	end = after_end->prv;
	//

	//If list is larger than 2 nodes print
	if(start->nxt != end){	
		for(a=0 ;a<lvl ;a++){
			printf("== ");
		}
		printf("[%d -] ",lvl);
		dl_list_print_partition(start,end);
	}
	//
	
	if(i != start){
		_dl_list_quick_sort(start,i->prv,lvl+1);
		start = before_start->nxt;
	}
	if(i != end){
		_dl_list_quick_sort(i->nxt,end,lvl+1);
		end = after_end->prv;
	}
	
	//exiting print
	for(a=0 ;a<lvl ;a++){
		printf("== ");
	}
	printf("[%d <] ",lvl);
	dl_list_print_partition(start,end);
	//
	
	return;
}


void dl_list_merge_sort(dl_head *head){
	_dl_list_merge_sort(&head->sentinel,&head->sentinel,0);
	head->is_sorted=1;
}

void _dl_list_merge_sort(dl_node *start_prv ,dl_node *end_nxt ,unsigned lvl){
	unsigned size = dl_list_size_partition(start_prv->nxt,end_nxt->prv);
	unsigned a;

	//Printing for entering
	for(a=0 ;a<lvl ;a++){
		printf("== ");
	}
	printf("[%d >] ",lvl);
	dl_list_print_partition(start_prv->nxt,end_nxt->prv);
	//

	//1 or 2 nodes case
	if(size == 1 || size == 2){
		if(size == 2){
			if(start_prv->nxt->key > end_nxt->prv->key){
				dl_list_node_swap(start_prv->nxt,end_nxt->prv);
			}		
		}

		//Printing exiting
		for(a=0 ;a<lvl ;a++){
			printf("== ");
		}
		printf("[%d <] ",lvl);
		dl_list_print_partition(start_prv->nxt,end_nxt->prv);
		//
		return;
	}
	//
	//Devide
	dl_node *cutnode = dl_node_nxt(start_prv,(size/2)+1);
	_dl_list_merge_sort(start_prv,cutnode,lvl+1);
	cutnode = cutnode->prv;
	_dl_list_merge_sort(cutnode,end_nxt,lvl+1);
	cutnode = cutnode->nxt;
	//

	dl_list_pseudo_insertion_sort(start_prv->nxt,cutnode,end_nxt->prv);

	//Printing exiting
	for(a=0 ;a<lvl ;a++){
		printf("== ");
	}
	printf("[%d <] ",lvl);
	dl_list_print_partition(start_prv->nxt,end_nxt->prv);
	//

}


void dl_list_pseudo_insertion_sort(dl_node *start, dl_node *curr ,dl_node *end){
	dl_node *i,*tmp,*tmp2;
	for(;curr != end->nxt ;curr =curr->nxt){

		for(i=curr->prv ;i->nxt != start ;i =i->prv){
			//printf("-%d- -%d-\n",i->key,curr->key);
			if(i->key<=curr->key){
				tmp2 = end->nxt;
				tmp = curr->nxt;
				_dl_node_detach_byaddress(curr);
				_dl_list_add_after(i,curr);
				curr = tmp->prv;
				end = tmp2->prv;
				break;
			}


		}


		if(i->nxt == start){
			if(start->key > curr->key){
				tmp2 = end->nxt;
				tmp = curr->nxt;
				_dl_node_detach_byaddress(curr);
				_dl_list_add_after(i,curr);
				start = curr;
				curr = tmp->prv;
				end = tmp2->prv;

			}
		}

	}
	return;
}

void dl_list_radix_sort_msd(dl_head *head,const unsigned DIGIT_LENGTH){
	_dl_list_radix_sort_msd(&head->sentinel ,DIGIT_LENGTH,0);
	head->is_sorted=1;
}

void _dl_list_radix_sort_msd(dl_node *sentinel ,const unsigned DIGIT_LENGTH ,unsigned lvl){

	if(8*sizeof(unsigned) <= DIGIT_LENGTH*lvl ){
		return;
	}

	unsigned size = pow(2,DIGIT_LENGTH);
	dl_node alphabet[size];
	unsigned i;

	//init array
	for(i=0 ;i<size ;i++){
		dl_sentinel_init(&alphabet[i]);
	}

	dl_node *curr;
	unsigned digit;

	while(sentinel->nxt != sentinel){
		curr = _dl_node_detach_byaddress(sentinel->nxt);
		digit = extract_digit_msb(curr->key,DIGIT_LENGTH,lvl);
		//printf("%d\n",digit);
		_dl_list_add_after(alphabet[digit].prv,curr);
		
	}

	for(digit=0 ;digit<size ;digit++){
		
		if(dl_list_size_partition(alphabet[digit].nxt ,alphabet[digit].prv) >= 2){		
			//printing
			for(i=0 ;i<lvl+1 ;i++ ,printf("== "));
			printf("[%d, %d] (",lvl+1,digit);
			num2binary_print(digit,DIGIT_LENGTH);
			printf(") ");
			dl_list_print_partition(alphabet[digit].nxt,alphabet[digit].prv);
			//
			_dl_list_radix_sort_msd(&alphabet[digit],DIGIT_LENGTH,lvl+1);
		}
		else if(alphabet[digit].nxt != &alphabet[digit]){
			//printing
			for(i=0 ;i<lvl+1 ;i++ ,printf("== "));
			printf("[%d, %d] (",lvl+1,digit);
			num2binary_print(digit,DIGIT_LENGTH);
			printf(") ");
			dl_list_print_partition(alphabet[digit].nxt,alphabet[digit].prv);
			//
		}

	}

	//Reconstruct list
	for(digit=0 ;digit<size ;digit++){
		while(alphabet[digit].nxt != &alphabet[digit]){
			_dl_list_add_after(sentinel->prv,_dl_node_detach_byaddress(alphabet[digit].nxt));
		}
	}
	//
	return;
}

void dl_list_radix_sort_lsd(dl_head *head,const unsigned DIGIT_LENGTH){

	unsigned size = pow(2,DIGIT_LENGTH);
	dl_node alphabet[size];
	unsigned i;

	//init array
	for(i=0 ;i<size ;i++){
		dl_sentinel_init(&alphabet[i]);
	}

	dl_node *curr;
	unsigned digit,lvl;

	for(lvl=0 ;lvl*DIGIT_LENGTH<8*sizeof(digit) ;lvl++){
	
		while(head->sentinel.nxt != &head->sentinel){
			curr = _dl_node_detach_byaddress(head->sentinel.nxt);
			digit = extract_digit_lsb(curr->key,DIGIT_LENGTH,lvl);
			//printf("%d\n",digit);
			_dl_list_add_after(alphabet[digit].prv,curr);

		}

		//Reconstruct list
		for(digit=0 ;digit<size ;digit++){
			while(alphabet[digit].nxt != &alphabet[digit]){
				_dl_list_add_after(head->sentinel.prv,_dl_node_detach_byaddress(alphabet[digit].nxt));
			}
		}
		//

		//Printing
		printf(" [%u] ",lvl);
		_dl_list_print_lsd(head,DIGIT_LENGTH,lvl);
		//
	}

}



