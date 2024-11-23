#include "ui.h"
#include "undoredo.h"
#include "tests.h"
#include <stdio.h>
#include <crtdbg.h>
#include <string.h>

void starting_entries(DynamicArray* array)
{
	/*
	This function creates 10 starting entries for the Intelligent Refrigerator and stores them into an array
	param: array -> the dynamic array pointer where to store these entries
	no return value
	*/
	Date exp_date;
	Product products[10];
	exp_date = create_exp_date(19, 3, 2024);
	products[0] = create_product("Apple", "fruit", 5, exp_date);
	exp_date.day += 2;
	products[1] = create_product("Yogurt", "dairy", 10, exp_date);
	exp_date.day += 2;
	products[2] = create_product("Cheese", "dairy", 7, exp_date);
	exp_date.day += 4;
	products[3] = create_product("Beef", "meat", 3, exp_date);
	exp_date.day = 7;
	exp_date.month += 1;
	products[4] = create_product("Chocolate", "sweets", 25, exp_date);
	exp_date.day += 2;
	products[5] = create_product("Candy", "sweets", 30, exp_date);
	exp_date.day += 3;
	products[6] = create_product("Banana", "fruit", 12, exp_date);
	exp_date.day += 4;
	products[7] = create_product("Orange", "fruit", 24, exp_date);
	exp_date.day += 2;
	products[8] = create_product("Chicken", "meat", 4, exp_date);
	products[9] = create_product("Milk", "dairy", 8, exp_date);
	for (int i = 0; i < 10; i++)
		add_product(array, products[i]);
}

int main() // Starting the program
{
	all_tests();
	DynamicArray* array = create_dynamic_array(2);
	State* undo_stack = create_state();
	State* redo_stack = create_state();
	Product temp_product;
	char user_name[101], user_category[101], search_query[101], category_query[101];
	int user_quantity, index;
	Date user_exp_date, temp_date = create_exp_date(1, 1, 2024);
	starting_entries(array);
	while (1)
	{
		menu();
		int user_option, sorting_option;
		printf(">> ");
		if (scanf("%d", &user_option) != 0)
		{
			fseek(stdin, 0, SEEK_END);
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
							temp_product = create_product(user_name, user_category, user_quantity, user_exp_date);
							index = product_exists(array, temp_product);
							add_state(array, undo_stack);
							if (index == -1)
							{
								add_product(array, temp_product);
								printf("Product added successfully!\n");
							}
							else
							{
								array->elements[index].quantity += user_quantity;
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
				temp_product = create_product(user_name, user_category, 1, temp_date);
				index = product_exists(array, temp_product);
				if (index == -1)
					printf("Product doesn't exist!\n");
				else
				{
					add_state(array, undo_stack);
					remove_product(array, temp_product);
				}
			}
			else if (user_option == 3) // update 
			{
				read_name(user_name);
				read_category(user_category);
				if (verify_valid_category(user_category) == 0)
					printf("Invalid category! (dairy, sweets, meat, fruit -> valid)\n");
				else
				{
					temp_product = create_product(user_name, user_category, 1, temp_date);
					index = product_exists(array, temp_product);
					if (index == -1)
						printf("Product doesn't exist!\n");
					else
					{
						read_name(user_name);
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
								add_state(array, undo_stack);
								temp_product = create_product(user_name, user_category, user_quantity, user_exp_date);
								update_product(array, array->elements[index], temp_product);
								printf("Product updated successfully!\n");
							}
						}
					}
				}
			}
			else if (user_option == 4) // display with search query
			{
				printf("Enter the search query: ");
				gets(search_query);
				printf("1. Ascending sorting\n");
				printf("2. Descending sorting\n");
				scanf("%d", &sorting_option);
				display_query(array, search_query, sorting_option);
			}
			else if (user_option == 5) // display products, category, exp_date filter
			{
				printf("Type in the category of the products: ");
				gets(category_query);
				if (verify_valid_category(category_query) == 1 || strcmp(category_query, "") == 0)
				{
					int amount_of_days;
					printf("Enter the amount of days before a filtered product expires: ");
					scanf("%d", &amount_of_days);
					display_category_expiration_date_filtering(array, category_query, amount_of_days);
				}
				else
					printf("Invalid category! (dairy, sweets, meat, fruit -> valid)\n");
			}
			else if (user_option == 6) // display products, category, quantity filter
			{
				printf("Type in the category of the products: ");
				gets(category_query);
				if (verify_valid_category(category_query) == 1 || strcmp(category_query, "") == 0)
				{
					int quantity;
					printf("The minimum quantity for the filtered products: ");
					scanf("%d", &quantity);
					display_category_quantity_filtering(array, category_query, quantity);
				}
				else
					printf("Invalid category! (dairy, sweets, meat, fruit -> valid)\n");
			}
			else if (user_option == 7) // undo
			{
				if (undo_stack->index == 0)
					printf("Cannot undo!\n");
				else
				{
					add_state(array, redo_stack);
					remove_state(array, undo_stack);
					printf("Successful undo!\n");
				}
			}
			else if (user_option == 8) // redo
			{
				if (redo_stack->index == 0)
					printf("Cannot redo!\n");
				else
				{
					add_state(array, undo_stack);
					remove_state(array, redo_stack);
					printf("Successful redo!\n");
				}
			}
			else if (user_option == 0) // exit
				break;
			else
				printf("Invalid menu option!\n");
		}
		else
		{
			printf("Next time insert a number!\n");
			break;
		}
	}
	destroy(array);
	destroy_state(undo_stack);
	destroy_state(redo_stack);
	_CrtDumpMemoryLeaks();
	return 0;
}
