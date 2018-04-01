// распечатка масиива - проверка
node* tmp_node;

for (int j = 0; j < HASHSIZE; j++)
{
    if (hashtable[j] != NULL)
    {
        printf("%i - ", j);
        tmp_node = hashtable[j];
        while(tmp_node != NULL)
        {
            printf("%s ",hashtable[j]->word);
            tmp_node = tmp_node->next;
        }
        printf("\n");
    }
    
}
