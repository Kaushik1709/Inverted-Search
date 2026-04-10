#include "inverted.h"
void save_database(mainnode *hash[])
{
    char fname[50];
    printf("Enter file name to save database: ");
    scanf("%s", fname);

    // validation for .txt
    char *ext = strstr(fname, ".txt");
    if (!ext || strcmp(ext, ".txt") != 0)
    {
        printf("File must be .txt\n");
        return;
    }

    FILE *fp = fopen(fname, "w");
    if (!fp)
    {
        printf("Unable to create file\n");
        return;
    }

    for (int i = 0; i < HASH_SIZE; i++)
    {
        mainnode *mtemp = hash[i];
        while (mtemp)
        {
            // count files
            int file_count = 0;
            subnode *stemp = mtemp->slink;
            while (stemp)
            {
                file_count++;
                stemp = stemp->next;
            }

            // Start record
            fprintf(fp, "#%d;%s;%d;", i, mtemp->word, file_count);

            stemp = mtemp->slink;
            while (stemp)
            {
                fprintf(fp, "%s;%d;", stemp->fname, stemp->count);
                stemp = stemp->next;
            }

            // End record
            fprintf(fp, "#\n");

            mtemp = mtemp->next;
        }
    }

    fclose(fp);
    printf("Database saved successfully in %s\n", fname);
}
