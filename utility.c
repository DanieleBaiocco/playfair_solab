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

char* getFileName (char* path){
    int count = check(path, '/');
    char* token = strtok(path, "/");
    for(int i=0; i<count-1; i++){
        token = strtok(NULL, " ");
        token = strtok(token,"/");
    }
    for(int i=0; i<strlen(token);i++){
        if(token[i]=='.')
            token[i]= '\0';
    }
    return token;
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
    char filenameplusext[strlen(filename) + strlen(extension)];
    strcpy(filenameplusext, filename);
    strcat(filenameplusext, extension);
    strcpy(pathname, directory);
    strcat(pathname, "/");
    strcat(pathname, filenameplusext);
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