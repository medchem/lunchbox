#define NAME_LEN 30
#define PHONE_LEN 15

enum category_type{
	LUNCHBOX, BEVERAGE
};

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

struct vendor *initialize_vendor(int leading_category, 
		char name[], char phone[]);
/* add_vendor returns the new vendor */
struct vendor *add_vendor(struct vendor *first, 
		char name[], char phone[]);
/* del_vendor returns the first vendor */
struct vendor *del_vendor(struct vendor *first, int n);
struct vendor *access_vendor(struct vendor *first, int n);

struct menu_item *initialize_item(struct vendor *v,
		char name[], int price);
struct menu_item *add_item(struct vendor *v,
		char name[], int price);
struct menu_item *del_item(struct vendor *v, int n);
struct menu_item *access_item(struct vendor *v, int n);

void list_vendor(struct vendor *first);
void list_item(struct vendor *v); 


