int64_t* array_int_min( int64_t* array, size_t size ) {
    int64_t* min = NULL;
    for ( size_t i = 0; i < size; i = i + 1 ) {
        if ( min == NULL ) {
            min = &array[i];
        }
        else {
            if ( array[i] < *min ) {
                min = &array[i];
            }
        }
    }
    return min;
}