#include "service.h"
#include "domain.h"
#include <stdio.h>

void add_product(DynamicArray* array, Product p)
{
	if (array == NULL)
		return;
	if (array->elements == NULL)
		return;
	if (array->length == array->capacity)
		resize(array);
	array->elements[array->length] = p;
	array->length++;
}

void remove_product(DynamicArray* array, Product p)
{
	if (array == NULL)
		return;
	if (array->elements == NULL)
		return;
	for (int i = 0; i < array->length; i++)
		if (same_product(array->elements[i], p))
		{
			array->elements[i] = array->elements[array->length - 1];
			array->length--;
			break;
		}	
}

void update_product(DynamicArray* array, Product p, Product new_p)
{
	if (array == NULL)
		return;
	if (array->elements == NULL)
		return;
	for (int i = 0; i < array->length; i++)
		if (same_product(array->elements[i], p))
			array->elements[i] = new_p;
}

void sort_products_ascending(DynamicArray* array)
{
	for (int i = 0; i < array->length; i++)
		for (int j = i + 1; j < array->length; j++)
			if (array->elements[i].quantity > array->elements[j].quantity)
			{
				Product aux = array->elements[i];
				array->elements[i] = array->elements[j];
				array->elements[j] = aux;
			}
}

void sort_products_descending(DynamicArray* array)
{
	for (int i = 0; i < array->length; i++)
		for (int j = i + 1; j < array->length; j++)
			if (array->elements[i].quantity < array->elements[j].quantity)
			{
				Product aux = array->elements[i];
				array->elements[i] = array->elements[j];
				array->elements[j] = aux;
			}
}

int product_exists(DynamicArray* array, Product p)
{
	for (int i = 0; i < array->length; i++)
		if (same_product(array->elements[i], p))
			return i;
	return -1;
}

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

int verify_valid_exp_date(Date user_exp_date)
{
	if (user_exp_date.day < 1 || user_exp_date.day > 31)
		return -1;
	else if (user_exp_date.month < 1 || user_exp_date.month > 12)
		return -2;
	else if (user_exp_date.year < 2024)
		return -3;
	return 1;
}
