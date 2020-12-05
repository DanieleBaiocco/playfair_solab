//
// Created by Daniele on 14/11/2020.
//

#ifndef UNTITLED10_PLAYFAIR_H
#define UNTITLED10_PLAYFAIR_H

#include <stdio.h>
#include <stdbool.h>

/*
 * devo rivedere l'alphabet perchè la map va levata primo, secondo se l'alphabet è solo un'insieme
 * di celle allora non so se va messo o meno come struct
 */
typedef struct PlayFairGrid {
    char** matrix;
    int rowLastInteger;
    int columnLastInteger;
} grid;

typedef struct MissingCharacter{
    char missing_character;
    char replace_character;
} misschar;

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
    cell** alphabet;
    misschar* missing_character;
    char special_character;
    key* key;
} kfcontainer;

FILE* changeifileformat (char* filei, misschar* missing_character, char special_character);
grid* create_grid (key* key, cell** alph);
kfcontainer* create_container (char* keyfile);
key* createkey(vblock_t *first, int numberofblocks);
cell** createAlphabet (char* alph_from_keyfile);
misschar* createMissingCharacter (char* string, char replacetothemissing);
void encode_file(char* directory, char** input);

#endif //UNTITLED10_PLAYFAIR_H
