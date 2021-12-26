/*
struct list {
    int64_t value;
    struct list* next;
};
*/

void print_int64(int64_t i);

void list_foreach(const struct list* l, void (f)(int64_t)) {
    while (l != NULL) {
        f(l->value);
        l = l->next;
    }
}

void list_print(const struct list* l) {
    list_foreach(l, print_int64_space);
}