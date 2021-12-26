#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

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

int main() {
    struct list* mylist = NULL;
    list_add_front(&mylist, 2000);
    list_add_front(&mylist, 3000);
    list_add_front(&mylist, 4000);


    return 1;
}