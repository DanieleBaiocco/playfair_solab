//
// Created by Daniele on 14/11/2020.
//
#include "playfair.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "deallocate.h"
#include "utility.h"

missing* createMissingCharacter (char* string, char replaceCharacter);
void createMap(char** matrice, map** map);
void shift(grid* grid);
void addblock(char* buffer, int bufferlength, cell** keyString, keyblock ** pfirst, keyblock ** last);
void createCell(cell** pCell, char c, int i);
key* createkey(keyblock *first);
void changeToFalse(char c, int index, keyblock* currentBlock);
void makeNextNullandRemoveEndChars(keyblock* last);
void finishToInitGrid(grid* grid, cell** alphabet);
void updateStateIntoAlphabet(cell** alphabet, char c);
void applyDecodeRule(char* atorespond, char* btorespond, int arow, int brow, int acolumn, int bcolumn, grid *pGrid);
void writeCoupleInsideFile(char atorespond, char btorespond, FILE *pFile);
void applyEncodeRule(char *atorespond, char *btorespond, int arow, int brow, int acolumn, int bcolumn, grid* grid);
char **initMatrix();
grid *initGrid(char** matrix);
void resetPointerAndFreeStructs(key *key, cell **alph, keyblock *firstblock);
void feedGrid(grid* newGrid, key* key, cell** alph);
cell **firstFGets(char* bufferforalph);
missing *secondFGet(char* bufferformissingchar, cell** alphab);
key *fourthFGets(FILE *pFile);
char thirdFGets(FILE *kfile);
kfcontainer *initkfcontainer(cell **alphab, missing *missingchar, char specialchar, key *totalkey);
void insertCoupleInsideTmpFile(int i, FILE *tmp, const char* buffer, char specialchar);
void insertLastWord(FILE *tmp, char *buffer, char specialchar);


FILE* decode_file(grid* grid, char* fileToDecode){
    FILE* input = fopen(fileToDecode,"r");
    FILE* tmp = tmpfile();
    char buffer[256];
    while(fgets(buffer, 256, input) != NULL){
        for(int i=0; i<strlen(buffer); i=i+3){
            int arow = grid->map[buffer[i]-65]->row;
            int acolumn = grid ->map[buffer[i]-65]->collumn;
            int brow = grid->map[buffer[i+1]-65]->row;
            int bcolumn = grid->map[buffer[i+1]-65]->collumn;
            char atorespond =' ';
            char btorespond = ' ';
            applyDecodeRule(&atorespond, &btorespond,arow, brow, acolumn, bcolumn, grid);
            writeCoupleInsideFile(atorespond,btorespond,tmp);
        }
    }
    fclose(input);
    rewind(tmp);
    return tmp;
}

void writeCoupleInsideFile(char atorespond, char btorespond, FILE *tmp) {
    putc(atorespond,tmp);
    putc(btorespond,tmp);
    putc(' ',tmp);
}

void applyDecodeRule(char* atorespond, char* btorespond, int arow, int brow, int acolumn, int bcolumn, grid *grid) {
    if(arow == brow){
        if((acolumn-1) == -1 ){
            *atorespond = grid->matrix[arow][4];
            *btorespond = grid->matrix[brow][--bcolumn];
        }
        else if ((bcolumn-1) == -1){
            *atorespond = grid->matrix[arow][--acolumn];
            *btorespond = grid->matrix[brow][4];
        }
        else{
            *atorespond = grid->matrix[arow][--acolumn];
            *btorespond = grid->matrix[brow][--bcolumn];
        }
    }else if(acolumn == bcolumn){
        if((arow-1)== -1 ){
            *atorespond = grid->matrix[4][acolumn];
            *btorespond = grid->matrix[--brow][bcolumn];
        }
        else if ((brow-1) == -1){
            *atorespond = grid->matrix[--arow][acolumn];
            *btorespond = grid->matrix[4][bcolumn];
        }
        else{
            *atorespond = grid->matrix[--arow][acolumn];
            *btorespond = grid->matrix[--brow][bcolumn];
        }
    }else {
        *atorespond = grid->matrix[arow][bcolumn];
        *btorespond = grid->matrix[brow][acolumn];
    }
}


void to_decoded_format(FILE *tmpFile, char *pathname) {
    FILE* output = fopen(pathname,"w");
    char buffer[256];
    while ( fgets(buffer,256,tmpFile)  != NULL ) {
        for(int i=0; i<strlen(buffer)-1; i=i+2) {
            char c1 = buffer[i];
            char c2 = buffer[i + 1];
            if (c1 == c2) {
                c2 = c1;
            }
        }
        removeSpaces(buffer);
        fputs(buffer,output);
    }
    fclose(output);
}

void encode_file(FILE * input, grid* grid, char* directory){
    FILE* outputFile = fopen(directory, "w");
    char buffer[256];
    while(fgets(buffer, 256, input) != NULL){
        for(int i=0; i<strlen(buffer); i=i+3){
            char a = buffer[i];
            char b = buffer[i+1];
            int arow = grid->map[a-65]->row;
            int acolumn = grid ->map[a-65]->collumn;
            int brow = grid->map[b-65]->row;
            int bcolumn = grid->map[b-65]->collumn;
            char atorespond =' ';
            char btorespond = ' ';
            applyEncodeRule(&atorespond, &btorespond, arow, brow, acolumn, bcolumn, grid);
            writeCoupleInsideFile(atorespond, btorespond, outputFile);
        }
    }
    fclose(outputFile);
}

void applyEncodeRule(char *atorespond, char *btorespond, int arow, int brow, int acolumn, int bcolumn, grid* grid) {
    if(arow == brow){
        *atorespond = grid->matrix[arow][++acolumn%5];
        *btorespond = grid->matrix[brow][++bcolumn%5];

    }else if(acolumn == bcolumn){
        *atorespond = grid->matrix[++arow%5][acolumn];
        *btorespond = grid->matrix[++brow%5][bcolumn];
    }else {
        *atorespond = grid->matrix[arow][bcolumn];
        *btorespond = grid->matrix[brow][acolumn];
    }
}

grid* create_grid (key* key, cell** alph){
    char **mat = initMatrix();
    map** mapOfNewGrid = malloc(sizeof (map*) * 25);
    grid* newGrid = initGrid(mat);
    keyblock * firstblock = key->block;
    while (key->block !=NULL && (newGrid->columnLastInteger != 4 || newGrid->rowLastInteger != 5)){
        for(key->index; key->index< key->block->size; key->index++){
            if(key->block->keyString[key->index]->state == true && key->block->keyString[key->index]->keyCharacter != ' ')
                feedGrid(newGrid,key,alph);
        }
        key->index =0;
        key->block=key->block->next;
    }
    if(newGrid->rowLastInteger != 4 || newGrid->columnLastInteger != 5)
        finishToInitGrid(newGrid, alph);
    resetPointerAndFreeStructs(key, alph, firstblock);
    createMap(newGrid->matrix,mapOfNewGrid);
    newGrid->map= mapOfNewGrid;
    return newGrid;
}

void feedGrid(grid* newGrid, key* key, cell** alph) {
    newGrid->matrix[newGrid->rowLastInteger][newGrid->columnLastInteger] =key->block->keyString[key->index]->keyCharacter;
    char imOnThis = newGrid->matrix[newGrid->rowLastInteger][newGrid->columnLastInteger];
    shift(newGrid);
    changeToFalse(imOnThis, key->index, key->block);
    updateStateIntoAlphabet(alph, key->block->keyString[key->index]->keyCharacter);
}

void resetPointerAndFreeStructs(key *key, cell **alph, keyblock *firstblock) {
    key->block = firstblock;
    freeKey(key);
    freeAlphabet(alph);
}

grid *initGrid(char** matrix) {
    grid* newGrid = malloc(sizeof (grid));
    newGrid->rowLastInteger=0;
    newGrid->columnLastInteger=0;
    newGrid->matrix = matrix;
    return newGrid;
}

char **initMatrix() {
    char **mat = malloc(5 * sizeof(char *));
    for(int i = 0; i < 5; i++)
        mat[i] = malloc(5 * sizeof(char));
    return mat;
}

void createMap(char** matrice, map** mapOfGrid){
    for(int i=0; i<26; i++){
        for(int j=0; j<5; j++){
            for(int k=0; k<5; k++){
                if(i+65 == matrice[j][k]){
                    mapOfGrid[i] = malloc(sizeof(map));
                    mapOfGrid[i]->character= matrice[j][k];
                    mapOfGrid[i]->row = j;
                    mapOfGrid[i]->collumn = k;
                }
            }
        }
    }
}

void finishToInitGrid(grid* grid, cell** alphabet){
    for(int i=0; i<25; i++){
        if(alphabet[i]->state == true){
            grid->matrix[grid->rowLastInteger][grid->columnLastInteger] = alphabet[i]->keyCharacter;
            shift(grid);
        }
    }
}

void updateStateIntoAlphabet(cell** alphabet, char c){
    for(int i=0; i<25;i++){
        if(alphabet[i]->keyCharacter == c && alphabet[i]->state == true){
            alphabet[i]->state = false;
            i=24;
        }
    }
}

void changeToFalse(char c, int index, keyblock* currentBlock){
    while (currentBlock!= NULL){
        for(index; index < currentBlock->size; index++){
            if(currentBlock->keyString[index]->keyCharacter == c){
                currentBlock->keyString[index]->state = false;
            }
        }
        index=0;
        currentBlock= currentBlock->next;
    }
}

void shift(grid* grid){
    if(grid->columnLastInteger == 4){
        grid->rowLastInteger++;
        grid->columnLastInteger=0;
    } else
        grid->columnLastInteger++;
}

cell** createAlphabet (char *bufferforalph){
    cell** alphabet = malloc(sizeof(cell*)*25);
    for(int i=0; i<25;i++){
        createCell(alphabet,bufferforalph[i],i);
    }
    return alphabet;

    }

kfcontainer* create_container (char* keyfile){
    FILE* kfile = fopen(keyfile,"r");
    char bufferforalph[31];
    fgets(bufferforalph,31,kfile);
    cell** alphab = firstFGets(bufferforalph);
    char bufferformissingcharacter[7];
    fgets(bufferformissingcharacter,7,kfile);
    missing* missingchar = secondFGet(bufferformissingcharacter, alphab);
    char specialchar = thirdFGets(kfile);
    key* totalkey = fourthFGets(kfile);
    return initkfcontainer(alphab,missingchar,specialchar,totalkey);
}

kfcontainer *initkfcontainer(cell **alphab, missing *missingchar, char specialchar, key *totalkey) {
    kfcontainer* kfcontainertoReturn = malloc(sizeof(kfcontainer));
    kfcontainertoReturn->alphabet = alphab;
    kfcontainertoReturn->missingCharacter = missingchar;
    kfcontainertoReturn->specialCharacter = specialchar;
    kfcontainertoReturn->key= totalkey;
    return kfcontainertoReturn;
}

key *fourthFGets(FILE *pFile) {
    keyblock *first = NULL;
    keyblock *last = NULL;
    char bufferforkey[128];
    while(fgets(bufferforkey, 128, pFile) != NULL){
        int bufflen = strlen(bufferforkey);
        if(bufflen!=1){
            cell** keyStr = malloc(sizeof(cell*)*bufflen);
            addblock(bufferforkey, bufflen, keyStr, &first, &last);
        }
    }
    makeNextNullandRemoveEndChars(last);
    fclose(pFile);
    return createkey(first);
}

char thirdFGets(FILE *kfile) {
    char bufferforspecialcharacter[7];
    fgets(bufferforspecialcharacter,7,kfile);
    return bufferforspecialcharacter[0];
}

missing *secondFGet(char* bufferformissingchar, cell** alphab) {
    char bff[25];
    for(int i =0; i<25; i++){
        strncat(bff, &alphab[i]->keyCharacter, 1);
    }
    return createMissingCharacter(bff, bufferformissingchar[0]);
}

cell **firstFGets(char* bufferforalph) {
    cell** alphabet = malloc(sizeof(cell*)*25);
    for(int i=0; i<25;i++){
        createCell(alphabet,bufferforalph[i],i);
    }
    return alphabet;
}

missing* createMissingCharacter (char* string, char replaceCharacter){
    missing* toReturn = malloc(sizeof (missing));
    char missingcharacter;
    for(int i=0; i<26; i++){
        char cc = i+65;
            if(strchr(string, cc)==NULL) {
                missingcharacter = cc;
               }
    }
    toReturn->missingCharacter = missingcharacter;
    toReturn->replaceCharacter = replaceCharacter;
    return toReturn;
}

key* createkey(keyblock *first) {
    key* keytoreturn = malloc(sizeof(key));
    keytoreturn->index=0;
    keytoreturn->block=first;
    return keytoreturn;
}

void makeNextNullandRemoveEndChars(keyblock* last){
    int startRemovingInt = last->size-5;
    for(startRemovingInt;startRemovingInt<last->size;startRemovingInt++){
        last->keyString[startRemovingInt]->keyCharacter = ' ';
    }
    last->next = NULL;
}

void addblock(char* buffer, int bufferlength, cell** keyStr, keyblock ** pfirst, keyblock ** plast ) {
    keyblock* new_block = malloc(sizeof(keyblock));
    for(int i=0; i<bufferlength;i++){
        createCell(keyStr,buffer[i],i);
    }
    new_block->keyString = keyStr;
    new_block->next= NULL;
    new_block->size= bufferlength;
    if (*pfirst == NULL) {
        *pfirst = new_block;
    } else {
        (*plast)->next = new_block;
    }
    *plast = new_block;
}

void createCell(cell **pCell, char c, int i) {
    pCell[i]=malloc(sizeof(cell));
    pCell[i]->keyCharacter = c;
    pCell[i]->state = true;
}

/**
 * Metodo che restituisce il contenuto dell'i-esimo file in formato playfair: le lettere della stringa
 * vengono raggruppate a due a due e vengono levati gli spazi. Inoltre per ogni lettera si controlla se
 * è uguale al carattere mancante. In caso affermativo sostituisco il carattere mancante col carattere
 * missing_character. Inoltre per ogni coppia devo controllare se i due caratteri sono uguali. In caso
 * affermativo rimpiazzo il primo/secondo carattere col carattere special_character.
 */
FILE * to_encoded_format(char* pathname, missing* missing_character, char special_character){
    FILE* fin = fopen(pathname, "r");
    FILE* tmp = tmpfile();
    char buffer[256];
    while ( fgets(buffer,256,fin)  != NULL ) {
        removeSpaces(buffer);
        replaceChar(buffer, missing_character->missingCharacter, missing_character->replaceCharacter);
        if(strlen(buffer)%2==0){
            for(int i=0; i<strlen(buffer)-2;i=i+2)
               insertCoupleInsideTmpFile(i, tmp,buffer, special_character);
            insertLastWord(tmp,buffer,special_character);
        }
        else{
            for(int i=0; i<strlen(buffer)-1; i=i+2)
                insertCoupleInsideTmpFile(i, tmp, buffer, special_character);
        }
    }
    fclose(fin);
    rewind(tmp);
    return tmp;
    }

void insertLastWord(FILE *tmp, char *buffer, char specialchar) {
    buffer[strlen(buffer) - 1] = specialchar;
    fputc(buffer[strlen(buffer) - 2], tmp);
    fputc(buffer[strlen(buffer) - 1], tmp);
    fputc(' ', tmp);
}

void insertCoupleInsideTmpFile(int i, FILE *tmp, const char* buffer, char specialchar) {
    char c1 = buffer[i];
    char c2 = buffer[i+1];
    if(c1==c2){
        c2= specialchar;
    }
    fputc(c1,tmp);
    fputc(c2,tmp);
    fputc(' ',tmp);
}




