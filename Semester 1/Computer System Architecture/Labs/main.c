#include <stdio.h>

int even_numbers(char even[]);

int main()
{
    char odd_numbers[101];
    char even[101];
    even_numbers(even);
    printf("Even numbers: %s", even)
}