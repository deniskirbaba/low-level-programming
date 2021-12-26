// эти функции вы уже реализовали на предыдущих шагах
int64_t* array_int_read( size_t* size );
int64_t* array_int_min( int64_t* array, size_t size);

// Выводит None если x == NULL, иначе число, на которое указывает x.
void intptr_print( int64_t* x ) {
    if ( x == NULL ) {
        printf( "None" );
    }
    else {
        printf( "%" PRId64, *x);
    }
}

void perform() {
    size_t size = 0;
    int64_t* array = array_int_read( &size );
    intptr_print( array_int_min( array, size ) );
    free( array );    
}