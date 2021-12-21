int is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

int string_count(char* str) { 
    int res = 0;
    char* current = str;
    while (*current != 0) {
        res = res + 1;
        current = current + 1;
    }
    return res;
}

int string_words(char* str)  {
    int res = 0;
    char* current = str;
    char* prev = NULL;
    while (*current != 0) {
        if (!is_whitespace(*current) && (prev == NULL || is_whitespace(*prev))) {
            res = res + 1;
        }
        prev = current;
        current = current + 1;
    }
    return res;
}