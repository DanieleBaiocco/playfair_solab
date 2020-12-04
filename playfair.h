//
// Created by Daniele on 14/11/2020.
//

#ifndef UNTITLED10_PLAYFAIR_H
#define UNTITLED10_PLAYFAIR_H


#include <stdbool.h>

typedef struct Map {
    char character;
    int integer;
}map;

/*
 * devo rivedere l'alphabet perchè la map va levata primo, secondo se l'alphabet è solo un'insieme
 * di celle allora non so se va messo o meno come struct
 */
typedef struct Alphabet {
    char* stringaAlph;
    map** mappacharpos;
} alph;

typedef struct PlayFairGrid {
    char** matrix;
    int rowLastInteger;
    int columnLastInteger;
} grid;

typedef struct Cell {
    char keycharacter;
    bool state;
} cell;

typedef struct vblock {
    cell** keyString;
    int size;
    struct vblock *next;
} vblock_t;

typedef struct KeyUsed {
    int index;
    vblock_t *block;
    int numberOfBlocks;
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
key* createkey(vblock_t *first, int numberofblocks);
alph* createAlphabet (char* alph_from_keyfile);
void encode_file(char* directory, char** input);

#endif //UNTITLED10_PLAYFAIR_H
