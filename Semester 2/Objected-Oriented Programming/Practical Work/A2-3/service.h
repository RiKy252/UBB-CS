#pragma once
#include "dynamicarray.h"

void add_product(DynamicArray* array, Product p);
/*
This function adds a product into a dynamic array
param: array -> the dynamic array where the product will be stored
param: p -> the product to be stored
stops if array is not allocated, resizes the array if necessary
*/
void remove_product(DynamicArray* array, Product p);
/*
This function removes a product from a dynamic array
param: array -> the dynamic array where we remove the product from
param: p -> the program which will be removed
stops if array is not allocated, if product doesn't exist it doesn't do anything
*/
void update_product(DynamicArray* array, Product p, Product new_p);
/*
This function updates a product from a dynamic array
param: array -> the dynamic array where we update the product
param: p -> the product to be updated
param: new_p -> the new product which will take place of the old product
stops if array is not allocated, if product doesn't exist it doesn't do anything
*/
void sort_products_ascending(DynamicArray* array);
/*
This function sorts the products of the dynamic array given as a parameter in ascending order by quantity
*/
void sort_products_descending(DynamicArray* array);
/*
This function sorts the products of the dynamic array given as a parameter in descending order by quantity
*/
int product_exists(DynamicArray* array, Product p);
/*
This function verifies if a product exists in a dynamic array
param: array -> the dynamic array where we search for the product
param: p -> the product we're searching
returns the index of the product in the array if it exists, -1 otherwise
*/
int verify_valid_category(char user_category[]);
/*
This function verifies if a category is valid or not
param: user_category[] -> the string we are verifying
returns 1 if the category is valid (one of: dairy, sweets, fruit, meat), 0 otherwise
*/
int verify_valid_quantity(int user_quantity);
/*
This function verifies if a quantity is valid or not
param: user_quantity -> the integer quantity we are verifying
returns 1 if the quantity is valid (strictly positive integer), 0 otherwise
*/
int verify_valid_exp_date(Date user_exp_date);
/*
This function verifies if an expiration date is valid or not
param: user_exp_date -> the Date we are verifying
returns 1 if the expiration date is valid (day: 1-31, month: 1-12, year: 2024+)
returns -1 if the day is not valid
returns -2 if the month is not valid
returns -3 if the year is not valid
*/
