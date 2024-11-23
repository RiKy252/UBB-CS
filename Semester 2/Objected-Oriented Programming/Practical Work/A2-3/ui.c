#include "ui.h"
#include <stdio.h>

void menu()
{
	printf("1. Add\n");
	printf("2. Delete\n");
	printf("3. Update\n"); // a
	printf("4. Display products (by name)\n"); // b
	printf("5. Display products (by expiration date)\n"); // c
	printf("6. Display products (by quantity)\n"); // bonus filtering
	printf("7. Undo\n");
	printf("8. Redo\n"); // d
	printf("0. Exit\n");
}

void read_name(char x[])
{
	printf("Type in the name: ");
	scanf(" %[^\n]", x);
}

void read_category(char x[])
{
	printf("Type in the category: ");
	scanf(" %[^\n]", x);
}

void read_quantity(int* x)
{
	printf("Type in the quantity: ");
	scanf("%d", x);
}

void read_exp_date(Date* x)
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

void to_string(Product x)
{
	printf("Product name: %s, category: %s, quantity: %d, expiration date: %d.%d.%d\n", x.name, x.category, x.quantity, x.exp_date.day, x.exp_date.month, x.exp_date.year);
}

void display_query(DynamicArray* array, char* query, int type_of_sort)
{
	int not_empty = 0;
	if (type_of_sort == 1)
		sort_products_ascending(array);
	else
		sort_products_descending(array);
	if (strcmp(query, "") == 0)
	{
		for (int i = 0; i < array->length; i++)
		{
			to_string(array->elements[i]);
			not_empty = 1;
		}
		if (not_empty == 0)
			printf("The refrigerator is empty!\n");
	}
	else
	{
		for (int i = 0; i < array->length; i++)
			if (strstr(array->elements[i].name, query) != NULL)
			{
				to_string(array->elements[i]);
				not_empty = 1;
			}
		if (not_empty == 0)
			printf("No products found!\n");
	}
}

void display_category_expiration_date_filtering(DynamicArray* array, char category[], int day)
{
	int remaining_days, not_empty = 0;
	int current_day = 19, current_month = 3, current_year = 2024;
	sort_products_ascending(array);
	if (strcmp(category, "") == 0)
	{
		for (int i = 0; i < array->length; i++)
		{
			remaining_days = (array->elements[i].exp_date.year - current_year) * 365 + (array->elements[i].exp_date.month - current_month) * 30 + (array->elements[i].exp_date.day - current_day);
			if (remaining_days <= day)
			{
				to_string(array->elements[i]);
				not_empty = 1;
			}
		}
	}
	else
	{
		for (int i = 0; i < array->length; i++)
		{
			if (strcmp(array->elements[i].category, category) == 0)
			{
				remaining_days = (array->elements[i].exp_date.year - current_year) * 365 + (array->elements[i].exp_date.month - current_month) * 30 + (array->elements[i].exp_date.day - current_day);
				if (remaining_days <= day)
				{
					to_string(array->elements[i]);
					not_empty = 1;
				}
			}
		}
	}
	if (not_empty == 0)
		printf("No products found!\n");
}

void display_category_quantity_filtering(DynamicArray* array, char category[], int quantity)
{
	int not_empty = 0;
	sort_products_ascending(array);
	if (strcmp(category, "") == 0)
	{
		for (int i = 0; i < array->length; i++)
			if (array->elements[i].quantity >= quantity)
			{
				to_string(array->elements[i]);
				not_empty = 1;
			}
	}
	else
	{
		for (int i = 0; i < array->length; i++)
			if (array->elements[i].quantity >= quantity && strcmp(array->elements[i].category, category) == 0)
			{
				to_string(array->elements[i]);
				not_empty = 1;
			}
	}
	if (not_empty == 0)
		printf("No products found!\n");
}
