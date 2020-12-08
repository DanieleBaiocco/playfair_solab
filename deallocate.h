//
// Created by daniele on 08/12/20.
//

#ifndef PLAYFAIR_DEALLOCATE_H
#define PLAYFAIR_DEALLOCATE_H
#include "playfair.h"

void freeAlphabet(cell** alph);
void freeKey(key* key);
void freeContainer(kfcontainer** container);
void freeGrid(grid** grid);

#endif //PLAYFAIR_DEALLOCATE_H
