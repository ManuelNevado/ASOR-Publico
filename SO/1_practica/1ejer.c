#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){

    setuid(0);
    if(errno){
        printf("%s\n",strerror(errno));
    }
    return 1;
}
