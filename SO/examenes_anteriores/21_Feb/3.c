/*  Escribe un programa que lea simultáneamente de una tubería con nombre,
    que existirá previamente en el directorio actual de trabajo y se llamará tuberia, y del terminal.
    Imprimirá en el terminal los datos leídos y terminará tras 5 segundos sin recibir datos (1
    punto).
    Al detectar el fin de fichero en la tubería, la cerrará y volverá a abrirla (0,5 puntos).
*/


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

#define MAX_BUFFER 1

int main(){

    struct timeval tv = {5,5000000};
    char buf[MAX_BUFFER];
    int fd1 = open("tuberia",O_RDONLY | O_NONBLOCK);
    int fd2 = open("tuberia2",O_RDONLY | O_NONBLOCK);
    if(errno){
        perror("Error al abrir la tuberia");
        close(fd1);
        close(fd2);
        return errno;
    }
    printf("FD de tuberia1: %d\nFD de tuberia2: %d\n",fd1,fd2);
    int selected;

/*
    int r = read(fd_tuberia, buf, MAX_BUFFER);
    printf("%s\n",buf);
*/
    
    do{
    fd_set set;
    FD_ZERO(&set);
    FD_SET(fd2,&set);
    FD_SET(fd1,&set);
//    FD_SET(0,&set);


    selected = select(fd2+1,&set,NULL,NULL,&tv);
    
    if(FD_ISSET(fd1,&set)){
        selected = fd1;
        printf("Recibido en: %d\n",selected);
    }
    else if(FD_ISSET(fd2,&set)){
        printf("Recibido en: %d\n",selected);
        selected = fd2;
    }
    else if(FD_ISSET(0,&set)){
        printf("Recibido en: %d\n",selected);
        selected = 0;
    }

    read(selected,buf, MAX_BUFFER);
    
    if(errno){
        perror("ERROR EN LA LECTURA");
        close(fd1);
        close(fd2);
        return errno;
    }
    printf("%s\n",buf);
    //sleep(5);    
    }while(selected!=-1);


    close(fd1);
    close(fd2);
    return 0;

}

