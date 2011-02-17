#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lunchbox.h"
#include "textutil.h"

void exit_success();
void test_initialize_vendor();
void test_read_950();
void test_add_del_vendor();
typedef void(*testfunction)();
int main()
{
	char *menu[]={"Exit program",\
			"Create vendor",\
			"Read and write string in cp950",\
			"Add vendors to list and delete vendors",
			""};
	testfunction test[]={exit_success,\
			test_initialize_vendor,\
			test_read_950,
			test_add_del_vendor};
	int choice, i=0;
	printf("Test function for lunchbox.\n" 
		"Please choose the function you want to test.\n");
	for(;;){
		for(;;){
			if(!strcmp(menu[i], ""))
				break;
			printf("%2d. %s\n", i, menu[i]);
			i++;
		}
		scanf("%d", &choice);
		test[choice]();
		i=0;
	}
	return 0;
}

void test_initialize_vendor()
{
	int input;
	char test_name[50];
	char test_phone[50];
	char category_str[50];

	printf("Please enter the name of the vendor:\n");
	readline(test_name);
	printf("Please enter the phone number of the vendor:\n");
	readline(test_phone);
	printf("Meal or drink? 1 for meal, 2 for drink\n");
	scanf("%d", &input);
	struct vendor *test_vendor=initialize_vendor(input-1, \
			test_name, test_phone);
	switch(test_vendor->category){
		case LUNCHBOX: strcpy(category_str, "Lunchbox"); 
			       break; /* LUNCHBOX=0 */
		case BEVERAGE: strcpy(category_str, "Drink");
			       break; /* BEVERAGE=1 */
	}
		printf("Number:  %d,  Name:  %-10s,  Phone:  %-10s\n",
			test_vendor->vendor_serial,\
			test_vendor->vendor_name,\
			test_vendor->phone);
	free(test_vendor);
}

/*
 * test read_950_to_utf and read_utf_to_950 in textutil.c.
 * failed to give correct result in previous version(20110202), 
 * so it need to be completely rewritten.
 */
void test_read_950()
{
	char input[STRMAX];
	char medium[STRMAX];
	char output[STRMAX];
	char *test="茅屋餵秋風所破歌";
	char testoutput[STRMAX], testfoutput[STRMAX];
	FILE *fp=fopen("test.txt", "w");

	printf("Insert arbitrary string:\n");
	readline(input);
	read_950_to_utf(input, medium);
	fprintf(fp, "%s \n", medium);
	read_utf_to_950(medium, output);
	printf("output:%s\n", output);

	read_utf_to_950(test, testoutput);
	printf("output:%s\n", testoutput);
	read_950_to_utf(testoutput, testfoutput);
	fprintf(fp, "%s \n", testfoutput);

	fclose(fp);
}


void exit_success()
{
	exit(EXIT_SUCCESS);
}

void test_add_del_vendor()
{
	char test_name[STRMAX], test_phone[STRMAX], ch, option;
	int input=(-1), i=0, choice=0;
	struct vendor *first, *p, *q;

for(;;){
	printf("Test function for adding and deleting vendors.\n");
	printf("Please enter a function. a for add, d for delete\n");
	scanf(" %c", &ch);
	switch(ch){
	case 'a':	
		for(;;){
			printf("Please enter the name of the vendor:\n");
			readline(test_name);
			printf("Please enter the phone number of the vendor:\n");
			readline(test_phone);
			if (input==(-1)){ 
			/* 
			 * If first vendor do not exist,
			 * we should initialize it first
			 */
			printf("Meal or drink? 1 for meal, 2 for drink\n");
			scanf("%d", &input);
			first=initialize_vendor(input-1,
					test_name, test_phone);
			}
			else{
				add_vendor(first, test_name, test_phone);
			}
			for(p=first;p!=NULL;p=p->next){
			printf("Number:  %d,  Name:  % 15s,  " 
					"Phone:  % 15s\n",
				p->vendor_serial,
				p->vendor_name,\
				p->phone);
			}
			printf("Continue? y/n ");
			scanf(" %c", &option);
			if (option=='n'){
				break;
			}
		}
		break;
	case 'd':
		for(;;){
		printf("Please enter the member you want to delete.\n");
		scanf("%d", &choice);
		first=del_vendor(first, choice);
		for(p=first;p!=NULL;p=p->next){
			printf("Number:  %d,  Name:  % 15s,  " 
					"Phone:  % 15s\n",
				p->vendor_serial,
				p->vendor_name,\
				p->phone);
		}
		printf("Continue? y/n ");
		scanf(" %c", &option);
		if (option=='n'){
			for(p=first, q=NULL; p!=NULL; 
					p=p->next,q=p){
				free(q);
			}
			break;
		}
		}
		break;
	case 'q':		
		for(p=first, q=NULL; p!=NULL; 
			p=p->next,q=p){
			free(q);
		}
		return;
	}
}
}	
