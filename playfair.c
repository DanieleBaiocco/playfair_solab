//
// Created by Daniele on 14/11/2020.
//
#include "playfair.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>
alph* createAlphabet (char * bufferforalph);
void createmapi(map** mappa, int i, char cj, int j);
alph* getAlph(map** alphmap, int dim, char* stringalph);
void addblock(char* buffer, int bufferlength, cell** keyString, vblock_t ** pfirst, vblock_t ** last);
void createCell(cell** pCell, char c, int i);
key *createkey(vblock_t *first);

alph* getAlph(map** alphmap, int dim, char* stringalph){
    alph* alphtoreturn= malloc(sizeof(alph));
    alphtoreturn->dimensione= dim;
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
    map** alphmap = malloc(sizeof(map*)*25);
    for(int i=0; i<26; i++){
        for(int j=0; j<25; j++){
            if(i+65==bufferforalph[j]){
                createmapi(alphmap,i,bufferforalph[j],j);
            }
         }
    }
    return getAlph(alphmap,25,bufferforalph);
}

kfcontainer* create_container (char* keyfile){
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
        cell** keyStr = malloc(sizeof(cell*)*bufflen);
        addblock(bufferforkey,bufflen, keyStr, &first, &last);
    }
    fclose(kfile);
    key* totalkey = createkey(first);
   kfcontainer* kfcontainertoReturn = malloc(sizeof(kfcontainer));
   kfcontainertoReturn->alphabet = alphab;
   kfcontainertoReturn->missing_character = missingchar;
   kfcontainertoReturn->special_character = specialchar;
   kfcontainertoReturn->key= totalkey;
   return kfcontainertoReturn;
}

key* createkey(vblock_t *first) {
    key* keytoreturn = malloc(sizeof(key));
    keytoreturn->index=0;
    keytoreturn->block=first;
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
