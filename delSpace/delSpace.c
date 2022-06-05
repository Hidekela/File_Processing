#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficheHelp()
{
    puts("Supprime tous les espaces dans un fichier, cree un nouveau fichier mais n'ecrase pas la source.\n");
    puts("Exemple: delSpace sourc.txt dest.txt\n\n");
    puts("Contenues de sour.txt:\n");
    puts("Lorem ipsum Dolor\nSit\n Amet  goril\n");
    puts("Contenues de dest.txt:\n");
    puts("LoremipsumDolor\nSit\nAmetgoril\n");
}

int supprimeEspace(char *argv[])
{
    char caractere = 0;
    FILE *source = NULL, *destination = NULL;
   
    source = fopen(argv[1],"r");
    if(source == NULL)
    {
        printf("Erreur d'ouverture de %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    destination = fopen(argv[2],"w");
    if(destination == NULL)
    {
        printf("Erreur d'ouverture de %s\n", argv[2]);
        fclose(source);
        return EXIT_FAILURE;
    }

    caractere = fgetc(source);

    while(caractere != EOF)
    {
        if(caractere == ' ')
        {
            caractere = fgetc(source);
            continue;
        }

        fputc(caractere,destination);
        caractere = fgetc(source);
    }

    printf("Le fichier \"%s\" n'a plus d'epaces! xD\n",argv[2]);

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

    return supprimeEspace(argv);
}