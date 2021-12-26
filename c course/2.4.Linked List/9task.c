#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

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

int main() {
    struct list* mylist = NULL;
    list_add_front(&mylist, 2000);
    list_add_front(&mylist, 3000);
    list_add_front(&mylist, 4000);


    return 1;
}