#include <stdio.h>
#include <string.h>
#include "playfair.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
void printInfo();
void printInfo() {
    printf("playfair (encode|decode) <keyfile> <directory> {<afile>} \n");
}

int main(int argc, char** argv) {

    if( argc < 4){
        printf("Numero dei parametri sbagliato, non è presente nessun file per la codifica|decodifica oppure ci sono parametri mancanti (ne aspettavo almeno 5, ne sono %d)!\n\n", argc);
        printInfo();
        return -1;
    }
    struct stat st = {0};
    if (stat(argv[3], &st) == -1) {
        printf("Directory di destinazione della codifica/decodifica non esistente, crearla e riprovare\n\n");
        return -1;
    }
    kfcontainer* keyfile_parsed = create_container(argv[2]);
  key* key = keyfile_parsed->key;
    cell** alph = keyfile_parsed->alphabet;
    misschar* missing_char = keyfile_parsed->missing_character;
    char special_char = keyfile_parsed->special_character;
    grid* grid = create_grid(key,alph);
   // for(int i =4; i<argc; i++) {
       FILE* tmploaded= changeifileformat(argv[4], missing_char, special_char);
      if (strcmp(argv[1], "encode") == 0) {
            char fileNamePrefix[] = "/filecodificato";
            //gestisco massimo 99 files
            //6 = 2 per gestire due caratteri numerici , 3 per il .py e 1 per il \0
            char *charOfAnInt = malloc(6);
            sprintf(charOfAnInt,"%i",1);
            strcat(charOfAnInt, ".py");
            char *fileName = malloc(sizeof(char) * ((strlen(fileNamePrefix) + strlen(charOfAnInt))));
            strcpy(fileName, fileNamePrefix);
            strcat(fileName, charOfAnInt);
            char *argv3Copy = malloc(sizeof(char) * (strlen(argv[3]) + strlen(fileName)));
            strcpy(argv3Copy, argv[3]);
            strcat(argv3Copy, fileName);
            encode_file(tmploaded, grid, argv3Copy);
          /*
            free(fileName);
            free(charOfAnInt);
            free(argv3Copy);*/
        }
   //}
}






