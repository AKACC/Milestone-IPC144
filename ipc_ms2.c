#include <stdio.h>
void clrKyb(void);
void pause(void);
int getInt(void);
int yes(void);  // ms2
int getIntLimited(int lowerLimit, int upperLimit);
void welcome(void);
void GrocInvSys(void);  // ms2
int menu(void);  // ms2


int main(void) {
	GrocInvSys();
	return 0;
}



// implmement MS2 fucntions here
int yes(void) {  // ms2
	char CH;
	int RET = 0;
	//char accEnt[4] = ("Y", "y", "N", "n");
	do {
		scanf("%c", &CH);
		clrKyb();
		if (CH != 'Y' && CH != 'y' && CH != 'N' && CH != 'n') {
			printf("Only (Y)es or (N)o are acceptable: ");
		}
	} while (CH != 'Y' && CH != 'y' && CH != 'N' && CH != 'n');
	if (CH == 'Y' || CH == 'y') {
		RET = 1;
	}
	

	return RET;
}

void GrocInvSys(void) {  // ms2
	int DONE = 0;
	int SEL;
	welcome();
	printf("\n");

	while (DONE == 0) {
		SEL = menu();
		switch (SEL)
		{
		case 1:
			printf("List Items!\n");
			pause();
			break;
			
		case 2:
			printf("Search Items!\n");
			pause();
			break;
		case 3:
			printf("Checkout Item!\n");
			pause();
			break;
		case 4:
			printf("Stock Item!\n");
			pause();
			break;
		case 5:
			printf("Add/Update Item!\n");
			pause();
			break;
		case 6:
			printf("Delete Item!\n");
			pause();
			break;
		case 7:
			printf("Search by name!\n");
			pause();
			break;

		default:
			printf("Exit the program? (Y)es/(N)o): ");
			DONE = yes();
			break;
		}
		//pause();
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



// copy MS1 functions here
void clrKyb(void) {
	char ch;
	do {
		scanf("%c", &ch);
	} while (ch != '\n');
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
int getIntLimited(int lowerLimit, int upperLimit) {
	int Value;
	//Value = getInt();
	do {
		Value = getInt();
		if (lowerLimit > Value || upperLimit < Value) {
			printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
			//Value = getInt();
		}
	} while (lowerLimit > Value || upperLimit < Value);
	return Value;
}
void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n\n");
}



/*
---=== Grocery Inventory System ===---

1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 8
Invalid value, 0 < value < 7: 1
List Items!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 2
Search Items!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 3
Checkout Item!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 4
Stock Item!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 5
Add/Update Item!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 6
Delete Item!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 7
Search by name!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 0
Exit the program? (Y)es/(N)o : x
Only (Y)es or (N)o are acceptable: n
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 0
Exit the program? (Y)es/(N)o : y
*/