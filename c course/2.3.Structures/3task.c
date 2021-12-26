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

struct maybe_int64 array_int_get( struct array_int a, size_t i ) {
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

void array_int_free( struct array_int a ) {
    if ( a.size > 0 ) {
        free(a.data);
        a.size = 0;
    }
}

void array_int_normalize( struct array_int array, int64_t m ) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        array.data[i] = array.data[i] - m;
    }
}

/* maybe_array_int */

struct maybe_array_int {
    struct array_int value;
    bool valid;
};

struct maybe_array_int some_array_int(struct array_int array) {
    return (struct maybe_array_int) { array, true };
}

const struct maybe_array_int none_array_int = { {NULL, 0}, false };

/* array_array_int */

struct array_array_int {
    struct array_int* data;
    size_t size;
};

struct maybe_array_int array_array_int_get_row( struct array_array_int a, size_t i ) {
    if ( 0 <= i && i < a.size ) { return some_array_int( a.data[i] ); }
    else { return none_array_int; }
}

bool array_array_int_set_row(struct array_array_int a, size_t i, struct array_int value) {
    if (0 <= i && i < a.size) {
        a.data[i] = value;
        return true;
    }
    else { return false; }
}

struct maybe_int64 array_array_int_get(struct array_array_int a, size_t i, size_t j) {
    struct maybe_array_int row = array_array_int_get_row(a, i);
    if (row.valid) {
        struct maybe_int64 res = array_int_get(row.value, j);
        if (res.valid) {
            return res;
        }
    }
    return none_int64;
}

bool array_array_int_set(struct array_array_int a, size_t i, size_t j, int64_t value) {
    struct maybe_array_int row = array_array_int_get_row(a, i);
    if (row.valid && array_int_set(row.value, j, value) && array_array_int_set_row(a, i, row.value)) {
        return true;
    }
    else {
        return false;
    }
}

struct array_array_int array_array_int_read() {
    size_t rows = read_size();
    struct array_int* array = malloc(sizeof(struct array_int) * rows);
    for (size_t i = 0; i < rows; i = i + 1) {
        array[i] = array_int_read();
    }
    return (struct array_array_int) {.data = array, .size = rows};
}

void array_array_int_print(struct array_array_int array) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        array_int_print(array.data[i]);
        printf("\n");
    }
}

struct maybe_int64 array_array_int_min(struct array_array_int array) {
    struct maybe_int64 res = {0, false};
    for (size_t i = 0; i < array.size; i = i + 1) {
        res = maybe_int64_min(res, array_int_min(array.data[i]));
    }
    return res;
}

void array_array_int_normalize( struct array_array_int array, int64_t m) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        const struct maybe_array_int cur_row = array_array_int_get_row( array, i );
        if (cur_row.valid) {
            array_int_normalize( cur_row.value, m );
        }
    }
}

void array_array_int_free( struct array_array_int array ) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        array_int_free(array.data[i]);
    }
    free(array.data);
}

/* main */

int main() {
    struct array_array_int array = array_array_int_read();
    struct maybe_int64 m = array_array_int_min(array);
    if (m.valid) {
        array_array_int_normalize(array, m.value);
        array_array_int_print(array);
    }
    array_array_int_free(array);

    return 0;
}