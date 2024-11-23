#pragma once
#include "service.h"

void menu();
void read_name(char x[]);
void read_category(char x[]);
void read_quantity(int* x);
void read_exp_date(Date* x);
void to_string(Product x);
void display_query(DynamicArray* array, char* query, int sort_type);
void display_category_quantity_filtering(DynamicArray* array, char category[], int quantity);
void display_category_expiration_date_filtering(DynamicArray* array, char category[], int day);
