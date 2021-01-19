//
// Created by daniele on 08/12/20.
//
#include "deallocate.h"
#include <stdlib.h>

void freeString(cell** cells, int size);
void freemap(map** map);
void freematrix(char** matrix);
void freeblocks(keyblock *block);

void freeKey(key* key){
    freeblocks(key->block);
    free(key->block);
    free(key);
}

void freeAlphabet(cell** alph){
    freeString(alph,25);
    free(alph);
}

void freeblocks(keyblock *block){
    freeString(block->keyString, 5);
    free(block->keyString);
    if(block->next!=NULL){
        freeblocks(block->next);
        free(block->next);
    }
}

void freeString(cell** cells, int size){
    for(int i=0; i<size; i++)
        free(cells[i]);
}

void freeGrid(grid** grid){
    freemap((*grid)->map);
    freematrix((*grid)->matrix);
    (*grid)->map = NULL;
    (*grid)->matrix = NULL;
    //free(*grid);
    (*grid)=NULL;
}

void freemap(map** map){
    for(int i=0; i<25; i++){
        free(map[i]);
        map[i]= NULL;
    }
    free(map);
}

void freematrix(char** matrix){
    for(int i=0;i<5;i++){
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
}

void freeContainer(kfcontainer** container){
    free((*container)->missingCharacter);
    free(*container);
    *container=NULL;
}

void freePointersToGridAndContainer(kfcontainer** pointerToContainer, grid** pointerToGrid){
    freeContainer(pointerToContainer);
    freeGrid(pointerToGrid);
}

