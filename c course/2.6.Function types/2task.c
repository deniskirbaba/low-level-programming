#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

/* Only heap strings in struct */
typedef struct {char* addr;} string_heap;

typedef uint64_t uid;
#define PRI_uid PRIu64
#define SCN_uid SCNu64

enum city {C_SARATOV, C_MOSCOW, C_PARIS, C_LOS_ANGELES, C_OTHER};

const char* city_string[] = {
        [C_SARATOV] = "Saratov",
        [C_MOSCOW] = "Moscow",
        [C_PARIS] = "Paris",
        [C_LOS_ANGELES] = "Los Angeles",
        [C_OTHER] = "Other"
};

struct user {
    const uid id;
    const string_heap name;
    enum city city;
};

/* Ascending sort by uid */

int uid_comparer(const struct user* x, const struct user* y) {
    if (x->id > y->id) return 1;
    if (x->id < y->id) return -1;
    return 0;
}

int uid_void_comparer(const void* x, const void* y) {
    return uid_comparer(x, y);
}

void users_sort_uid(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), uid_void_comparer);
}

/* Sort by name */

int string_comparer(const struct user* x, const struct user* y) {
    return strcmp(x->name.addr, y->name.addr);
}

int string_void_comparer(const void* x, const void* y) {
    return string_comparer(x, y);
}

void users_sort_name(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), string_void_comparer);
}

/* Sort by city name */

int city_comparer(const struct user* x, const struct user* y) {
    return strcmp(city_string[x->city], city_string[y->city]);
}

int city_void_comparer(const void* x, const void* y) {
    return city_comparer(x, y);
}

void users_sort_city(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), city_void_comparer);
}

void print_uid(struct user users[], size_t sz) {
    for (size_t i = 0; i < sz; i = i + 1) {
        printf("%" PRI_uid "\n", users[i].id);
    }
}

void print_names(struct user users[], size_t sz) {
    for (size_t i = 0; i < sz; i = i + 1) {
        printf(users[i].name.addr);
        printf("\n");
    }
}

void print_cities(struct user users[], size_t sz) {
    for (size_t i = 0; i < sz; i = i + 1) {
        printf(city_string[users[i].city]);
        printf("\n");
    }
}

int main() {
    struct user a = {5, "qwewr", C_LOS_ANGELES};
    struct user b = {58, "asg", C_MOSCOW};
    struct user c = {1, "asoijg", C_SARATOV};
    struct user d = {6523, "aaa", C_PARIS};
    struct user ae = {56, "bdkfapo", C_PARIS};

    struct user users[] = {a, b, c, d, ae};

    users_sort_city(users,5);

    print_cities(users, 5);

    return 0;
}