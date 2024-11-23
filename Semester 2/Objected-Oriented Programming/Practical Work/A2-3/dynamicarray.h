#pragma once
#include "domain.h"

typedef Product TElement;

typedef struct
{
	TElement* elements;
	int length;
	int capacity;
}DynamicArray;

DynamicArray* create_dynamic_array(int capacity);
/*
This function creates a dynamic array
param: capacity -> the initial capacity of the dynamical allocated array
returns the dynamic array as a DynamicArray* type (pointer) or stops if at some point it couldn't allocate memory
*/
void destroy(DynamicArray* array);
/*
This function destroys a dynamic array, freeing all dynamically allocated memory in the heap
param: array -> the array which will be destroyed
stops if the array is NULL
*/
void resize(DynamicArray* array);
/*
This function resizes a dynamic array, multiplying the capacity with 2
param: array -> the array to be resized
stops if the array is NULL or couldn't allocate memory for the elements after increasing capacity
*/
int get_length(DynamicArray* array);
/*
This function is a getter, returns as a integer the length of a dynamic array
param: array -> the dynamic array to get the length for
returns the length of the array if it is not NULL, 0 otherwise
*/
int get_capacity(DynamicArray* array);
/*
This function is a getter, returns as a integer the capacity of a dynamic array
param: array -> the dynamic array to get the capacity for
returns the capacity of the array if it is not NULL, 0 otherwise
*/
