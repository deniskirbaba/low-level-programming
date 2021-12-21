int discriminant(int a, int b, int c) {
    return b * b - 4 * a * c;
}

int root_count(int a, int b, int c) {
   int D = discriminant(a, b, c);
   if (D > 0) {
       return 2;
   }
   if (D == 0) {
       return 1;
   }
   else {
       return 0;
   }
}

int main() {
    int a = read_int();
    int b = read_int();
    int c = read_int();
    
    printf("%d", root_count(a, b, c));

    return 0;
}