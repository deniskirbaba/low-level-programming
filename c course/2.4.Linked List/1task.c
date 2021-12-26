#include <stdint.h>
#include <stdlib.h>

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

int main() {
    struct list one_node_list = *node_create(1000);

    return 1;
}