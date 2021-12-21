// position -- адрес указателя на первый элемент E в массиве,
// для которого predicate(E) выполняется.
// Функция возвращает 0 если элемент не найден.
int array_contains(int* array, int* limit, int** position) {
    for (int* current = array; current < limit; current = current + 1) {
        if (predicate(*current) == 1) {
            *position = current;
            return 1;
        }
    }
    return 0;
}