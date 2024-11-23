#pragma once
typedef struct
{
	int day;
	int month;
	int year;
}Date;

typedef struct
{
	char name[101];
	char category[101]; // dairy, sweets, meat, fruit
	int quantity;
	Date exp_date;
}Product;

Date create_exp_date(int day, int month, int year);
/*
This function takes as inputs: day, month and year as integers and transforms them into a Data struct type
returns the Data type
param: day -> the day of the date
param: month -> the month of the date
param: year -> the year of the date
*/
Product create_product(char name[], char category[], int quantity, Date exp_date);
/*
This function takes as inputs: two string of characters representing the name of the product, and the category of the
product respectively, an integer representing the quantity of the product and a Date type representing the expiration date
of the product, the function creates the product
return the product as a Product data type
param: name[] -> the name of the product to be created
param: category[] -> the category of the product to be created
param: quantity -> the quantity of the product
param: exp_date -> the expiration date of the product
*/
char* get_name(Product* p);
/*
This is a getter function, gets the name of the product given as a parameter and returns it
*/
char* get_category(Product* p);
/*
This is a getter function, gets the category of the product given as a parameter and returns it
*/
int get_quantity(Product* p);
/*
This is a getter function, gets the quantity of the product given as a parameter and returns it
*/
Date get_exp_date(Product* p);
/*
This is a getter function, gets the expiration date of the product given as a parameter and returns it
*/
int same_product(Product p1, Product p2);
/*
This function verifies if two given products are the same (meaning they have the same name and category)
returns 1 if they are the same, 0 otherwise
param: p1 -> first product
param: p2 -> second product
*/
int identical_products(Product p1, Product p2);
/*
This function verifies if two given products are identical (having all attributes identical)
returns 1 if they are identical, 0 otherwise
param: p1 -> first product
param: p2 -> second product
*/
