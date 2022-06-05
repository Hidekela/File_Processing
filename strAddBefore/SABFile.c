#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficheHelp()
{
    puts("Ajoute une chaine de caractere au debut de chaque ligne de fichier, ecrase la source.\n\n");
    puts("Exemple: SABFile sour.txt \"chaine \"\n\n");
    puts("Contenues de sour.txt:\n");
    puts("Lorem ipsum\nDolor\nSit\nAmet goril\n");
    puts("Contenues de sour.txt apres:\n");
    puts("chaine Lorem ipsum\nchaine Dolor\nchaine Sit\nchaine Amet goril\n");
}

int ajoutPrefixe(char *argv[])
{
    int lenFname = strlen(argv[1]), i;
    char caractere = 0;
    char commande[100] = {0};
    FILE *source = NULL, *destination = NULL;
   
    for(i = 0; i < lenFname; i++)
    {
        if(argv[1][i] == '/' || argv[1][i] == '\\')
        {
            puts("Placez vous dans le meme dossier que le fichier!\n");
            return EXIT_SUCCESS;
        }
    }

    source = fopen(argv[1],"r");
    if(source == NULL)
    {
        printf("Erreur d'ouverture de %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    destination = fopen("tmp","w");
    if(destination == NULL)
    {
        puts("Erreur d'ecriture de fichier\n");
        fclose(source);
        return EXIT_FAILURE;
    }

    caractere = fgetc(source);
    fprintf(destination,"%s",argv[2]);

    while(caractere != EOF)
    {
        fputc(caractere,destination);
        caractere = fgetc(source);
        if(caractere == '\n')
        {
            fputc(caractere,destination);
            fprintf(destination,"%s",argv[2]);
            caractere = fgetc(source);
        }
    }

    fclose(source);
    fclose(destination);

    sprintf(commande,"del %s",argv[1]);
    system(commande);
    sprintf(commande,"ren tmp %s",argv[1]);
    system(commande);
    
    printf("Le fichier \"%s\" a ete prefixe avec success! :p\n",argv[1]);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if(argc != 3 || argv[1][0] == '/')
    {
        afficheHelp();
        return EXIT_SUCCESS;
    }

    return ajoutPrefixe(argv);
}