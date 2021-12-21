int is_prime(int a) {
    if (a > 1) {
        for (int i = 2; i < a; i = i + 1) {
            if (a % i == 0) {
                return 0;
            }
        }
        return 1;
    }
    else {
        return 0;
    }
}