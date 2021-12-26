#include <stdlib.h>
#include <inttypes.h>

enum move_dir {MD_UP, MD_RIGHT, MD_DOWN, MD_LEFT, MD_NONE};

/* callbacks and robot structures */

struct callback {
    void (*handler)(enum move_dir dir);
    struct callback* next;
};

struct robot {
    const char* name;
    struct callback* callbacks;
};

typedef void (*move_callback)(enum move_dir);

/* callbacks funcs */

struct callback* callback_node_create(move_callback value) {
    struct callback* res = malloc(sizeof(struct callback));
    res->handler = value;
    res->next = NULL;
    return res;
}

struct callback* callback_last(struct callback* callback) {
    struct callback* res = NULL;
    while (callback != NULL) {
        res = callback;
        callback = callback->next;
    }
    return res;
}

void callback_add_back(struct callback** old, move_callback value) {
    struct callback* new_back_node = callback_node_create(value);
    struct callback* penult = callback_last(*old);
    if (penult) {
        penult->next = new_back_node;
    }
    else {
        *old = new_back_node;
    }
}

void callback_delete_last(struct callback** callback) {
    if ((*callback)->next == NULL) {
        free(*callback);
        *callback = NULL;
    }
    else {
        struct callback *penult = *callback;
        struct callback *last = (*callback)->next;
        while (last->next != NULL) {
            penult = last;
            last = last->next;
        }
        free(last);
        penult->next = NULL;
    }
}

void callback_destroy(struct callback* callback) {
    while (callback != NULL) {
        callback_delete_last(&callback);
    }
}

void register_callback(struct robot* robot, move_callback new_cb) {
    callback_add_back(&(robot->callbacks), new_cb);
}

void unregister_all_callbacks(struct robot* robot) {
    callback_destroy(robot->callbacks);
}

void move(struct robot* robot, enum move_dir dir) {
    struct callback* curmove = robot->callbacks;
    while (curmove != NULL) {
        curmove->handler(dir);
        curmove = curmove->next;
    }
}