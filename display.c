#include "inverted.h"

void display_database(mainnode *hash[])
{
    printf("\n---------------- DATABASE ----------------\n");
    printf("Index  Word        FileCount   FileName      WordCount\n");
    printf("------------------------------------------\n");

    for (int i = 0; i < HASH_SIZE; i++)
    {
        mainnode *mtemp = hash[i];
        while (mtemp)
        {
            int file_count = 0;
            subnode *stemp = mtemp->slink;

            // Count number of files
            while (stemp)
            {
                file_count++;
                stemp = stemp->next;
            }

            printf("%-5d %-10s %-10d ", i, mtemp->word, file_count);

            stemp = mtemp->slink;
            while (stemp)
            {
                printf("%-12s %-5d ", stemp->fname, stemp->count);
                stemp = stemp->next;
            }
            printf("\n");

            mtemp = mtemp->next;
        }
    }
}
