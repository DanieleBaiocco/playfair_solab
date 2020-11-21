//
// Created by Daniele on 14/11/2020.
//

#ifndef UNTITLED10_PLAYFAIR_H
#define UNTITLED10_PLAYFAIR_H

#include <rpcndr.h>

typedef struct Map {
    char character;
    int integer;
}map;

typedef struct Alphabet {
    char* stringaAlph;
    map** mappacharpos;
    int dimensione;
} alph;

typedef struct PlayFairGrid grid;

typedef struct Cell {
    char keycharacter;
    boolean state;
} cell;

typedef struct vblock {
    cell** keyString;
    int size;
    struct vblock *next;
} vblock_t;

typedef struct KeyUsed {
    int index;
    vblock_t *block;
} key;

typedef struct Container {
    alph* alphabet;
    char missing_character;
    char special_character;
    key* key;
} kfcontainer;

char** changeifileformat (char* filei, char* missing_character, char* special_character);
grid* create_grid (key* key, alph* alph);
kfcontainer* create_container (char* keyfile);
key* load_key(char* key_from_keyfile);
alph* load_alph (char* alph_from_keyfile);
void encode_file(char* directory, char** input);

#endif //UNTITLED10_PLAYFAIR_H
