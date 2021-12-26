#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

/* int64_t funcs */

int64_t nothing(int64_t value) {
    return value;
}

int64_t absolute(int64_t value) {
    if (value < 0) {
        return -value;
    }
    else {
        return value;
    }
}

void print_int64_space(int64_t value) {
    printf("%" PRId64 " ", value);
}

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

struct maybe_int64 maybe_read_int64() {
    int64_t res;
    int st = scanf("%" SCNd64, &res);
    if (st == 1) {
        return some_int64(res);
    }
    else {
        return none_int64;
    }
}

/* linked list */

struct list {
    int64_t value;
    struct list* next;
};

struct list* node_create(int64_t value) {
    struct list* res = malloc(sizeof(struct list));
    res->value = value;
    res->next = NULL;
    return res;
}

void list_add_front(struct list** old, int64_t value) {
    struct list* new_front_node = node_create(value);
    new_front_node->next = *old;
    *old = new_front_node;
}

size_t list_length(const struct list* list) {
    size_t length = 0;
    while (list) {
        struct list* next_node = list->next;
        list = next_node;
        length = length + 1;
    }
    return length;
}

void list_delete_last(struct list** list) {
    if ((*list)->next == NULL) {
        free(*list);
        *list = NULL;
    }
    else {
        struct list *penult = *list;
        struct list *last = (*list)->next;
        while (last->next != NULL) {
            penult = last;
            last = last->next;
        }
        free(last);
        penult->next = NULL;
    }
}

void list_destroy(struct list* list) {
    while (list != NULL) {
        list_delete_last(&list);
    }
}

struct list* list_last(struct list* list) {
    struct list* res = NULL;
    while (list != NULL) {
        res = list;
        list = list->next;
    }
    return res;
}

void list_add_back(struct list** old, int64_t value) {
    struct list* new_back_node = node_create(value);
    struct list* penult = list_last(*old);
    if (penult) {
        penult->next = new_back_node;
    }
    else {
        *old = new_back_node;
    }
}

int64_t list_sum(const struct list* list) {
    int64_t res = 0;
    while(list) {
        res = res + list->value;
        list = list->next;
    }
    return res;
}

struct maybe_int64 list_at(const struct list* list, size_t idx) {
    if (idx < 0 || idx >= list_length(list)) {
        return none_int64;
    }
    else {
        for (size_t i = 0; i < idx; i = i + 1) {
            list = list->next;
        }
        return some_int64(list->value);
    }
}

struct list* list_reverse(const struct list* list) {
    struct list* reversed = NULL;
    while (list != NULL) {
        list_add_front(&reversed, list->value);
        list = list->next;
    }
    return reversed;
}

struct list* list_read() {
    struct list* res = NULL;
    struct list* last = NULL;
    struct maybe_int64 value = maybe_read_int64();
    while (value.valid) {
        if (res == NULL) {
            res = node_create(value.value);
        }
        else {
            if (last == NULL) {
                last = node_create(value.value);
                res->next = last;
            }
            else {
                last->next = node_create(value.value);
                last = last->next;
            }
        }
        value = maybe_read_int64();
    }
    return res;
}

struct list* list_map(const struct list* l, int64_t (f) (int64_t))  {
    struct list* res = NULL;
    struct list* cur = NULL;
    while (l != NULL) {
        struct list* new_node = node_create(f(l->value));
        if (res == NULL) {
            res = new_node;
        }
        else {
            cur->next = new_node;
        }
        cur = new_node;
        l = l->next;
    }
    return res;
}

void list_foreach(const struct list* l, void (f)(int64_t)) {
    while (l != NULL) {
        f(l->value);
        l = l->next;
    }
}

void list_print(const struct list* l) {
    list_foreach(l, print_int64_space);
}

struct list* list_copy(const struct list* l) {
    return list_map(l, nothing);
}

struct list* list_abs(const struct list* l) {
    return list_map(l, absolute);
}

/* main */

int main() {
    struct list* mylist = list_read();
    list_print(list_abs(mylist));

    return 0;
}