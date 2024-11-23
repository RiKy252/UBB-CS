#include "dynamicarray.h"
#include <stdio.h>
#include <stdlib.h>

DynamicArray* create_dynamic_array(int capacity)
{
	DynamicArray* da = malloc(sizeof(DynamicArray));
	if (da == NULL)
		return NULL;
	da->capacity = capacity;
	da->length = 0;
	da->elements = malloc(capacity * sizeof(TElement));
	if (da->elements == NULL)
		return NULL;
	return da;
}

void destroy(DynamicArray* array)
{
	if (array == NULL)
		return;
	free(array->elements);
	array->elements = NULL;
	free(array);
}

void resize(DynamicArray* array)
{
	if (array == NULL)
		return;
	array->capacity *= 2;
	TElement* aux = realloc(array->elements, array->capacity * sizeof(TElement));
	if (aux == NULL)
		return;
	array->elements = aux;
}

int get_length(DynamicArray* array)
{
	if (array == NULL)
		return 0;
	return array->length;
}

int get_capacity(DynamicArray* array)
{
	if (array == NULL)
		return 0;
	return array->capacity;
}
