#include "inverted.h"

void search_database(mainnode *hash[], char *key)
{
    int index = tolower(key[0]) - 'a';

    if (index < 0 || index >= 26 || hash[index] == NULL)
    {
        printf("Word not found in database\n");
        return;
    }

    mainnode *mtemp = hash[index];

    while (mtemp)
    {
        if (strcmp(mtemp->word, key) == 0)
        {
            printf("\nWord found: %s\n", key);
            subnode *stemp = mtemp->slink;

            while (stemp)
            {
                printf("File: %s  Count: %d\n", stemp->fname, stemp->count);
                stemp = stemp->next;
            }
            return;
        }
        mtemp = mtemp->next;
    }

    printf("Word not found in database\n");
}
