#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

/* reading funcs */

size_t read_size() {
    size_t sz = 0;
    scanf("%zu", &sz);
    return sz;
}

int64_t read_int64() {
    int64_t res;
    scanf("%" SCNd64, &res);
    return res;
}

/* maybe_int64 */

struct maybe_int64 {
    bool valid;
    int64_t value;
};

struct maybe_int64 some_int64(int64_t i) {
    return (struct maybe_int64) { .value = i, .valid = true };
}

const struct maybe_int64 none_int64 = {0};

void maybe_int64_print(struct maybe_int64 i) {
    if (i.valid) {
        printf("Some %" PRId64, i.value);
    }
    else {
        printf("None");
    }
}

struct maybe_int64 maybe_int64_min(struct maybe_int64 a, struct maybe_int64 b) {
    if (!a.valid && !b.valid) {
        return none_int64;
    }
    if (a.valid && !b.valid) {
        return a;
    }
    if (!a.valid && b.valid) {
        return b;
    }
    else {
        if (a.value >= b.value) {
            return b;
        }
        else {
            return a;
        }
    }
}

/* array_int */

struct array_int {
    int64_t* data;
    size_t size;
};

void array_int_fill( int64_t* array, size_t sz ) {
    for( size_t i = 0; i < sz; i = i + 1 ) {
        array[i] = read_int64();
    }
}

struct array_int array_int_read() {
    const size_t size = read_size();
    if (size > 0) {
        int64_t* array = malloc( sizeof(int64_t) * size);
        array_int_fill( array, size );
        return (struct array_int) { .data = array, .size = size };
    }
    else return (struct array_int) {0};
}

struct maybe_int64 array_int_get(struct array_int a, size_t i) {
    if (i > a.size || a.size == 0 || i < 0) {
        return none_int64;
    }
    else {
        return some_int64(a.data[i]);
    }
}

bool array_int_set( struct array_int a, size_t i, int64_t value ) {
    if (i > a.size || a.size == 0 || i < 0) {
        return false;
    }
    else {
        a.data[i] = value;
        return true;
    }
}

void array_int_print( struct array_int array ) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        printf("%" PRId64 " " , array_int_get( array, i).value);
    }
}

struct maybe_int64 array_int_min( struct array_int array ) {
    int64_t* res = NULL;
    for (size_t i = 0; i < array.size; i = i + 1) {
        if (res == NULL) {
            res = &array.data[i];
        }
        else {
            if (array.data[i] < *res) {
                res = &array.data[i];
            }
        }
    }
    if (res == NULL) {
        return none_int64;
    }
    else {
        return some_int64(*res);
    }
}

void array_int_free(struct array_int* a) {
    if (a->size > 0 ) {
        free(a->data);
        a->size = 0;
    }
}

void array_int_normalize( struct array_int array, int64_t m ) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        array.data[i] = array.data[i] - m;
    }
}

struct array_int array_int_create( size_t sz ) {
    return (struct array_int) { .data = malloc( sizeof( int64_t ) * sz ), .size = sz };
}

/* stack */

struct stack {
    size_t count;
    struct array_int data;
};

size_t stack_count(const struct stack* s) {
    return s->count;
}

struct stack stack_create(size_t size) {
    return (struct stack) {.count = 0, .data = array_int_create(size)};
}

void stack_destroy(struct stack* s) {
    array_int_free(&(s->data));
    s->count = 0;
}

bool stack_is_full(const struct stack* s) {
    return s->count == s->data.size;
}

bool stack_is_empty(const struct stack* s) {
    return s->count == 0;
}

bool stack_push(struct stack* s, int64_t value) {
    if (!stack_is_full(s) && array_int_set(s->data, s->count, value)) {
        s->count = s->count + 1;
        return true;
    }
    else {
        return false;
    }
}

struct maybe_int64 stack_pop(struct stack* s) {
    if (stack_is_empty(s)) {
        return none_int64;
    }
    else {
        s->count = s->count - 1;
        return array_int_get(s->data, s->count);
    }
}

void stack_print( const struct stack* s ) {
    for (size_t i = 0; i < stack_count( s ); i = i + 1 ) {
        printf("%" PRId64, array_int_get( s->data, i).value);
        printf(" ");
    }
}

/* main */

int main() {
    struct stack stack = stack_create(10);
    stack_push(&stack, 100);
    stack_push(&stack, 200);
    stack_push(&stack, 300);
    stack_push(&stack, 400);
    stack_pop(&stack);
    stack_print(&stack);

    return 0;
}