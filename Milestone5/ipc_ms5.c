
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Item {
   double price;
   int sku;
   int isTaxed;
   int quantity;
   int minQuantity;
   char name[21];
};

/********************************************************************
Milestones 1 to 4  prototypes, definitions and etc...*/
#define LINEAR 1
#define FORM 0

const double TAX = 0.13;

struct Item itemEntry(int sku);
void clrKyb(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);
void dspItem(const struct Item item,int linear);
int yes(void);
void pause(void);
void clrKyb();


void welcome(void);
void GrocInvSys(void);
int menu(void);
//ms3 prototypes, definitions and etc...
#define STOCK 1
#define CHECKOUT 0
void prnTitle(void);
void listItems(const struct Item item[], int NoOfItems);
void prnFooter(double gTotal);
//ms4 prototypes, definitions and etc...
#define SKU_MAX 999
#define SKU_MIN 100
#define MAX_QTY 999
void search(const struct Item item[], int NoOfRecs);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);
void adjustQty(struct Item item[], int NoOfRecs, int stock);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);

/*End of milestone 1 to 4 stuff
*********************************************************************/



/********************************************************************
Milestone 5 prototypes*/


#define MAX_ITEM_NO 500
#define DATAFILE "items.txt"

void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(struct Item* item, char fileName[], int NoOfRecs);
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr);
void fileCheck(struct Item* item, char fileName[], int noOfRecs);

/*End of milestone 5 prototypes
*********************************************************************/




/**************************************************************************
    TTTTTTTTT   EEEEEEEE   SSSSSSSS   TTTTTTTTTT   EEEEEEEEE   RRRRRRRR
       TT       EE         SS             TT       EE          RR     RR
       TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RRRRRRRR
       TT       EE               SS       TT       EE          RR  RR
       TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RR    RR
***************************************************************************
Tester for saveItem, loadItem, saveItems and loadItems:
uncomment this to test your functions prior to putting all the code together by adding a * and / here:
void prnFile() {
   FILE* tp = fopen("test.txt", "r");
   char ch;
   if (tp) {
      for (; fscanf(tp,"%c", &ch) == 1; putchar(ch));
      fclose(tp);
   }
   else {
      printf("text.txt not found\n");
   }
}
int main(void) {
   int i, n;
   struct Item GI[3] = {
      { 4.4,275,0,10,2,"Royal Gala Apples" },
      { 5.99,386,0,20,4,"Honeydew Melon" },
      { 3.99,240,0,30,5,"Blueberries" },
   };
   struct Item I;
   struct Item IN[3];
   printf("***********Testing saveItem:\n");
   printf("Your saveItem saved the following in test.txt: \n");
   FILE* tp = fopen("test.txt", "w");
   if (tp) {
      for (i = 0; i < 3; i++) saveItem(GI[i], tp);
      fclose(tp);
      prnFile();
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("275,10,2,4.40,0,Royal Gala Apples\n");
   printf("386,20,4,5.99,0,Honeydew Melon\n");
   printf("240,30,5,3.99,0,Blueberries\n");
   printf("***********END Testing saveItem!\n\n\n");
   pause();
   printf("***********Testing loadItem:\n");
   printf("Your loadItem loaded the following from test.txt: \n");
   tp = fopen("test.txt", "r");
   if (tp) {
      for (i = 0; i < 3; i++) {
         loadItem(&I, tp);
         dspItem(I, LINEAR);
      }
      fclose(tp);
      tp = fopen("test.txt", "w");
      fclose(tp);
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
   printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
   printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
   printf("***********END Testing loadItem!\n\n\n");
   pause();
   printf("***********Testing saveItems:\n");
   printf("Your saveItems saved the following in test.txt: \n");
   saveItems(GI, "test.txt", 3);
   prnFile();
   printf("*******************************\nThey have to match the following:\n");
   printf("275,10,2,4.40,0,Royal Gala Apples\n");
   printf("386,20,4,5.99,0,Honeydew Melon\n");
   printf("240,30,5,3.99,0,Blueberries\n");
   printf("***********END Testing saveItems!\n\n\n");
   pause();
   printf("***********Testing loadItems:\n");
   printf("Your loadItems loaded the following from test.txt: \n");
   loadItems(IN, "test.txt", &n);
   for (i = 0; i < n; i++) {
      dspItem(IN[i], LINEAR);
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
   printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
   printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
   printf("***********END Testing loadItems!\n\n\n");
   pause();
   printf("Done!\n");
   return 0;
}
/* End MS5 functions' tester
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/


/********************************************************************
Main function to run the application
uncomment this to test your functions after putting all the code together by adding a * and / here:*/
int main(void) {
GrocInvSys();
return 0;
}
 /*End Main function
********************************************************************/





/********************************************************************
Milestone 5 functions*/
void saveItem(struct Item item, FILE* dataFile){
	fprintf(dataFile,"%d,%d,%d,%.2lf,%d,%s\n", item.sku, item.quantity, item.minQuantity, item.price, item.isTaxed, item.name);
}

int loadItem(struct Item* item, FILE* dataFile){
	if(fscanf(dataFile,"%d,%d,%d,%lf,%d,%[^\n]", &item->sku,&item->quantity,&item->minQuantity,&item->price,&item->isTaxed,item->name) == 6)
		{
		return 1;
		}else{
			return 0;
		}

}

int saveItems(struct Item* item, char fileName[], int NoOfRecs){
	//struct Item sitem;
	int i;
	FILE* fptr;
	fptr = fopen(fileName,"w");
	if(fptr == NULL){
		return 0;
	}else{

		for(i = 0; i < NoOfRecs; i++){
			saveItem(*(item+i),fptr);
		}
		fclose(fptr);
		return 1;
	}
}

int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr){
	FILE* fptr;
	int num = 0;
	fptr = fopen(fileName,"r");

	if(!fptr){
		return 0;
	}else{
		for(;loadItem(item,fptr) != 0;item++){
			num += 1;
		}

		*NoOfRecsPtr = num;
		fclose(fptr);
		return 1;
	}
}
void fileCheck(struct Item* item, char fileName[], int noOfRecs){
	if(saveItems(item, fileName, noOfRecs)==0)
		printf("could not update data file %s\n",DATAFILE);
}

/*End of milestone 5 functions
*********************************************************************/

/********************************************************************
Milestones 1  to 4 functions*/
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

	return itemEntry;
}

void clrKyb(){
	while(getchar() != '\n');
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

void dspItem(struct Item item,int linear){
	char* YNans[4];
	if(item.isTaxed == 1){
		*YNans = "Yes";
	}else{
		*YNans = "No";
		}
	if(linear == 1){

		printf("|%3d|%-20s|%8.2lf|  %3s| %3d | %3d | %11.2lf|", item.sku, item.name, item.price, *YNans,item.quantity, item.minQuantity,item.price*item.quantity);

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
		if(item.quantity <= item.minQuantity){
			printf("WARNING: Quantity low, please order ASAP!!!\n");
		}
	}
}



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

void pause(void) {
	printf("Press <ENTER> to continue...");
	clrKyb();
}
//ms3 functions
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
//END ms3 functions   #####################

// ms2 functions***********************
void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n");
}

void GrocInvSys(void) {
	struct Item gItem[MAX_ITEM_NO];
	int rNum;
	int DONE = 0;
	int SEL;
	welcome();
	printf("\n");
	if(loadItems(gItem, DATAFILE, &rNum) == 0){
		printf("Could not read from %s.\n", DATAFILE);
	}
	while (DONE == 0) {
		SEL = menu();
		switch (SEL)
		{
		case 1:
			printf("List Items!\n");
			listItems(gItem, rNum);
			pause();
			break;

		case 2:
			printf("Search Items!\n");
			search(gItem, rNum);
			pause();
			break;
		case 3:
			printf("Checkout Item!\n");
			adjustQty(gItem, rNum, CHECKOUT);
			fileCheck(gItem, DATAFILE, rNum);
			pause();
			break;
		case 4:
			printf("Stock Item!\n");
			adjustQty(gItem, rNum, STOCK);
			fileCheck(gItem, DATAFILE, rNum);
			pause();
			break;
		case 5:
			printf("Add/Update Item!\n");
			addOrUpdateItem(gItem, &rNum);
			fileCheck(gItem, DATAFILE, rNum);
			pause();
			break;
		case 6:
			printf("Delete Item!\n");
			printf("Not implemented!\n");
			pause();
			break;
		case 7:
			printf("Search by name!\n");
			printf("Not implemented!\n");
			pause();
			break;

		default:
			printf("Exit the program? (Y)es/(N)o : ");
			DONE = yes();
			break;
		}
	}
}

int menu(void) {  // ms2
	int ent;
	int lnum = 0; // lowerlimit
	int unum = 7; // upperlimit
	printf("1- List all items\n");
	printf("2- Search by SKU\n");
	printf("3- Checkout an item\n");
	printf("4- Stock an item\n");
	printf("5- Add new item or update item\n");
	printf("6- delete item\n");
	printf("7- Search by name\n");
	printf("0- Exit program\n");
	printf("> ");
	ent = getIntLimited(lnum, unum);
	return ent;
}
//End ms2 functions###################


//ms4 functions************************
void search(const struct Item item[], int NoOfRecs) {
	int userIn;
	int index;
	printf("Please enter the SKU: ");
	userIn = getIntLimited(SKU_MIN,SKU_MAX);
	if(locateItem(item,NoOfRecs,userIn, &index) == 0)
		printf("Item not found!\n");
	else{
		char* YNans[4];
		if(item[index].isTaxed == 1){
			*YNans = "Yes";
		}else{
			*YNans = "No";
		}
		printf("        SKU: %d\n"
			    "       Name: %s\n"
			    "      Price: %.2lf\n"
				 "   Quantity: %d\n"
			    "Minimum Qty: %d\n"
				 "   Is Taxed: %s\n", item[index].sku, item[index].name, item[index].price, item[index].quantity, item[index].minQuantity, *YNans);

	}

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

void adjustQty(struct Item item[], int NoOfRecs, int stock) {
	int userQut;
	int sku;
	int flag = 0;
	int index;
	int i;
	printf("Please enter the SKU: ");
	sku = getInt();
	for(i = 0; i < NoOfRecs ; i++){
			if(sku == item[i].sku){
				index = i;
				flag = 1;
			}
	}
	if(flag == 0){
		printf("SKU not found in storage!\n");
	}else{
		dspItem(item[index],FORM);
		if(stock == 1){
			printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ","to stock", MAX_QTY-item[index].quantity);
			userQut = getIntLimited(0, MAX_QTY-item[index].quantity);
			if(userQut == 0){
				printf("--== Aborted! ==--\n");
			}else{
				item[index].quantity += userQut;
				printf("--== Stocked! ==--\n");
			}
		}
		else if(stock == 0){
			printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", "to checkout", item[index].quantity);
			userQut = getIntLimited(0, item[index].quantity);
			if(userQut == 0){
				printf("--== Aborted! ==--\n");
			}else{
				item[index].quantity -= userQut;
				printf("--== Checked out! ==--\n");
			}
		}

		if(item[index].quantity <= item[index].minQuantity){
			printf("Quantity is low, please reorder ASAP!!!\n");
		}
	}
}

void addOrUpdateItem(struct Item item[], int* NoOfRecs) {
	int userIn;
	int index;
	printf("Please enter the SKU: ");
	userIn = getIntLimited(SKU_MIN,SKU_MAX);
	if(locateItem(item, *NoOfRecs, userIn, &index)==1){
		dspItem(item[index],FORM);
		printf("Item already exists, Update? (Y)es/(N)o: ");
		if(yes() == 1){
			updateItem(&item[index]);

		}else{
			printf("--== Aborted! ==--\n");
		}
	}else{
		addItem(item, NoOfRecs, userIn);
	}
}
/*End of milestone 1 to 4 functions
*********************************************************************/








/* ms5 Tester output
***********Testing saveItem:
Your saveItem saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItem!
Press <ENTER> to continue...
***********Testing loadItem:
Your loadItem loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItem!
Press <ENTER> to continue...
***********Testing saveItems:
Your saveItems saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItems!
Press <ENTER> to continue...
***********Testing loadItems:
Your loadItems loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItems!
Press <ENTER> to continue...
Done!
*/
