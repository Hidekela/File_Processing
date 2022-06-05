#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficheHelp()
{
    puts("Ajoute une saut a la derniere ligne dans un fichier.\n");
    puts("Exemple: addEL sour.txt\n\n");
    puts("Contenues de sour.txt:\n");
    puts("'Lorem ipsum Dolor\nSit\nAmet goril'\n");
    puts("Contenues de sour.txt apres:\n");
    puts("'Lorem ipsum Dolor\nSit\nAmet goril\n'\n");
}

int addEmptyLine(char *argv[])
{
    int i, len = strlen(argv[1]);
    FILE *source = NULL;

    for(i = 0; i < len; i++)
    {
        if(argv[1][i] == '/' || argv[1][i] == '\\')
        {
            puts("Placez vous dans le meme dossier que le fichier!\n");
            return EXIT_SUCCESS;
        }
    }

    source = fopen(argv[1],"a");
    if(source == NULL)
    {
        printf("Erreur d'ouverture de %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    fseek(source,0,SEEK_END);
    fputc('\n',source);
    
    printf("Le fichier \"%s\" a ete traite avec success!\n",argv[1]);

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

    return addEmptyLine(argv);
}