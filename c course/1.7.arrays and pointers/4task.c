void array_reverse(int* array, int size) {
    for (int i = 0; i < size / 2; i = i + 1) {
        int x = array[i];
        array[i] = array[size - 1 - i];
        array[size - 1 - i] = x;
    }
}

void array_reverse_ptr(int* array, int* limit) {
    int* left = array;
    int* right = limit-1;
    while (left < right) {
        int x = *left;
        *left = *right;
        *right = x;
        left = left + 1;
        right = right - 1;
    }
}