/*/*
== Item System ==

Author	: Zixian Ou
Date	: Nov 9th 2016
Student Number: 125421164
Matrix Account: zou2
Seneca Email: zou2@myseneca.ca
Workshop: #3 Milestone

*/


#include <stdio.h>
#include <stdlib.h>
// define statements go here
#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0


/* ms1 prototypes*/
void welcome(void);
void prnTitle(void);
void prnFooter(double gTotal);
void pause(void);
void clrKyb(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);
/* ipc_ms2 prototype*/
int yes(void);  // ms2

struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};


/* ms3 prototypes*/

double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
struct Item itemEntry(int sku);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);

/* Constant double TAX value */
const double TAX = 0.13;



int main() {
	struct Item I[21] = {
		{ 4.4,275,0,10,2,"Royal Gala Apples" },
		{ 5.99,386,0,20,4,"Honeydew Melon" },
		{ 3.99,240,0,30,5,"Blueberries" },
		{ 10.56,916,0,20,3,"Seedless Grapes" },
		{ 2.5,385,0,5,2,"Pomegranate" },
		{ 0.44,495,0,100,30,"Banana" },
		{ 0.5,316,0,123,10,"Kiwifruit" },
		{ 4.49,355,1,20,5,"Chicken Alfredo" },
		{ 5.49,846,1,3,5,"Veal Parmigiana" },
		{ 5.29,359,1,40,5,"Beffsteak Pie" },
		{ 4.79,127,1,30,3,"Curry Checken" },
		{ 16.99,238,1,10,2,"Tide Detergent" },
		{ 10.49,324,1,40,5,"Tide Liq. Pods" },
		{ 10.99,491,1,50,5,"Tide Powder Det." },
		{ 3.69,538,1,1,5,"Lays Chips S&V" },
		{ 3.29,649,1,15,5,"Joe Org Chips" },
		{ 1.79,731,1,100,10,"Allen's Apple Juice" },
		{ 6.69,984,1,30,3,"Coke 12 Pack" },
		{ 7.29,350,1,50,5,"Nestea 12 Pack" },
		{ 6.49,835,1,20,2,"7up 12 pack" }
	};
	double val;
	int ival;
	int searchIndex;
	val = totalAfterTax(I[0]);
	printf("totalAfterTax: yours=%lf, program's=44.000000\n", val);
	val = totalAfterTax(I[7]);
	printf("totalAfterTax: yours=%lf, program's=101.474000\n", val);
	ival = isLowQty(I[0]);
	printf("isLowQty: yours=%d, program's=0\n", ival);
	ival = isLowQty(I[14]);
	printf("isLowQty: yours=%d, program's=1\n", ival);
	pause();
	printf("itemEntry, enter the following values:\n");
	printf("        SKU: 999\n"
		"       Name: Red Apples\n"
		"      Price: 4.54\n"
		"   Quantity: 50\n"
		"Minimum Qty: 5\n"
		"   Is Taxed: n\n");
	printf("Enter the values:\n");
	I[20] = itemEntry(999);
	printf("dspItem, Linear:\nYours: ");
	dspItem(I[20], LINEAR);
	printf(" Prog: |999|Red Apples          |    4.54|   No|  50 |   5 |      227.00|\n");
	printf("dspItem, Form:\nYours:\n");
	dspItem(I[20], FORM);
	printf("Programs: \n");
	printf("        SKU: 999\n"
		"       Name: Red Apples\n"
		"      Price: 4.54\n"
		"   Quantity: 50\n"
		"Minimum Qty: 5\n"
		"   Is Taxed: No\n");
	I[20].quantity = 2;
	I[20].isTaxed = 1;
	pause();
	printf("dspItem, Linear with low value and taxed:\nYours: ");
	dspItem(I[20], LINEAR);
	printf(" Prog: |999|Red Apples          |    4.54|  Yes|   2 |   5 |       10.26|***\n");
	printf("dspItem, Form with low value:\nYours:\n");
	dspItem(I[20], FORM);
	printf("Programs: \n");
	printf("        SKU: 999\n"
		"       Name: Red Apples\n"
		"      Price: 4.54\n"
		"   Quantity: 2\n"
		"Minimum Qty: 5\n"
		"   Is Taxed: Yes\n"
		"WARNING: Quantity low, please order ASAP!!!\n");
	pause();
	printf("Listing Items: \n");
	listItems(I, 21);
	pause();
	printf("Locate Item, successful search:\n");
	printf("program: Found the item 999 at index: 20\n");
	printf("  Yours: ");
	if (locateItem(I, 21, 999, &searchIndex)) {
		printf("Found the item 999 at index: %d\n", searchIndex);
	}
	else {
		printf("No item with the sku 999 is in the array!\n");
	}

	printf("Locae Item, unsuccessful search:\n");
	printf("Progam: No item with the sku 732 is in the array!\n");
	printf(" Yours: ");
	if (locateItem(I, 21, 732, &searchIndex)) {
		printf("Found the item at index: %d\n", searchIndex);
	}
	else {
		printf("No item with the sku 732 is in the array!\n");
	}
	return 0;
}





/* ms3 functions*/


double totalAfterTax(struct Item item) {
	double total;
	if(item.isTaxed == 1){
		total = item.price * item.quantity * (1 + TAX);
	}else{
		total = item.price * item.quantity;
	}
	return total;
}

int isLowQty(struct Item item) {
	int result;
	if(item.quantity < item.minQuantity ){
		result = 1;
	}
	else {
		result = 0;
	}
	return result;
}

struct Item itemEntry(int sku) {
	struct Item itemEntry;
	itemEntry.sku = sku;
	printf("        SKU: %d\n", sku);
	printf("       Name: ");
	scanf("%20[^\n]", itemEntry.name);
	clrKyb();
	printf("      Price: ");
	itemEntry.price = getDbl();
	printf("   Quantity: ");
	itemEntry.quantity = getInt();;
	printf("Minimum Qty: ");
	itemEntry.minQuantity = getInt();
	printf("   Is Taxed: ");
	itemEntry.isTaxed = yes();
	//scanf("%d", &itemEntry.isTaxed);

	return itemEntry;
}

void dspItem(struct Item item,int linear){
	char* YNans[4];
	double Total;
	if(item.isTaxed == 1){
		*YNans = "Yes";
		Total = item.price*item.quantity*(1 + TAX);
	}else{
		*YNans = "No";
		Total = item.price*item.quantity;
		}
	if(linear == 1){

		printf("|%3d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|", item.sku, item.name, item.price, *YNans,item.quantity, item.minQuantity, Total);

		if(item.quantity < item.minQuantity){
			printf("***\n");
		}else{
			printf("\n");
		}
	}else{
		printf("        SKU: %d\n"
				"       Name: %s\n"
				"      Price: %.2lf\n"
				"   Quantity: %d\n"
				"Minimum Qty: %d\n"
				"   Is Taxed: %s\n", item.sku, item.name, item.price, item.quantity, item.minQuantity, *YNans);
		if(item.quantity < item.minQuantity){
			printf("WARNING: Quantity low, please order ASAP!!!\n");
		}
	}
}


void listItems(const struct Item item[], int NoOfItems){
	int i;
	double Total = 0;
	double gTotal = 0;

	prnTitle();
	for(i = 0; i < NoOfItems ; i++){
		char* YNans[4];
			if(item[i].isTaxed == 1){
				*YNans = "Yes";
				Total = item[i].price*item[i].quantity*(1 + TAX);
			}else{
				*YNans = "No";
				Total = item[i].price*item[i].quantity;
			}
		gTotal += Total;

		printf("%-4d|%3d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|", i+1,item[i].sku, item[i].name, item[i].price, *YNans, item[i].quantity, item[i].minQuantity, Total);
		if(item[i].quantity < item[i].minQuantity){
					printf("***\n");
				}else{
					printf("\n");
				}
	}
	prnFooter(gTotal);
}

int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index){
	int i;
	int flag = 0;
	for(i = 0; i < NoOfRecs ; i++){
		if(sku == item[i].sku){
			*index = i;
			flag = 1;
		}
	}

	return flag;
}

/*   item entry output
SKU: 999
Name: Red Apples
Price: 4.54
Quantity: 50
Minimum Qty: 5
Is Taxed: n

SKU: 999
Name: Red Apples
Price: 4.54
Quantity: 50
Minimum Qty: 5
Is Taxed: No
WARNING: Quantity low, please order ASAP!!!


*/

/*  dspItems
|999|Red Apples          |    4.54|   No|  50 |   5 |      227.00|

SKU: 999
Name: Red Apples
Price: 4.54
Quantity: 50
Minimum qty: 5
Is Taxed: No

*/


/*ms1 and 2 functions: */
/* ms1 functions */
//void clrKyb(void) {
//	char ch;
//	do {
//		scanf("%c", &ch);
//	} while (ch != '\n');
//}
void clrKyb(){
	//char ch;
	while(getchar() != '\n');
}
void welcome(void){
   printf("---=== Grocery Inventory System ===---\n\n");
}
void prnTitle(void){
   printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
   printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
}
void prnFooter(double gTotal){
   printf("--------------------------------------------------------+----------------\n");
   if(gTotal > 0){
      printf("                                           Grand Total: |%12.2lf\n", gTotal);
	}
}
void pause(void) {
	printf("Press <ENTER> to continue...");
	clrKyb();
}
int getInt(void) {
	int value;
	char NL = 'x';
	while (NL != '\n') {
		scanf("%d%c", &value, &NL);
		if (NL != '\n') {
			clrKyb();
			printf("Invalid integer, please try again: ");
		}
	}
	return value;
}

double getDbl(void){
   double value;
   char NL = 'x';
   while(NL != '\n'){
      scanf("%lf%c", &value, &NL);
      if(NL != '\n'){
         clrKyb();
         printf("Invalid number, please try again: ");
      }
   }
   return value;
}

int getIntLimited(int lowerLimit, int upperLimit){
	int Value;
	do{
		Value = getInt();
		if(lowerLimit > Value || upperLimit < Value ){
			printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
			}
	}while(lowerLimit > Value || upperLimit < Value );
	return Value;
}
double getDblLimited(double lowerLimit, double upperLimit){
	double Value;
	do{
		Value = getDbl();
			if(lowerLimit > Value || upperLimit < Value ){
			printf("Invalid value, %lf< value < %lf: ", lowerLimit, upperLimit);
			}
	}while(lowerLimit > Value || upperLimit < Value );

	return Value;
}


/* ms2 functions */

int yes(void) {  // ms2
	char CH;
	int RET = 0;
	do {
		scanf("%c", &CH);// to discard all whitespace.
		clrKyb();

		if (CH != 'Y' && CH != 'y' && CH != 'N' && CH != 'n') {
			printf("Only (Y)es or (N)o are acceptable: ");
		}
	}while (CH != 'Y' && CH != 'y' && CH != 'N' && CH != 'n');
	if (CH == 'Y' || CH == 'y') {
		RET = 1;
	}

	return RET;
}
