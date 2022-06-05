#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficheHelp()
{
    puts("Cree un nouveau fichier.\n");
    puts("Exemple: createFile fichier.txt\n\n");
}

int mergeFile(char *argv[])
{
    FILE *source = NULL;
   
    source = fopen(argv[1],"w");
    if(source == NULL)
    {
        printf("Erreur de creation de %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("Le fichier \"%s\" a ete cree!\n",argv[1]);

    fclose(source);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if(argc != 2 || argv[1][0] == '/')
    {
        afficheHelp();
        return EXIT_SUCCESS;
    }

    return mergeFile(argv);
}