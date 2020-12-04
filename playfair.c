//
// Created by Daniele on 14/11/2020.
//
#include "playfair.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void shift(grid* grid);
alph* createAlphabet (char * bufferforalph);
void createmapi(map** mappa, int i, char cj, int j);
alph* getAlph(map** alphmap, char* stringalph);
void addblock(char* buffer, int bufferlength, cell** keyString, vblock_t ** pfirst, vblock_t ** last);
void createCell(cell** pCell, char c, int i);
key *createkey(vblock_t *first, int numberofblocks);
grid* create_grid (key* key, alph* alph);
void changeToFalse(char c, int index, vblock_t* currentBlock);

grid* create_grid (key* key, alph* alph){
    //init matrice
    char **mat = malloc(5 * sizeof(char *));
    for(int i = 0; i < 5; i++)
        mat[i] = malloc(5 * sizeof(char));
    grid* newGrid = malloc(sizeof (grid));
    newGrid->rowLastInteger=0;
    newGrid->columnLastInteger=0;
    newGrid->matrix = mat;

    while (key->block !=NULL && (newGrid->columnLastInteger!=4 || newGrid->rowLastInteger!=4)){
        for(key->index; key->index < key->block->size; key->index++){
            if(key->block->keyString[key->index]->state == true){
                //viene aggiunto nella matrice e viene cambiata la posizione corrente
                char imOnThis= newGrid->matrix[newGrid->rowLastInteger][newGrid->columnLastInteger];
                imOnThis =key->block->keyString[key->index]->keycharacter;
                //viene fatta avanzare di uno la posizione corrente
                shift(newGrid);
                //vengono messi a false tutti gli altri con quella lettera
                changeToFalse(imOnThis, key->index, key->block);
                //viene eliminato(credo) quel carattere presente all'interno dell'alfabeto

            }
        }
        key->block=key->block->next;
    }
}

void changeToFalse(char c, int index, vblock_t* currentBlock){
    while (currentBlock !=NULL ){
        for(index; index < currentBlock->size; index++){
            if(currentBlock->keyString[index]->keycharacter == c){
                currentBlock->keyString[index]->state = false;
            }
        }
        currentBlock= currentBlock->next;
    }
}

void shift(grid* grid){
    if(grid->columnLastInteger==4){
        grid->rowLastInteger++;
        grid->columnLastInteger=0;
    }
    grid->columnLastInteger++;
}

alph* getAlph(map** alphmap, char* stringalph){
    alph* alphtoreturn= malloc(sizeof(alph));
    alphtoreturn->mappacharpos= alphmap;
    alphtoreturn->stringaAlph=stringalph;
    return alphtoreturn;
}

void createmapi(map** mappa, int i, char cj, int j){
    mappa[i] = malloc(sizeof(map));
    mappa[i]->character=cj;
    mappa[i]->integer=j;

}

alph* createAlphabet (char *bufferforalph){
    map** alphmap = malloc(sizeof(map*)*26);
    for(int i=0; i<26; i++){
        for(int j=0; j<25; j++){
            if(i+65==bufferforalph[j]){
                createmapi(alphmap,i,bufferforalph[j],j);
            }
         }
    }
    //vedi come eliminare dinamicamente memoria
    return getAlph(alphmap,bufferforalph);
}

kfcontainer* create_container (char* keyfile){
    int numberOfBlocks = 0;
    FILE* kfile = fopen(keyfile,"r");
    char bufferforalph[31];
    fgets(bufferforalph,31,kfile);
   alph* alphab = createAlphabet (bufferforalph);
   char bufferformissingcharacter[7];
   fgets(bufferformissingcharacter,7,kfile);
  char missingchar = bufferformissingcharacter[0];
    char bufferforspecialcharacter[7];
    fgets(bufferforspecialcharacter,7,kfile);
    char specialchar = bufferforspecialcharacter[0];
    vblock_t *first = NULL;
    vblock_t *last = NULL;
    char bufferforkey[128];
    while(fgets(bufferforkey,128,kfile)!= NULL){
        int bufflen = strlen(bufferforkey);
        if(bufflen!=1){
        numberOfBlocks++;
        cell** keyStr = malloc(sizeof(cell*)*bufflen);
        addblock(bufferforkey, bufflen, keyStr, &first, &last);
        }
    }
    last->next = NULL;
    fclose(kfile);
    key* totalkey = createkey(first, numberOfBlocks);
   kfcontainer* kfcontainertoReturn = malloc(sizeof(kfcontainer));
   kfcontainertoReturn->alphabet = alphab;
   kfcontainertoReturn->missing_character = missingchar;
   kfcontainertoReturn->special_character = specialchar;
   kfcontainertoReturn->key= totalkey;
   return kfcontainertoReturn;
}

key* createkey(vblock_t *first, int numberofblocks) {
    key* keytoreturn = malloc(sizeof(key));
    keytoreturn->index=0;
    keytoreturn->block=first;
    keytoreturn->numberOfBlocks = numberofblocks;
    return keytoreturn;

}

void addblock(char* buffer, int bufferlength, cell** keyStr, vblock_t ** pfirst, vblock_t ** plast ) {
    vblock_t* new_block = malloc(sizeof(vblock_t));
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
    pCell[i]->keycharacter = c;
    pCell[i]->state = true;
}


char** changeifileformat(char* filei, char* missing_character, char* special_character){
    FILE* fin = fopen( filei , "r" );
    char buffer[256];
    while ( fgets(buffer,256,fin)  != NULL ) {

    }

    fclose(fin);
return NULL;
}
