//
// Created by Daniele on 14/11/2020.
//
#include "playfair.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void createMap(char** matrice, map** map, misschar* missing);
void remove_spaces(char* s);
void shift(grid* grid);
cell** createAlphabet (char* bufferforalph);
void addblock(char* buffer, int bufferlength, cell** keyString, vblock_t ** pfirst, vblock_t ** last);
void createCell(cell** pCell, char c, int i);
key *createkey(vblock_t *first, int numberofblocks);
grid* create_grid (key* key, cell** alph, misschar* missing);
void changeToFalse(char c, int index, vblock_t* currentBlock);
void makeNextNullandRemoveEndChars(vblock_t* last);
void finishToInitGrid(grid* grid, cell** alphabet);
void updateStateIntoAlphabet(cell** alphabet, char c);
void replacechar(char *s,char c1,char c2);
FILE* changeifileformat(char* filei, misschar* missing, char special_character);

grid* create_grid (key* key, cell** alph, misschar* missing){
    //init matrice
    char **mat = malloc(5 * sizeof(char *));
    for(int i = 0; i < 5; i++)
        mat[i] = malloc(5 * sizeof(char));
    map** mapOfNewGrid = malloc(sizeof (map*) * 25);
    grid* newGrid = malloc(sizeof (grid));
    newGrid->rowLastInteger=0;
    newGrid->columnLastInteger=0;
    newGrid->matrix = mat;
    newGrid->map = mapOfNewGrid;
    while (key->block !=NULL && (newGrid->columnLastInteger!=4 || newGrid->rowLastInteger!=5)){
        for(key->index; key->index< key->block->size; key->index++){
            if(key->block->keyString[key->index]->state == true && key->block->keyString[key->index]->keycharacter!= ' '){
                //viene aggiunto nella matrice e viene cambiata la posizione corrente
                newGrid->matrix[newGrid->rowLastInteger][newGrid->columnLastInteger] =key->block->keyString[key->index]->keycharacter;
                //viene fatta avanzare di uno la posizione corrente
                char imOnThis = newGrid->matrix[newGrid->rowLastInteger][newGrid->columnLastInteger];
                shift(newGrid);
                //vengono messi a false tutti gli altri con quella lettera
               changeToFalse(imOnThis, key->index, key->block);
               //update sull'alfabeto
               updateStateIntoAlphabet(alph, key->block->keyString[key->index]->keycharacter);
            }
        }
        key->index =0;
        key->block=key->block->next;
    }
    if(newGrid->rowLastInteger!=4||newGrid->columnLastInteger!=5)
                finishToInitGrid(newGrid, alph);
    for(int i=0; i<5;i++){
        for(int j=0 ; j<5; j++){
            printf("%c",newGrid->matrix[i][j]);
        }
    }
    printf("\n");
    createMap(newGrid->matrix, newGrid->map, missing);
    for (int i=0; i<26;i++){
        if(i+65==missing->missing_character)
            i=i+1;
        printf("%c ", newGrid->map[i]->character);
        printf("%i ", newGrid->map[i]->row);
        printf("%i\n", newGrid->map[i]->collumn);
    }
}

void createMap(char** matrice, map** mapOfGrid, misschar* missing){
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
            grid->matrix[grid->rowLastInteger][grid->columnLastInteger] = alphabet[i]->keycharacter;
            shift(grid);
        }
    }
}

void updateStateIntoAlphabet(cell** alphabet, char c){
    for(int i=0; i<25;i++){
        if(alphabet[i]->keycharacter == c && alphabet[i]->state == true){
            alphabet[i]->state = false;
            i=24;
        }
    }
}
void changeToFalse(char c, int index, vblock_t* currentBlock){
    while (currentBlock!= NULL){

        for(index; index < currentBlock->size; index++){
            if(currentBlock->keyString[index]->keycharacter == c){
                currentBlock->keyString[index]->state = false;
            }
        }
        index=0;
        currentBlock= currentBlock->next;
    }
}

void shift(grid* grid){
    if(grid->columnLastInteger==4){
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
    /*map** alphmap = malloc(sizeof(map*)*26);
    for(int i=0; i<26; i++){
        for(int j=0; j<25; j++){
            if(i+65==bufferforalph[j]){
                createmapi(alphmap,i,bufferforalph[j],j);
            }
         }*/
    }
    //vedi come eliminare dinamicamente memoria



kfcontainer* create_container (char* keyfile){
    int numberOfBlocks = 0;
    FILE* kfile = fopen(keyfile,"r");
    char bufferforalph[31];
    fgets(bufferforalph,31,kfile);
   cell** alphab = createAlphabet (bufferforalph);
   char bufferformissingcharacter[7];
   fgets(bufferformissingcharacter,7,kfile);
   char bff[25];
    for(int i =0; i<25; i++){
        strncat(bff, &alphab[i]->keycharacter, 1);
    }
  misschar* missingchar = createMissingCharacter(bff, bufferformissingcharacter[0]);
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
    makeNextNullandRemoveEndChars(last);
    fclose(kfile);
    key* totalkey = createkey(first, numberOfBlocks);
   kfcontainer* kfcontainertoReturn = malloc(sizeof(kfcontainer));
   kfcontainertoReturn->alphabet = alphab;
   kfcontainertoReturn->missing_character = missingchar;
   kfcontainertoReturn->special_character = specialchar;
   kfcontainertoReturn->key= totalkey;
   return kfcontainertoReturn;

}

misschar* createMissingCharacter (char* string, char replacetothemissing){
    misschar* toReturn = malloc(sizeof (misschar));
    char missingcharacter;
    for(int i=0; i<26; i++){
        char cc = i+65;
            if(strchr(string, cc)==NULL)
                missingcharacter= cc;
    }
    toReturn->missing_character = missingcharacter;
    toReturn->replace_character = replacetothemissing;
    return toReturn;
}

key* createkey(vblock_t *first, int numberofblocks) {
    key* keytoreturn = malloc(sizeof(key));
    keytoreturn->index=0;
    keytoreturn->block=first;
    keytoreturn->numberOfBlocks = numberofblocks;
    return keytoreturn;

}

void makeNextNullandRemoveEndChars(vblock_t* last){
    int startRemovingInt = last->size-5;
    for(startRemovingInt;startRemovingInt<last->size;startRemovingInt++){
        last->keyString[startRemovingInt]->keycharacter = ' ';
    }
    last->next = NULL;
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

/*
 * Metodo che restituisce il contenuto dell'i-esimo file in formato playfair: le lettere della stringa
 * vengono raggruppate a due a due e vengono levati gli spazi. Inoltre per ogni lettera si controlla se
 * è uguale al carattere mancante. In caso affermativo sostituisco il carattere mancante col carattere
 * missing_character. Inoltre per ogni coppia devo controllare se i due caratteri sono uguali. In caso
 * affermativo rimpiazzo il primo/secondo carattere col carattere special_character.
 */
FILE * changeifileformat(char* filei, misschar* missing, char special_character){
    FILE* fin = fopen(filei,"r");
    FILE* tmp = tmpfile();
    char buffer[256];
    while ( fgets(buffer,256,fin)  != NULL ) {
        remove_spaces(buffer);
        replacechar(buffer,missing->missing_character,missing->replace_character);

        if(strlen(buffer)%2==0){
        for(int i=0; i<strlen(buffer)-2;i=i+2){
            char c1 = buffer[i];
            char c2 = buffer[i+1];
            if(c1==c2){
                c2= special_character;
            }
            fputc(c1,tmp);
            fputc(c2,tmp);
            fputc(' ',tmp);
            }
            buffer[strlen(buffer)-1]=special_character;
            fputc(buffer[strlen(buffer)-2],tmp);
            fputc(buffer[strlen(buffer)-1],tmp);
            fputc(' ',tmp);
        }
        else{
                for(int i=0; i<strlen(buffer)-1; i=i+2){
                    char c1 = buffer[i];
                    char c2 = buffer[i+1];
                    if(c1==c2){
                        c2= special_character;
                    }
                    fputc(c1,tmp);
                    fputc(c2,tmp);
                    fputc(' ',tmp);
                }
            }
        }//endwhile
        fclose(fin);
    rewind(tmp);
    return tmp;
    }



void remove_spaces(char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while ((*s++ = *d++));
}

void replacechar(char *s,char c1,char c2){
    for(int i=0;s[i];i++){
        if(s[i]==c1){
            s[i]=c2;
        }
    }
}
