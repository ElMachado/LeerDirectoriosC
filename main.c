#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <zconf.h>
int nivel=0;

void recorrer(DIR *d);
DIR *in;

int main(int argc, char **argv)
{
    in = opendir(argv[1]);
    if( in != 0)
    {
        printf("<-----Tree------>.\n");
        printf("Leyendo la ruta: %s \n",argv[1]);
        chdir(argv[1]);
    }
    else{
        printf("<-----Ruta invalida------> \n");
        printf("Leyendo el directorio actual... \n");
        in = opendir(".");
    }

    recorrer(in);
}

void recorrer(DIR *d){
    struct dirent *actual = readdir(d);
    nivel++;
    while(actual != NULL){
        if((strcmp(actual->d_name, ".") != 0) && (strcmp(actual->d_name, "..") != 0)){
            DIR *siguiente = opendir(actual->d_name); //Intenta abrirlo como un directorio
            chdir(actual->d_name);

            if(siguiente != NULL){
              //  if(nivel!=1) nivel--;
                //es directorio
                char *a = actual->d_name;
                printf("\n%*s",nivel*4,"");
                printf("%s\n",actual->d_name);
            //    printf("%*s|_\n",nivel*4,"");
              //  printf("%*s|\n",nivel*5,"");
                recorrer(siguiente);
             chdir("..");
            }else{
                //es archivo
                printf("%*s\n",nivel*4,actual->d_name);
            }
        }
        actual = readdir(d);
    }
    closedir(d);
    if(nivel!=1)nivel--;
   // printf("%*s___\n",nivel*6,"");
}