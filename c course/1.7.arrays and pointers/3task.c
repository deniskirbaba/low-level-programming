void factorize( int n, int* a, int* b )
{
    for (int i = 2; i <= n / 2; i = i + 1) {
        if (n % i == 0) {
            *a = i;
            *b = n / i;
            return;
        }
    }
    *a = 1;
    *b = n;
}