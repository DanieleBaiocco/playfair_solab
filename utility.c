//
// Created by daniele on 08/12/20.
//

#include "utility.h"
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

int check(char *s,char c);

bool checkDirectory(char* directory){
    struct stat st = {0};
    return stat(directory, &st) == -1;
}

char* getFileName(char* path) {
    char* filename = strrchr(path, '/');

    if (filename != NULL)
        filename++;
    else
        filename = path;

    char* dot = strrchr(filename, '.');

    if (dot != NULL)
        *dot = '\0';

    return filename;
}

int check(char *s,char c){
    int i,count=0;
    for(i=0;s[i];i++){
        if(s[i]==c){
            count++;
        }
    }
    return count;
}

void createPathName(char* directory, char* filename, char* extension, char* pathname){
    char filenameplusext[strlen(filename) + strlen(extension) + 1];
    strcpy(filenameplusext, filename);
    strcat(filenameplusext, extension);
    strcpy(pathname, directory);
    strcat(pathname, "/");
    strcat(pathname, filenameplusext);
}

void encodeSpaces(const char* input, char* output) {
    int j = 0;

    for (int i = 0; input[i] != '\0'; i++) {

        // Ignoriamo i caratteri di fine riga
        if (input[i] == '\n' || input[i] == '\r') {
            continue;
        }

        // Spazio -> ZQ
        if (input[i] == ' ') {
            output[j++] = 'Z';
            output[j++] = 'Q';
        }

        // Z reale -> ZY
        else if (input[i] == 'Z') {
            output[j++] = 'Z';
            output[j++] = 'Y';
        }

        else {
            output[j++] = input[i];
        }
    }

    output[j] = '\0';
}


void restoreSpaces(const char* input, char* output) {
    int j = 0;

    for (int i = 0; input[i] != '\0'; ) {

        // ZQ -> spazio
        if (input[i] == 'Z' && input[i + 1] == 'Q') {
            output[j++] = ' ';
            i += 2;
        }

        // ZY -> Z originale
        else if (input[i] == 'Z' && input[i + 1] == 'Y') {
            output[j++] = 'Z';
            i += 2;
        }

        else {
            output[j++] = input[i];
            i++;
        }
    }

    output[j] = '\0';
}

void removeSpaces(char* s) {
    const char* d = s;
    do {
        while (*d == ' ')
            ++d;
    } while ((*s++ = *d++));
}

void replaceChar(char *s, char c1, char c2){
    for(int i=0;s[i];i++){
        if(s[i]==c1){
            s[i]=c2;
        }
    }
}