#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficheHelp()
{
    puts("Numerote chaque ligne de fichier, cree un nouveau fichier mais n'ecrase pas la source.\nSi le numero est inférieur à 10, ajoute 0 devant\n\n");
    puts("Exemple: NLF sourc.txt dest.txt\n\n");
    puts("Contenues de sour.txt:\n");
    puts("Lorem ipsum\nDolor\nSit\nAmet goril\n");
    puts("Contenues de dest.txt:\n");
    puts("01 Lorem ipsum\n02 Dolor\n03 Sit\n04 Amet goril\n");
}

int numeroteFichier(char *argv[])
{
    int i = 1;
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
    fprintf(destination,"0%d ",i);
    i++;

    while(caractere != EOF)
    {
        fputc(caractere,destination);
        caractere = fgetc(source);
        if(caractere == '\n')
        {
            fputc(caractere,destination);
            if(i<10)
                fprintf(destination,"0%d ",i);
            else
                fprintf(destination,"%d ",i);

            i++;
            caractere = fgetc(source);
        }
    }

    printf("Le fichier \"%s\" a ete numerote avec success!\n",argv[2]);

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

    return numeroteFichier(argv);
}