struct heap_string {
  char* addr;
};

// скопировать в кучу
struct heap_string halloc(const char* s) {
    size_t length = 0;
    const char* ptr = s;
    while(*ptr != NULL) {
        length = length + 1;
        ptr = ptr + 1;
    }
    char* copied_string = malloc(sizeof(char) * (length + 1));
    for (size_t i = 0; i < length; i = i + 1) {
        copied_string[i] = s[i];
    }
    return (struct heap_string) {.addr = copied_string};
}

// освободить память
void heap_string_free( struct heap_string h ) {
    free(h.addr);
}