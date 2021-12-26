#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

enum either_type { ET_INT, ET_STRING };

struct either_int_string {
    enum either_type type;
    union {
        char* as_string;
        int64_t as_int;
    };
};

struct either_int_string either_from_string(char* s) {
    struct either_int_string res = {.type = ET_STRING, .as_string = s};
    return res;
}
struct either_int_string either_from_int(int64_t i) {
    struct either_int_string res = {.type = ET_INT, .as_int = i};
    return res;
}

void either_int_string_destroy(struct either_int_string e) {
    if (e.type == ET_STRING) {
        free(e.as_string);
    }
}

void print(struct either_int_string e) {
    switch (e.type) {
        case ET_INT: {
            printf("Int %" PRId64, e.as_int);
            break;
        }
        case ET_STRING: {
            printf("String %s", e.as_string);
            break;
        }
        default: {
            break;
        }
    }
}

int main() {
    struct either_int_string a = {ET_STRING, "hello"};
    print(a);
    either_from_string("bye");
    print(a);
    either_from_int(10);
    print(a);
    either_int_string_destroy();
    print(a);
}