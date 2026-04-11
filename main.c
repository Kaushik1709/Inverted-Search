#include "inverted.h"

int main(int argc, char *argv[])
{
    mainnode *hash[HASH_SIZE] = {NULL};
    int db_created = 0;   // flag to avoid multiple creates
    int choice;
    char key[WORD_SIZE];
    char fname[FILE_SIZE];
    while (1)
    {
        printf("\n------ INVERTED SEARCH MENU ------\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Word\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");
        printf("----------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:   
            if (db_created)
            {
                printf("Database already created.\n");
                break;
            }

            if (argc < 2)
            {
                printf("No files passed from command line\n");
                break;
            }

            if (!validate_files(argv, argc))
            {
                printf("Validation failed\n");
                break;
            }

            for (int i = 1; i < argc; i++)
                create_database(argv[i], hash);

            db_created = 1;
            printf("Database created successfully\n");
            break;

        case 2:   
            if (!db_created)
            {
                printf("Create database first\n");
                break;
            }
            display_database(hash);
            break;

        case 3:   
            if (!db_created)
            {
                printf("Create database first\n");
                break;
            }
            printf("Enter word to search: ");
            scanf("%s", key);
            for (int i = 0; key[i]; i++)
                key[i] = tolower(key[i]);
            search_database(hash, key);
            break;

       case 4:   
            if (!db_created)
            {
                printf("Create database first\n");
                break;
            }
            save_database(hash);
            break;
    
        case 5:   
            
            update_database(hash);
            db_created =1;
            break;
    
        case 6:
            exit(0);

        default:
            printf("Invalid choice\n");
        }
    }
}



// Validate files 
int validate_files(char *argv[], int argc)
{
    for (int i = 1; i < argc; i++)
    {
        //Check extension
        char *ext = strstr(argv[i], ".txt");
        if (!ext || strcmp(ext, ".txt") != 0)
        {
            printf("%s : Not a .txt file\n", argv[i]);
            return 0;
        }

        //Check duplicate
        for (int j = i + 1; j < argc; j++)
        {
            if (strcmp(argv[i], argv[j]) == 0)
            {
                printf("%s : Duplicate file\n", argv[i]);
                return 0;
            }
        }

        //Check existence & empty
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("%s : File not found\n", argv[i]);
            return 0;
        }

        fseek(fp, 0, SEEK_END);
        if (ftell(fp) == 0)
        {
            printf("%s : Empty file\n", argv[i]);
            fclose(fp);
            return 0;
        }
        fclose(fp);
    }
    return 1;
}
