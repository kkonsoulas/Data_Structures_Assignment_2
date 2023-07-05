#ifndef __SORT_H_
#define __SORT_H_

#include "dlist.h"
#include <stdio.h>
#include <math.h>

unsigned extract_digit_msb(unsigned num ,const unsigned DIGIT_LENGTH ,const unsigned LVL);

void num2binary_print(unsigned num, unsigned short digits);

void _dl_list_print_lsd(dl_head *head,const unsigned DIGIT_LENGTH,unsigned lvl);

void dl_list_insertion_sort(dl_head *head);

void dl_list_selection_sort(dl_head *head);

void dl_list_quick_sort(dl_head *head);

void _dl_list_quick_sort(dl_node *start ,dl_node* end ,unsigned lvl);

void dl_list_merge_sort(dl_head *head);

void _dl_list_merge_sort(dl_node *start_prv ,dl_node *end_nxt ,unsigned lvl);

//a required function for merge sort 
void dl_list_pseudo_insertion_sort(dl_node *start, dl_node *curr ,dl_node *end);

void dl_list_radix_sort_msd(dl_head *head,const unsigned DIGIT_LENGTH);

void _dl_list_radix_sort_msd(dl_node *sentinel ,const unsigned DIGIT_LENGTH ,unsigned lvl);

void dl_list_radix_sort_lsd(dl_head *head,const unsigned DIGIT_LENGTH);


#endif
