#include <stdio.h>
#include <string.h>
#include "playfair.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
void printInfo();
int check(char *s,char c);
char* getFileName (char* argvI);
void createPathName(char* directory, char* firstpart, char* extension, char* pathname);

void createPathName(char* directory, char* firstpart, char* extension, char* pathname){
    char firstpartplusext[strlen(firstpart)+strlen(extension)];
    strcpy(firstpartplusext, firstpart);
    strcat(firstpartplusext, extension);
    strcpy(pathname, directory);
    strcat(pathname, "/");
    strcat(pathname, firstpartplusext);
}

char* getFileName (char* argvI){
    int count = check(argvI,'/');
    char* token = strtok(argvI,"/");
    for(int i=0; i<count-1; i++){
        token = strtok(NULL, " ");
        token = strtok(token,"/");
    }
    for(int i=0; i<strlen(token);i++){
        if(token[i]=='.')
            token[i]= '\0';
    }
    return token;
}

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
    if (strcmp(argv[1], "encode") == 0) {
      for(int i =4; i<argc; i++) {
            FILE* tmpFile= toEncodedFormat(argv[i], missing_char, special_char);
            char* tkn = getFileName(argv[i]);
            char pathName[strlen(argv[3])+strlen(tkn)+3] ;
            createPathName(argv[3], tkn, ".pf", pathName);
            encode_file(tmpFile, grid, pathName);
        }
   }  else if (strcmp(argv[1], "decode") == 0) {
        for(int i =4; i<argc; i++) {
            FILE* tmpFile = decode_file(grid, argv[i]);
            char* tkn = getFileName(argv[i]);
            char pathName[strlen(argv[3])+strlen(tkn)+4];
            createPathName(argv[3], tkn, ".dec",pathName);
            toDecodedFormat(tmpFile, pathName, missing_char, special_char);
        }
    } else {
        printf("Inserisci correttamente una tra le parole encode e decode\n");
        printInfo();
        return -1;
    }
}





