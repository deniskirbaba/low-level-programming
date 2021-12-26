#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>



int main() {

    int fd = open("hello.txt", O_WRONLY|O_CREAT );
    write( fd, "Hello", 5 ); 
    close( fd );

    return 0;
}
