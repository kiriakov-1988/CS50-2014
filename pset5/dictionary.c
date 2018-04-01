/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"

// счетчик загруженных слов
int count_word = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    node* corrent = root;
    
    int level;
    int length = strlen(word);
    int index;

    for (level = 0; level < length; level++)
    {
        index = char_to_int(word[level]);
        if (corrent->children[index])
        {
            corrent = corrent->children[index];
        }
        else
        {
            return false;
        }
    }
    
    if (corrent->is_word == true)
    {
        return true;
    }

    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    // открытие файла
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("\nCould not open dictionary\n");
        return 1;
    }
    
    root = new_node(); /* cоздаем корень дерева */
    node* corrent = root; /* создаем типа бегунок */
    
    char dic_word[LENGTH + 1]; /* для хранения каждого нового слова из словаря */
    
    int level;
    int length;
    int index;

    while (true)
    {        
    
            fscanf(file, "%s", dic_word);
            
            if (feof(file))
            {
                break;
            }
            
            length = strlen(dic_word);
            
            corrent = root;
         
            for (level = 0; level < length; level++)
            {
                index = char_to_int(dic_word[level]);
                if (!corrent->children[index])
                {
                    corrent->children[index] = new_node();
                    if (corrent->children[index] == NULL)
                    {
                        printf("\nCould not load dictionary\n");
                        return 2;
                    }
                }
                corrent = corrent->children[index];
            }
         
            // mark last node as leaf
            corrent->is_word = true;
            count_word++; /* счетчик слов */
    }
    
    // закрытие словоря
    fclose(file);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    
    if (count_word != 0)
    {
        return count_word;
    }
    else
    {
        return 0;
    }
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
void freeNode(node *currentNode);
 
bool unload(void)
{
    // TODO
    for (int i=0; i<ALPHABET_SIZE; i++)            // can't just call freeNode(&root),this will cause free(&root),but
        {
            if (root->children[i] != NULL)  // root is not in heap(cause it's not allocated by malloc)
           
                freeNode(root->children[i]);
           
        }
        free(root);
        return true;         // can't figure out when to return false...
    }

    void freeNode(node *currentNode)
    {
        for (int i=0; i<ALPHABET_SIZE; i++)
        {
            if (currentNode->children[i] != NULL)   // free node recursively, the method is elegant!
                freeNode(currentNode->children[i]); // first free all the children,then free itself.
        }
        free(currentNode);
    }


/* из символа к числу */
int char_to_int(char c)
{
    int k = 0;
    
    if(isalpha(c))
    {
        k = ( (int)tolower(c) - (int)'a' );
    }
    else if (c == '\'')
    {
        k = 26;
    }
    
    return k;
}

/* создание нового узла с дефольными значениями */
node* new_node(void)
{
    node* tmp_node = malloc(sizeof(node));
    
    tmp_node->is_word = false;
    
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        tmp_node->children[i] = NULL;
    }
    
    return tmp_node;
}

