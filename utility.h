//
// Created by daniele on 08/12/20.
//

#ifndef PLAYFAIR_UTILITY_H
#define PLAYFAIR_UTILITY_H
#include <stdbool.h>

bool checkDirectory(char* directory);
char* getFileName (char* path);
void createPathName(char* directory, char* filename, char* extension, char* pathname);
void removeSpaces(char* s);
void replaceChar(char *s, char c1, char c2);

#endif //PLAYFAIR_UTILITY_H
