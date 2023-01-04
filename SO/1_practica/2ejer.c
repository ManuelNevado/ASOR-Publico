#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/utsname.h>

/*
 * uname returns system info inthe struct pointed by the param
 * uname(struct utsname *buf)
 */

int main(){

    struct utsname buf;

    uname(&buf);

    if(errno){
        perror("FAIL!");
        return errno;
    }

    printf("%s\n", buf.sysname);
    printf("%s\n", buf.version);
    printf("%s\n", buf.machine);

    return 0;
}
