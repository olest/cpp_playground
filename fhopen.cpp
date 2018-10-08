#include <unistd.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

// http://cutler.io/2005/08/determine-the-number-of-open-files/

int main ( int argc, char** argv, char** env ) {
    int i = 0;
    int fd_counter = 0;
    int max_fd_number = 0;
    struct stat stats;
    struct rlimit rlimits;
    max_fd_number = getdtablesize();
    getrlimit(RLIMIT_NOFILE, &rlimits);
    printf("max_fd_number: %d\n", max_fd_number );
    printf("rlim_cur: %lu\n", rlimits.rlim_cur );
    printf("rlim_max: %lu\n", rlimits.rlim_max );
    for ( i = 0; i <= max_fd_number; i++ ) { 
        fstat(i, &stats); 
        if ( errno != EBADF ) { 
            fd_counter++; 
        } 
    } 
    printf( "open files: %d\n", fd_counter ); 
    return 0; 
} 
