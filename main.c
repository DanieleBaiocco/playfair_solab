#include <stdio.h>
#include <string.h>
#include "playfair.h"
#include <stdlib.h>
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
    kfcontainer* keyfile_parsed = create_container(argv[2]);
   key* key = keyfile_parsed->key;
    alph* alph = keyfile_parsed->alphabet;
    char missing_char = keyfile_parsed->missing_character;
    char special_char = keyfile_parsed->special_character;
    /*all'interno della creazione della griglia avrò un metodo che dato un carattere mi va a invalidare tutti
    gli altri caratteri uguali all'interno della keystring e un altro metodo che preso un carattere me lo va
    a rimuovere dall'alfabeto. Questo carattere è lo stesso per entrambi i metodi e corrisponde a un carattere
    che viene inserito con successo nella griglia.*/
    //grid* grid = create_grid(key,alph);
    /*
    for(int i =4; i<argc; i++) {
        char** fileIInPlayFairFormat = changeifileformat(argv[i], missing_char, special_char);
        if (strcmp(argv[1], "encode") == 0) {
            char fileNamePrefix[] = "/filecodificato";
            //gestisco massimo 99 files
            //6 = 2 per gestire due caratteri numerici , 3 per il .py e 1 per il \0
            char *charOfAnInt = malloc(6);
            itoa(i - 3, charOfAnInt, 10);
            strcat(charOfAnInt, ".py");
            char *fileName = malloc(sizeof(char) * ((strlen(fileNamePrefix) + strlen(charOfAnInt))));
            strcpy(fileName, fileNamePrefix);
            strcat(fileName, charOfAnInt);
            char *argv3Copy = malloc(sizeof(char) * (strlen(argv[3]) + strlen(fileName)));
            strcpy(argv3Copy, argv[3]);
            strcat(argv3Copy, fileName);
            encode_file(argv3Copy, fileIInPlayFairFormat);
            free(fileName);
            free(charOfAnInt);
            free(argv3Copy);
        }
    }*/

}





