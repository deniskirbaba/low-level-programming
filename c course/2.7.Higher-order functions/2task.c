/*
struct list {
    int64_t value;
    struct list* next;
};
*/

static int64_t triple(int64_t x) {
    return x * 3;
}

void list_map_mut(struct list* l, int64_t (f)(int64_t)) {
    while (l != NULL) {
        l->value = f(l->value);
        l = l->next;
    }
}

void list_triple(struct list* l) {
    list_map_mut(l, triple);
}