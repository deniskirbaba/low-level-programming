int is_sorted3(int a, int b, int c) {
    if (a > b && b > c) {
        return -1;
    }
    if (a < b && b < c) {
        return 1;
    }
    else {
        return 0;
    }
}