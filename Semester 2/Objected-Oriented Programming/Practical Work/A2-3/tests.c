#include "tests.h"
#include <assert.h>
#include <string.h>

void test_create_state()
{
    State* state = create_state();
    assert(state != NULL);
    assert(state->matrix != NULL);
    for (int i = 0; i < 100; i++)
        assert(state->matrix[i] != NULL);
    assert(state->index == 0);
    destroy_state(state);
}

void test_add_state()
{
    DynamicArray* arr = create_dynamic_array(4);
    Product p = create_product("test", "fruit", 10, create_exp_date(1, 1, 2024));
    add_product(arr, p);
    State* state = create_state();
    add_state(arr, state);
    assert(state->matrix[0]->length == 1);
    assert(identical_products(state->matrix[0]->elements[0], arr->elements[0]));
    assert(state->index == 1);
    destroy(arr);
    destroy_state(state);
}

void test_remove_state()
{
    DynamicArray* arr = create_dynamic_array(4);
    Product p = create_product("test", "fruit", 10, create_exp_date(1, 1, 2024));
    add_product(arr, p);
    State* state = create_state();
    add_state(arr, state);
    remove_state(arr, state);
    assert(state->index == 0);
    assert(arr->length == state->matrix[0]->length);
    assert(identical_products(state->matrix[0]->elements[0], arr->elements[0]));
    destroy(arr);
    destroy_state(state);
}

void test_undo_redo()
{
    test_create_state();
    test_remove_state();
    test_add_state();
}

// ------------------------

void test_create_exp_date()
{
    Date date;
    date = create_exp_date(1, 5, 2024);
    assert(date.day == 1);
    assert(date.month == 5);
    assert(date.year == 2024);
}

void test_create_product()
{
    Date date;
    date = create_exp_date(25, 5, 2026);
    Product p;
    p = create_product("test", "meat", 101, date);
    assert(strcmp(p.name, "test") == 0);
    assert(strcmp(p.category, "meat") == 0);
    assert(p.quantity == 101);
    assert(p.exp_date.day == date.day && p.exp_date.month == date.month && p.exp_date.year == date.year);
}

void test_get_name()
{
    Date date;
    date = create_exp_date(1, 1, 2024);
    Product p = create_product("Banana", "fruit", 99, date);
    assert(strcmp(get_name(&p), "Banana") == 0);
}

void test_get_category()
{
    Date date;
    date = create_exp_date(1, 1, 2024);
    Product p = create_product("Banana", "fruit", 99, date);
    assert(strcmp(get_category(&p), "fruit") == 0);
}

void test_get_quantity()
{
    Date date;
    date = create_exp_date(1, 1, 2024);
    Product p = create_product("Banana", "fruit", 99, date);
    assert(p.quantity == 99);
}

void test_get_exp_date()
{
    Date date;
    date = create_exp_date(1, 1, 2024);
    Product p = create_product("Banana", "fruit", 99, date);
    assert(get_exp_date(&p).day == date.day);
    assert(get_exp_date(&p).month == date.month);
    assert(get_exp_date(&p).year == date.year);
}

void test_same_product()
{
    Product p1, p2, p3;
    Date date = create_exp_date(19, 8, 2028);
    p1 = create_product("Pineapple", "fruit", 1023, date);
    p2 = create_product("Pineapple", "fruit", 923, date);
    p3 = create_product("Apple", "meat", 23, date);
    assert(same_product(p1, p2) == 1);
    assert(same_product(p1, p3) == 0);
}

void test_identical_products()
{
    Product p1, p2, p3;
    Date date = create_exp_date(19, 8, 2028);
    p1 = create_product("Pineapple", "fruit", 1023, date);
    p2 = create_product("Pineapple", "fruit", 1023, date);
    p3 = create_product("Apple", "meat", 23, date);
    assert(identical_products(p1, p2) == 1);
    assert(identical_products(p1, p3) == 0);
}

void test_domain()
{
    test_create_product();
    test_create_exp_date();
    test_get_name();
    test_get_category();
    test_get_quantity();
    test_get_exp_date();
    test_same_product();
    test_identical_products();
}

// ------------------------

void test_create_dynamic_array()
{
    DynamicArray* arr = create_dynamic_array(2);
    assert(arr != NULL);
    assert(arr->capacity == 2);
    assert(arr->length == 0);
    assert(arr->elements != NULL);
    destroy(arr);
}

void test_resize()
{
    DynamicArray* arr = create_dynamic_array(2);
    resize(arr);
    assert(arr->capacity == 4);
    assert(arr->elements != NULL);
    destroy(arr);
}

void test_get_length()
{
    DynamicArray* arr = create_dynamic_array(2);
    Product p1, p2, p3;
    Date date = create_exp_date(1, 1, 2024);
    p1 = create_product("Pineapple", "fruit", 1023, date);
    p2 = create_product("Pineapple", "fruit", 1023, date);
    p3 = create_product("Apple", "meat", 23, date);
    add_product(arr, p1);
    add_product(arr, p2);
    add_product(arr, p3);
    assert(get_length(arr) == 3);
    destroy(arr);
}

void test_get_capacity()
{
    DynamicArray* arr = create_dynamic_array(2);
    Product p1, p2, p3;
    Date date = create_exp_date(1, 1, 2024);
    p1 = create_product("Pineapple", "fruit", 1023, date);
    p2 = create_product("Pineapple", "fruit", 1023, date);
    p3 = create_product("Apple", "meat", 23, date);
    add_product(arr, p1);
    add_product(arr, p2);
    add_product(arr, p3);
    assert(get_capacity(arr) == 4);
    destroy(arr);
}

void test_dynamic_array()
{
    test_create_dynamic_array();
    test_resize();
    test_get_length();
    test_get_capacity();
}

// ------------------------

void test_add_product()
{
    DynamicArray* arr = create_dynamic_array(2);
    Date date = create_exp_date(7, 7, 2026);
    Product p = create_product("new", "dairy", 50, date);
    add_product(arr, p);
    assert(identical_products(arr->elements[0], p) == 1);
    assert(arr->length == 1);
    destroy(arr);
}

void test_remove_product()
{
    DynamicArray* arr = create_dynamic_array(2);
    Date date = create_exp_date(7, 7, 2026);
    Product p1 = create_product("new", "dairy", 50, date);
    Product p2 = create_product("another", "dairy", 75, date);
    add_product(arr, p1);
    add_product(arr, p2);
    remove_product(arr, p1);
    assert(identical_products(arr->elements[0], p2) == 1);
    assert(arr->length == 1);
    destroy(arr);
}

void test_update_product()
{
    DynamicArray* arr = create_dynamic_array(2);
    Date date = create_exp_date(7, 7, 2026);
    Date new_date = create_exp_date(9, 10, 2030);
    Product p = create_product("new", "dairy", 50, date);
    Product new_p = create_product("more new", "dairy", 73, new_date);
    add_product(arr, p);
    update_product(arr, p, new_p);
    assert(arr->length == 1);
    assert(identical_products(arr->elements[0], new_p) == 1);
    destroy(arr);
}

void test_sort_products_ascending()
{
    Product p1, p2, p3, p4;
    DynamicArray* arr = create_dynamic_array(2);
    Date exp_date = create_exp_date(19, 3, 2024);
    p1 = create_product("Apple", "fruit", 5, exp_date);
    p2 = create_product("Chocolate", "sweets", 25, exp_date);
    p3 = create_product("Yogurt", "dairy", 10, exp_date);
    p4 = create_product("Banana", "fruit", 12, exp_date);
    add_product(arr, p1);
    add_product(arr, p2);
    add_product(arr, p3);
    add_product(arr, p4);
    sort_products_ascending(arr);
    assert(identical_products(arr->elements[0], p1) == 1);
    assert(identical_products(arr->elements[1], p3) == 1);
    assert(identical_products(arr->elements[2], p4) == 1);
    assert(identical_products(arr->elements[3], p2) == 1);
    assert(arr->length == 4);
    destroy(arr);
}

void test_sort_products_descending()
{
    Product p1, p2, p3, p4;
    DynamicArray* arr = create_dynamic_array(2);
    Date exp_date = create_exp_date(19, 3, 2024);
    p1 = create_product("Apple", "fruit", 5, exp_date);
    p2 = create_product("Chocolate", "sweets", 25, exp_date);
    p3 = create_product("Yogurt", "dairy", 10, exp_date);
    p4 = create_product("Banana", "fruit", 12, exp_date);
    add_product(arr, p1);
    add_product(arr, p2);
    add_product(arr, p3);
    add_product(arr, p4);
    sort_products_descending(arr);
    assert(identical_products(arr->elements[0], p2) == 1);
    assert(identical_products(arr->elements[1], p4) == 1);
    assert(identical_products(arr->elements[2], p3) == 1);
    assert(identical_products(arr->elements[3], p1) == 1);
    assert(arr->length == 4);
    destroy(arr);
}

void test_product_exists()
{
    Product p1, p2, p3;
    DynamicArray* arr = create_dynamic_array(2);
    Date exp_date = create_exp_date(19, 3, 2024);
    p1 = create_product("Apple", "fruit", 5, exp_date);
    p2 = create_product("Chocolate", "sweets", 25, exp_date);
    p3 = create_product("Yogurt", "dairy", 10, exp_date);
    add_product(arr, p1);
    add_product(arr, p2);
    assert(product_exists(arr, p1) == 0);
    assert(product_exists(arr, p2) == 1);
    assert(product_exists(arr, p3) == -1);
    destroy(arr);
}

void test_verify_valid_category()
{
    char c1[51], c2[51];
    strcpy(c1, "dairy");
    strcpy(c2, "other");
    assert(verify_valid_category(c1) == 1);
    assert(verify_valid_category(c2) == 0);
}

void test_verify_valid_quantity()
{
    int q1, q2, q3;
    q1 = 5;
    q2 = -3;
    q3 = 0;
    assert(verify_valid_quantity(q1) == 1);
    assert(verify_valid_quantity(q2) == 0);
    assert(verify_valid_quantity(q3) == 0);
}

void test_verify_valid_exp_date()
{
    Date date1, date2, date3, date4;
    date1 = create_exp_date(7, 9, 2027);
    date2 = create_exp_date(33, 6, 2025);
    date3 = create_exp_date(28, 14, 2024);
    date4 = create_exp_date(18, 12, 2022);
    assert(verify_valid_exp_date(date1) == 1);
    assert(verify_valid_exp_date(date2) == -1);
    assert(verify_valid_exp_date(date3) == -2);
    assert(verify_valid_exp_date(date4) == -3);
}

void test_service()
{
    test_add_product();
    test_remove_product();
    test_update_product();
    test_sort_products_ascending();
    test_sort_products_descending();
    test_product_exists();
    test_verify_valid_category();
    test_verify_valid_quantity();
    test_verify_valid_exp_date();
}

void all_tests()
{
    test_undo_redo();
    test_domain();
    test_dynamic_array();
    test_service();
}