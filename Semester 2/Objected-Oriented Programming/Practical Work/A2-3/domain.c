#include "domain.h"
#include <string.h>


Date create_exp_date(int day, int month, int year)
{
	Date exp_date;
	exp_date.day = day;
	exp_date.month = month;
	exp_date.year = year;
	return exp_date;
}

Product create_product(char name[], char category[], int quantity, Date exp_date)
{
	Product product;
	strcpy(product.name, name);
	strcpy(product.category, category);
	product.quantity = quantity;
	product.exp_date = exp_date;
	return product;
}

char* get_name(Product* p)
{
	return p->name;
}

char* get_category(Product* p)
{
	return p->category;
}

int get_quantity(Product* p)
{
	return p->quantity;
}

Date get_exp_date(Product* p)
{
	return p->exp_date;
}

int same_product(Product p1, Product p2)
{
	if (strcmp(p1.name, p2.name) == 0 && strcmp(p1.category, p2.category) == 0)
		return 1;
	return 0;
}

int identical_products(Product p1, Product p2)
{
	if (strcmp(p1.name, p2.name) == 0 && strcmp(p1.category, p2.category) == 0 && p1.quantity == p2.quantity && p1.exp_date.day == p2.exp_date.day && p1.exp_date.month == p2.exp_date.month && p1.exp_date.year == p2.exp_date.year)
		return 1;
	return 0;
}
