#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#define STACK_CAPACITY 10

/* int64_t funcs */

void print_int64(int64_t value) {
    printf("%" PRId64, value);
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

/* array_int */

struct array_int {
    int64_t* data;
    size_t size;
};

struct array_int array_int_create( size_t sz ) {
    return (struct array_int) {.data = malloc( sizeof( int64_t ) * sz ), .size = sz};
}

void array_int_free(struct array_int* a) {
    if (a->size > 0 ) {
        free(a->data);
        a->size = 0;
    }
}

struct maybe_int64 array_int_get(struct array_int a, size_t i) {
    if (i > a.size || a.size == 0 || i < 0) {
        return none_int64;
    }
    else {
        return some_int64(a.data[i]);
    }
}

bool array_int_set( struct array_int a, size_t i, int64_t value ) {
    if (i > a.size || a.size == 0 || i < 0) {
        return false;
    }
    else {
        a.data[i] = value;
        return true;
    }
}

/* stack */

struct stack {
    size_t count;
    struct array_int data;
};

struct stack stack_create(size_t size) {
    return (struct stack) {.count = 0, .data = array_int_create(size)};
}

void stack_destroy(struct stack* s) {
    array_int_free(&(s->data));
    s->count = 0;
}

bool stack_is_full(const struct stack* s) {
    return s->count == s->data.size;
}

bool stack_is_empty(const struct stack* s) {
    return s->count == 0;
}

bool stack_push(struct stack* s, int64_t value) {
    if (!stack_is_full(s) && array_int_set(s->data, s->count, value)) {
        s->count = s->count + 1;
        return true;
    }
    else {
        return false;
    }
}

struct maybe_int64 stack_pop(struct stack* s) {
    if (stack_is_empty(s)) {
        return none_int64;
    }
    else {
        s->count = s->count - 1;
        return array_int_get(s->data, s->count);
    }
}

/* funcs */

enum opcode {BC_PUSH, BC_IPRINT, BC_IREAD, BC_IADD, BC_STOP};

struct bc_noarg {
    enum opcode opcode;
};

struct bc_arg64 {
    enum opcode opcode;
    int64_t arg;
};

union ins {
    enum opcode opcode;
    struct bc_arg64 as_arg64;
    struct bc_noarg as_noarg;
};

/* vm_state */

struct vm_state {
    const union ins *ip;
    struct stack data_stack;
};

struct vm_state state_create(const union ins *ip) {
    return (struct vm_state){.ip = ip,
            .data_stack = stack_create(STACK_CAPACITY)};
}

void state_destroy(struct vm_state *state) {
    state->ip = NULL;
    stack_destroy(&state->data_stack);
}

void interpret(struct vm_state *state) {
    while (true) {
        switch(state->ip->opcode) {
            case BC_PUSH: {
                stack_push(&(state->data_stack), state->ip->as_arg64.arg);
                break;
            }
            case BC_IPRINT: {
                struct maybe_int64 res = (stack_pop(&(state->data_stack)));
                if (res.valid) {
                    print_int64(res.value);
                }
                break;
            }
            case BC_IREAD: {
                struct maybe_int64 value = maybe_read_int64();
                if (value.valid) {
                    stack_push(&(state->data_stack), value.value);
                }
                break;
            }
            case BC_IADD: {
                struct maybe_int64 res1 = stack_pop(&(state->data_stack));
                struct maybe_int64 res2 = stack_pop(&(state->data_stack));
                if (res1.valid && res2.valid) {
                    stack_push(&(state->data_stack), res1.value + res2.value);
                }
                break;
            }
            case BC_STOP: {
                return;
            }
            default: {
                //err("Not implemented");
                return;
            }
        }
        state->ip = state->ip + 1;
    }
}

void interpret_program(const union ins *program) {
    struct vm_state state = state_create(program);
    interpret(&state);
    state_destroy(&state);
}

int main() {
    const union ins program[] = {
            { BC_IREAD },
            { BC_IPRINT },
            { BC_STOP }
    };

    interpret_program(program);

    return 0;
}