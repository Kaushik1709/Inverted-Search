#include "inverted.h"
void update_database(mainnode *hash[])
{
    char fname[50];
    printf("Enter backup file name: ");
    scanf("%s", fname);

    // validate extension
    char *ext = strstr(fname, ".txt");
    if (!ext || strcmp(ext, ".txt") != 0)
    {
        printf("Only .txt files allowed\n");
        return;
    }

    FILE *fp = fopen(fname, "r");
    if (!fp)
    {
        printf("File not found\n");
        return;
    }

    // clear old database
    clear_database(hash);

    char line[512];

    while (fgets(line, sizeof(line), fp))
    {
        if (line[0] != '#')
        {
            printf("Invalid database file format\n");
            fclose(fp);
            return;
        }

        // remove last #
        line[strlen(line) - 2] = '\0';   // remove "#\n"

        // skip first #
        char *token = strtok(line + 1, ";");

        int index = atoi(token);          // index
        token = strtok(NULL, ";");        // word
        char word[50];
        strcpy(word, token);

        token = strtok(NULL, ";");        // file count
        int fcount = atoi(token);

        // create main node
        mainnode *newm = malloc(sizeof(mainnode));
        strcpy(newm->word, word);
        newm->slink = NULL;
        newm->next = hash[index];
        hash[index] = newm;

        subnode *last = NULL;

        for (int i = 0; i < fcount; i++)
        {
            char fname2[50];
            int count;

            token = strtok(NULL, ";");
            strcpy(fname2, token);

            token = strtok(NULL, ";");
            count = atoi(token);

            subnode *news = malloc(sizeof(subnode));
            strcpy(news->fname, fname2);
            news->count = count;
            news->next = NULL;

            if (newm->slink == NULL)
                newm->slink = news;
            else
                last->next = news;

            last = news;
        }
    }

    fclose(fp);
    printf("Database updated successfully from backup file\n");
}

void clear_database(mainnode *hash[])
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        mainnode *m = hash[i];
        while (m)
        {
            subnode *s = m->slink;
            while (s)
            {
                subnode *stmp = s;
                s = s->next;
                free(stmp);
            }
            mainnode *mtmp = m;
            m = m->next;
            free(mtmp);
        }
        hash[i] = NULL;
    }
}