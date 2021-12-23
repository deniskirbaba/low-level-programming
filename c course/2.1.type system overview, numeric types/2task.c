size_t count_zeroes( const void* data, size_t sz ) {
    const int8_t* data8 = (const int8_t*) data;
    size_t res = 0;
    for ( size_t i = 0; i < sz; i = i + 1 ) {
        if ( data8[i] == 0 ) {
            res = res + 1;
        }
    }
    return res;
}
