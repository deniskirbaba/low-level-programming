#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

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

int main() {
    struct list* mylist = node_create(1000);
    list_add_front(&mylist, 2000);
    list_add_front(&mylist, 3000);
    printf("%zu", list_length(mylist));

    return 1;
}