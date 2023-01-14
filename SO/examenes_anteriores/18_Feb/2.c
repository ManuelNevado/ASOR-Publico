/*
 * Escriba un programa que recorra un directorio, cuya ruta recibe como
argumento, y muestre el nombre de los ficheros que contiene, el uid del usuario propietario,
número de i-nodo y tamaño.
 */
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

void open_dir(char* path);
int get_uid(char* name);

int main(int argc, char** argv){
    
    if(argc!=2){
        fprintf(stderr,"The format must be: ./[bin] [path]\n");
        return 1;
    }

    open_dir(argv[1]);
    return 0;
}


void open_dir(char* path){

    DIR* dir = opendir(path);
    if(errno)
        perror("ERRNO RAISED!!!");
    struct dirent* file = readdir(dir);
    while(file != NULL){
        printf("inode: %ld\n",file->d_ino);
        printf("Size: %d\n",file->d_reclen);
        printf("name: %s\n",file->d_name);
        printf("owner's uid: %d\n",get_uid(file->d_name));
        file = readdir(dir);
    }
}

int get_uid(char* name){
    struct stat* buf;
    stat(name,buf);
    return buf->st_uid;
}
