#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lunchbox.h"

struct vendor *initialize_vendor(int leading_category, \
		char name[], char phone[])
{
	struct vendor *initial=malloc(sizeof(struct vendor));
	register int i;

	if (initial==NULL){
		printf("Error: failed to initialize first vendor");
		exit(1);
	}
	if ((leading_category!=LUNCHBOX)&&(leading_category!=BEVERAGE)){
		printf("Error: invalid category");
		exit(1);
	}	
	initial->category=leading_category;
	if (strlen(name)>NAME_LEN){
		for(i=0;i<NAME_LEN;i++){
			initial->vendor_name[i]=name[i];
		}
	}
	else{
		strcpy(initial->vendor_name, name);
	}
	if(strlen(phone)>PHONE_LEN){
		for(i=0;i<PHONE_LEN;i++){
			initial->phone[i]=phone[i];
		}
	}
	else{
		strcpy(initial->phone, phone);
	}
	initial->vendor_serial=1;
	initial->first_item=NULL;
	initial->next=NULL;
	return initial;
}


/*
 * add_vendor
 * Access the last vendor of the linked list, and 
 * add a vendor there.
 */
struct vendor *add_vendor(struct vendor *first, 
		char name[], char phone[])
{
	struct vendor *new_vendor=initialize_vendor(
			first->category, name, phone);
	struct vendor *last;
	for(last=first;last->next!=NULL;last=last->next)
		;
	new_vendor->vendor_serial=last->vendor_serial+1;
	last->next=new_vendor;
	return new_vendor;
}
/* done	
struct vendor *initialize_vendor(int leading_category, 
		char name[], char phone[]);
struct vendor *add_vendor(struct vendor *first, 
		char name[], char phone[]);
*/
struct vendor *del_vendor(struct vendor *first, int n)
{
	/* Need to return something since the list modified.*/
	struct vendor *prev, *cur, *coming, *p;
	register int i=1;
	/* When we want to delete the first member: */
	if (n==1){
		
		p=first;
		printf("p=first\n");
		first=first->next; /* The new first vendor */
		free(p);  
		for(coming=first;coming!=NULL;coming=coming->next){
		coming->vendor_serial=coming->vendor_serial-1;
		}
		return first;
	}
	/* First locate previous node */
	for(cur=first, prev=NULL;
		i<n;
		prev=cur, cur=cur->next, i++)
		;	
	/* 
	 * Link previous node to coming node, 
	 * and free current node.
	 */
	prev->next=cur->next;
	free(cur);

	/* All serial numbers later than current should minus 1 */
	
	for(coming=prev->next;coming!=NULL;coming=coming->next){
		coming->vendor_serial=coming->vendor_serial-1;
	}
	return first;	
}

struct vendor *access_vendor(struct vendor *first, int n)
{
	struct vendor *p;
	for(p=first; (p!=NULL)&&(p->vendor_serial!=n); p=p->next)
		;
	if(p==NULL){
		printf("Can't access vendor, returning first vendor\n");
		return first;
	}
	else
		return p;
}
/*
struct menu_item{
	int item_serial;
	char item_name[NAME_LEN];
	char vendor[NAME_LEN];
	int item_price;
	struct menu_item *next;
};

struct vendor{
	int vendor_serial;	
	char vendor_name[NAME_LEN];
	char phone[PHONE_LEN];
	enum category_type category;
	struct menu_item *first_item;
	struct vendor *next;
};
*/
struct menu_item *initialize_item(struct vendor *v,
		char name[], int price)
{
/*
	struct menu_item *current=malloc(sizeof(struct menu_item));
	current->vendor_serial=1;
	*/

}
struct menu_item *add_item(struct vendor *v,
		char name[], int price)
{
	;
}
struct menu_item *del_item(struct vendor *v, int n)
{
	;
}
struct menu_item *access_item(struct vendor *v, int n)
{
	;
}
/* To do
struct menu_item *initialize_item(struct vendor *v,
		char name[], int price);

struct menu_item *add_item(struct vendor *v,
		char name[], int price);
void del_item(struct vendor *v, int n);
struct menu_item *access_item(struct vendor *v, int n);
*/


