#include <stdio.h>
#include <string.h>
#include "playfair.h"
#include "deallocate.h"
#include "utility.h"

void printInfo() {
    printf("playfair (encode|decode) <keyfile> <directory> {<afile>} \n");
}
void encodeSession(kfcontainer* keyFile, char** argv, int i, grid* grid){
    FILE* tmpFile= to_encoded_format(argv[i], keyFile->missingCharacter, keyFile->specialCharacter);
    char* filename = getFileName(argv[i]);
    char pathname[strlen(argv[3]) + strlen(filename) + 3] ;
    createPathName(argv[3], filename, ".pf", pathname);
    encode_file(tmpFile, grid, pathname);
}

void decodeSession(kfcontainer* keyFile, char** argv, int i, grid* grid){
    FILE* tmpFile = decode_file(grid, argv[i]);
    char* filename = getFileName(argv[i]);
    char pathname[strlen(argv[3]) + strlen(filename) + 4];
    createPathName(argv[3], filename, ".dec", pathname);
    to_decoded_format(tmpFile, pathname);
}

int main(int argc, char** argv) {
    if( argc < 4){
        printf("Numero dei parametri sbagliato, non è presente nessun file per la codifica|decodifica oppure ci sono parametri mancanti (ne aspettavo almeno 5, ne sono %d)!\n\n", argc);
        printInfo();
        return -1;
    }
    if(checkDirectory(argv[3])) {
        printf("Directory di destinazione della codifica/decodifica non esistente; crearla o cambiarla e riprovare\n\n");
        return -1;
    }
    kfcontainer* keyFile = create_container(argv[2]);
    grid* grid = create_grid(keyFile->key, keyFile->alphabet);
    if (strcmp(argv[1], "encode") == 0) {
      for(int i =4; i<argc; i++)
          encodeSession(keyFile, argv, i, grid);
    } else if (strcmp(argv[1], "decode") == 0) {
        for (int i = 4; i < argc; i++)
            decodeSession(keyFile, argv, i, grid);
    }
    else {
        printf("Inserisci correttamente una tra le parole encode e decode\n");
        printInfo();
        return -1;
    }
    freePointersToGridAndContainer(&keyFile, &grid);
    return -1;
}






