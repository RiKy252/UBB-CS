// Intelligent Refrigerator
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>

// Domain

struct Date {
	int day;
	int month;
	int year;
};

struct Product {
	char name[101];
	char category[101]; // dairy, sweets, meat, fruit
	int quantity;
	struct Date exp_date;
};


// Repo

void add_product(struct Product** list, int* length, char* name, char* category, int quantity, struct Date exp_date)
{
	*list = realloc(*list, (*length + 1) * sizeof(struct Product));
	if (*list == NULL) {
		printf("Memory allocation failed!\n");
		return;
	}
	strcpy((*list)[*length].name, name);
	strcpy((*list)[*length].category, category);
	(*list)[*length].quantity = quantity;
	(*list)[*length].exp_date = exp_date;
	(*length) += 1;
}

void remove_product(struct Product** list, int* length, int index)
{
	// This part belongs to service
	(*length)--;
	if (*length < 0 || index == -1)
		return;
	if (*length == 0)
		*list = NULL;
	else
	{
		(*list)[index] = (*list)[*length];
		*list = realloc(*list, (*length) * sizeof(struct Product));
	}
}

void update_product(struct Product* list, int index, int quantity, struct Date exp_date)
{
	list[index].quantity = quantity;
	list[index].exp_date = exp_date;
}

// Service

int verify_valid_category(char user_category[])
{
	if (!(strcmp(user_category, "dairy") == 0 || strcmp(user_category, "sweets") == 0 || strcmp(user_category, "meat") == 0 || strcmp(user_category, "fruit") == 0))
		return 0;
	return 1;
}

int verify_valid_quantity(int user_quantity)
{
	if (user_quantity <= 0)
		return 0;
	return 1;
}

int verify_valid_exp_date(struct Date user_exp_date)
{
	if (user_exp_date.day < 0 || user_exp_date.day > 31)
		return -1;
	else if (user_exp_date.month < 0 || user_exp_date.month > 12)
		return -2;
	else if (user_exp_date.year < 2024)
		return -3;
	return 1;
}

int product_exists(struct Product* list, int length, char* name, char* category)
{
	for (int i = 0; i < length; i++)
		if (strcmp(list[i].name, name) == 0 && strcmp(list[i].category, category) == 0)
			return i;
	return -1;
}

void sort_products_ascending(struct Product* list, int length)
{
	for (int i = 0; i < length; i++)
		for (int j = i + 1; j < length; j++)
			if (list[i].quantity > list[j].quantity)
			{
				struct Product aux = list[i];
				list[i] = list[j];
				list[j] = aux;
			}
}

// to do: input validations

// UI

void menu()
{
	printf("1. Add\n");
	printf("2. Delete\n");
	printf("3. Update\n");
	printf("4. Display (search query)\n");
	printf("0. Exit\n");
}

void read_name(char* x)
{
	printf("Type in the name: ");
	scanf("%s", x);
}

void read_category(char* x)
{
	printf("Type in the category: ");
	scanf("%s", x);
}

void read_quantity(int* x)
{
	printf("Type in the quantity: ");
	scanf("%d", x);
}

void read_exp_date(struct Date* x)
{
	int data;
	printf("Enter the day of the expiration date: ");
	scanf("%d", &data);
	x->day = data;
	printf("Enter the month of the expiration date: ");
	scanf("%d", &data);
	x->month = data;
	printf("Enter the year of the expiration data: ");
	scanf("%d", &data);
	x->year = data;
}

void to_string(struct Product x)
{
	printf("Product name: %s, category: %s, quantity: %d, expiration date: %d.%d.%d\n", x.name, x.category, x.quantity, x.exp_date.day, x.exp_date.month, x.exp_date.year);
}

void display_query_ascending(struct Product* list, int length, char* query)
{
	int not_empty = 0;
	sort_products_ascending(list, length);
	if (strcmp(query, "all") == 0)
	{
		for (int i = 0; i < length; i++)
			to_string(list[i]);
		if (not_empty == 0)
			printf("The refrigerator is empty!\n");
	}
	else
	{
		for (int i = 0; i < length; i++)
			if (strstr(list[i].name, query) != NULL)
			{
				to_string(list[i]);
				not_empty = 1;
			}
		if (not_empty == 0)
			printf("The refrigerator is empty!\n");
	}
}

int main()
{
	struct Product* list = NULL;
	int length = 0;
	char user_name[101];
	char user_category[101];
	int user_quantity;
	struct Date user_exp_date;
	char query[101];
	int index;
	while (1)
	{
		menu();
		int user_option;
		printf(">> ");
		if (scanf("%d", &user_option) != 0)
			if (user_option == 1) // add
			{
				read_name(user_name);
				read_category(user_category);
				if (verify_valid_category(user_category) == 0)
					printf("Invalid category! (dairy, sweets, meat, fruit -> valid)\n");
				else
				{
					read_quantity(&user_quantity);
					if (verify_valid_quantity(user_quantity) == 0)
						printf("Please enter a non-zero positive quantity!\n");
					else
					{
						read_exp_date(&user_exp_date);
						if (verify_valid_exp_date(user_exp_date) == -1)
							printf("Please enter a valid day!\n");
						else if (verify_valid_exp_date(user_exp_date) == -2)
							printf("Please enter a valid month!\n");
						else if (verify_valid_exp_date(user_exp_date) == -3)
							printf("Please enter a valid year!\n");
						else
						{
							index = product_exists(list, length, user_name, user_category);
							if (index == -1)
								add_product(&list, &length, user_name, user_category, user_quantity, user_exp_date);
							else
							{
								list[index].quantity += user_quantity;
								printf("Product already exists, quantity added!\n");
							}
						}
					}
				}
			}
			else if (user_option == 2) // remove 
			{
				read_name(user_name);
				read_category(user_category);
				index = product_exists(list, length, user_name, user_category);
				if (index == -1)
					printf("Product doesn't exist!\n");
				else
					remove_product(&list, &length, index);
			}
			else if (user_option == 3) // update 
			{
				read_name(user_name);
				read_category(user_category);
				if (verify_valid_category(user_category) == 0)
					printf("Invalid category! (dairy, sweets, meat, fruit -> valid)\n");
				else
				{
					index = product_exists(list, length, user_name, user_category);
					if (index == -1)
						printf("Product doesn't exist!\n");
					else {
						read_quantity(&user_quantity);
						if (verify_valid_quantity(user_quantity) == 0)
							printf("Please enter a non-zero positive quantity!\n");
						else
						{
							read_exp_date(&user_exp_date);
							if (verify_valid_exp_date(user_exp_date) == -1)
								printf("Please enter a valid day!\n");
							else if (verify_valid_exp_date(user_exp_date) == -2)
								printf("Please enter a valid month!\n");
							else if (verify_valid_exp_date(user_exp_date) == -3)
								printf("Please enter a valid year!\n");
							update_product(list, index, user_quantity, user_exp_date);
						}
					}
				}
			}
			else if (user_option == 4) // display with search query
			{
				printf("Enter the search query: ");
				scanf("%s", query);
				display_query_ascending(list, length, query);
			}
			else if (user_option == 0) // exit
				break;
			else
				printf("Invalid menu option!\n");
		else
		{
			printf("Next time insert a number!\n");
			break;
		}
	}
		free(list);
		_CrtDumpMemoryLeaks();
		return 0;
	}
