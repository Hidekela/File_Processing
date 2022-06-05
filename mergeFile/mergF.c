#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficheHelp()
{
    puts("Ajoute le contenu d'un fichier vers un autre.\n");
    puts("Exemple: mergF sour.txt dest.txt\n\n");
    puts("Contenues de sour.txt:\n");
    puts("Sit\nAmet goril\n");
    puts("Contenues de dest.txt:\n");
    puts("Lorem ipsum Dolor\n");
    puts("Contenues de dest.txt apres:\n");
    puts("Lorem ipsum Dolor\nSit\nAmet goril\n");
}

int mergeFile(char *argv[])
{
    char caractere = 0;
    FILE *source = NULL, *destination = NULL;
   
    source = fopen(argv[1],"r");
    if(source == NULL)
    {
        printf("Erreur d'ouverture de %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    destination = fopen(argv[2],"a");
    if(destination == NULL)
    {
        printf("Erreur d'ouverture de %s\n", argv[2]);
        fclose(source);
        return EXIT_FAILURE;
    }

    fputc('\n',destination);
    caractere = fgetc(source);

    while(caractere != EOF)
    {
        fputc(caractere,destination);
        caractere = fgetc(source);
    }

    printf("Le fichier \"%s\" a ete ajouter a la fin de \"%s\"!\n",argv[1],argv[2]);

    fclose(source);
    fclose(destination);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if(argc != 3 || argv[1][0] == '/')
    {
        afficheHelp();
        return EXIT_SUCCESS;
    }

    return mergeFile(argv);
}