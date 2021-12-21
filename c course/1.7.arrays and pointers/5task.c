void array_fib(int* array, int* limit) {  
    for (int* current = array; current < limit; current = current + 1) {
      if (current == array) {
          *current = 1;
          continue;
      }
      if (current == array + 1) {
          *current = 1;
          continue;
      }
      else {
          *current = *(current - 1) + *(current - 2);
      }
   }
}