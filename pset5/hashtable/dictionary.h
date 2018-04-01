/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
// #include <string.h> // для memset

// мои подключения
#include <stdio.h> // для открытия файлов
#include <stdlib.h> // для malloc
// #include <stdint.h>
#include <string.h> // для strcmp
#include <ctype.h> // для  tolower


// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H


// мои данные ///////////////////////////////////////////////////////

// структура для списка
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// создание хеш-таблицы с размреом САЙЗ
#define HASHSIZE 19683



// прототип для хеш функции

int hash_function(char* word);


