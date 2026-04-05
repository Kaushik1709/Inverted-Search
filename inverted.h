#ifndef INVERTED_H
#define INVERTED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_SIZE 50
#define FILE_SIZE 50
#define HASH_SIZE 26

/* Sub node (file list) */
typedef struct subnode
{
    char fname[FILE_SIZE];
    int count;
    struct subnode *next;
}subnode;

/* Main node (word list) */
typedef struct mainnode
{
    char word[WORD_SIZE];
    subnode *slink;
    struct mainnode *next;
}mainnode;

/* Function prototypes */
int validate_files(char *argv[], int argc);
int create_database(char *fname, mainnode *hash[]);
void display_database(mainnode *hash[]);
void search_database(mainnode *hash[], char *key);
void save_database(mainnode *hash[]);

void update_database(mainnode *hash[]);
void clear_database(mainnode *hash[]);

#endif
