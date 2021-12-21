int is_square(int a) {
    if (a >= 0) {
        int i = 0;

        while (i * i < a) {
            i = i + 1;
        }

        if (i * i == a) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}