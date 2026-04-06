#include "inverted.h"

int create_database(char *fname, mainnode *hash[])
{
    FILE *fp = fopen(fname, "r");
    if (!fp)
        return 0;

    char word[WORD_SIZE];

    while (fscanf(fp, "%s", word) != EOF)
    {
        // convert to lowercase
        for (int i = 0; word[i]; i++)
            word[i] = tolower(word[i]);

        int index = word[0] - 'a';
        if (index < 0 || index >= 26)
            continue;

        mainnode *mtemp = hash[index];

        while (mtemp)
        {
            if (strcmp(mtemp->word, word) == 0)
                break;
            mtemp = mtemp->next;
        }

        if (mtemp == NULL)
        {
            // New word
            mainnode *newm = malloc(sizeof(mainnode));
            strcpy(newm->word, word);
            newm->next = hash[index];
            hash[index] = newm;

            subnode *news = malloc(sizeof(subnode));
            strcpy(news->fname, fname);
            news->count = 1;
            news->next = NULL;

            newm->slink = news;
        }
        else
        {
            // Word exists → check file list
            subnode *stemp = mtemp->slink;
            while (stemp)
            {
                if (strcmp(stemp->fname, fname) == 0)
                {
                    stemp->count++;
                    break;
                }
                if (stemp->next == NULL)
                    break;
                stemp = stemp->next;
            }

            if (stemp->next == NULL && strcmp(stemp->fname, fname) != 0)
            {
                subnode *news = malloc(sizeof(subnode));
                strcpy(news->fname, fname);
                news->count = 1;
                news->next = NULL;
                stemp->next = news;
            }
        }
    }

    fclose(fp);
    return 1;
}
