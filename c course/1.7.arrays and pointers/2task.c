void normalize(int* pa) {
   while (*pa > 0 && *pa % 2 == 0) {
       *pa = *pa / 2;
   }
}