 int64_t read_int64() {
    int64_t a = 0;
    scanf( "%" SCNd64, &a );
    return a;
}

size_t read_size() {
    size_t a = 0;
    scanf( "%zu", &a );
    return a;
}

// заполнить уже выделенный массив array размера size числами
void array_int_fill( int64_t* array, size_t* size ) {
    for ( size_t i = 0; i < *size; i = i + 1 ) {
        array[i] = read_int64();
    }
}

// Считать размер массива в *size, выделить память под массив и заполнить его числами.
int64_t* array_int_read( size_t* size ) {
    *size = read_size();
    int64_t* array = malloc( 8 * *size );
    array_int_fill( array, size );
    return array;
}