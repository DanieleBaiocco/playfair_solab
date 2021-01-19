//
// Created by Daniele on 14/11/2020.
//

#ifndef UNTITLED10_PLAYFAIR_H
#define UNTITLED10_PLAYFAIR_H

#include <stdio.h>
#include <stdbool.h>

typedef struct Map{
    char character;
    int row;
    int collumn;
} map;

typedef struct PlayFairGrid {
    char** matrix;
    int rowLastInteger;
    int columnLastInteger;
    map** map;
} grid;

typedef struct MissingReplaceCharacter{
    char missingCharacter;
    char replaceCharacter;
} missing;

typedef struct Cell {
    char keyCharacter;
    bool state;
} cell;

typedef struct KeyBlock {
    cell** keyString;
    int size;
    struct KeyBlock* next;
} keyblock;

typedef struct KeyUsed {
    int index;
    keyblock *block;
} key;

typedef struct Container {
    cell** alphabet;
    missing* missingCharacter;
    char specialCharacter;
    key* key;
} kfcontainer;

kfcontainer* create_container (char* keyFile);
grid* create_grid (key* key, cell** alph);
void encode_file(FILE * input, grid* grid, char* directory);
FILE* decode_file(grid* grid, char* fileToDecode);
FILE* to_encoded_format(char* pathname, missing* missingCharacter, char specialCharacter);
void to_decoded_format(FILE *tmpFile, char *pathname);

#endif //UNTITLED10_PLAYFAIR_H
