#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){

    setuid(0);
    if(errno){
        printf("The instruction [setuid(0)] has raised an errno\n");
        printf("The errno code is: %d\n", errno);
        printf("The strerror associated is: %s\n",strerror(errno));
        printf("The perror way to raise it would be:\n");
        printf("~~~~~~~~~~~~~~~~~~\n");
        perror("FAIL!");
        printf("~~~~~~~~~~~~~~~~~~\n");
        return 1;
    }
    return 0;
}
