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

// создание хеш-таблицы с размреом САЙЗ
node* hashtable[HASHSIZE];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    
    char check_word[LENGTH+1];
    
    for(int k = 0; k < LENGTH+1; k++)
    {
        check_word[k] = tolower(word[k]);
    }
    
    int hash = hash_function(check_word);
    
    if(hashtable[hash] != NULL)
    {
        if(strcmp(check_word, hashtable[hash]->word) == 0)
        {
            return true;
        }
        else
        {
            node* tmp_node = hashtable[hash]->next;
            while(tmp_node != NULL)
            {
                if(strcmp(check_word, tmp_node->word) == 0)
                {
                    return true;
                    break;
                }
                tmp_node = tmp_node->next;
            }
        }
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
        printf("Could not open dictionary\n");
        return 2;
    }
    
    for (int i = 0; i < HASHSIZE; i++)  // начало списка    типа -- node* head = NULL;
    {
        hashtable[i] = NULL;
    }
    
    while (!feof(file))
    {
        // добавляем/считываем новое слово
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        fscanf(file, "%s", new_node->word);
        count_word++; // счетчик слов
        new_node->next = NULL;
        
        node* tmp_ptr = NULL;
        
        int hash;
        hash = hash_function(new_node->word);
        
        if (hashtable[hash] == NULL)
        {
            hashtable[hash] = new_node;
        }
        else
        {
            tmp_ptr = hashtable[hash];
            hashtable[hash] = new_node;
            new_node->next = tmp_ptr;
        }
        
    }
    
    // закрытие словоря
    fclose(file);

    return true;
}

// хеш функция
int hash_function(char* word)
{
            int p = 0;
            int sum = 0;
            for ( ;word[p] != '\0'; p++)
            {
                sum = sum + word[p]*(p*4+1+p);
            }
            
            sum = sum + (word[1] % 28);
            
            sum = (sum + p) % HASHSIZE;
            
            return sum;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    if (count_word != 0)
    {
        return count_word-1;
    }
    else
    {
        return 0;
    }
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    
node* tmp_node;

int f = 0, m_max = 0; /// проверка

for (int j = 0; j < HASHSIZE; j++)
{
    if (hashtable[j] != NULL)
    {
        int m_pot = 0; /// проверка
        
        tmp_node = hashtable[j];
        while(tmp_node != NULL)
        {
            node* predptr = tmp_node;
            tmp_node = tmp_node->next;
            free(predptr);
            count_word--;
            
            m_pot++; /// проверка
        }
        
        if (m_max <= m_pot)      /// проверка
        {
            m_max = m_pot;
        }
    }
    else /// проверка
    {
        f++;
    }
    
}    
    if (count_word == 0)
    {
        printf("\n%i\n", f);       /// проверка
        printf("%i\n", m_max); 
        return true;
    }
    else
    {
        return false;
    }
}





