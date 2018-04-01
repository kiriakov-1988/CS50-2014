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
#define HASHSIZE 31249



// прототип для хеш функции

int hash_function(char* word);

// список простых чисел
// int int_primes[45] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197};


char check_word[LENGTH+1];






