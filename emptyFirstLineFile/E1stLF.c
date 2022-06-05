#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficheHelp()
{
    puts("Vide la premiere ligne dans un fichier, ecrase la source.\n");
    puts("Exemple: E1stLF sour.txt\n\n");
    puts("Contenues de sour.txt:\n");
    puts("Lorem ipsum Dolor\nSit\nAmet goril\n");
    puts("Contenues de sour.txt apres:\n");
    puts("\nSit\nAmet goril\n");
}

int emptyFirstLineFile(char *argv[])
{
    int i, len = strlen(argv[1]);
    char caractere = 0;
    char commande[100] = {0};
    FILE *source = NULL, *destination = NULL;

    for(i = 0; i < len; i++)
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

    destination = fopen("temp.txt","w");
    if(destination == NULL)
    {
        printf("Erreur d'ouverture du fichier de destination!\n");
        fclose(source);
        return EXIT_FAILURE;
    }

    caractere = fgetc(source);

    while(caractere != EOF && caractere != '\n')
    {
        caractere = fgetc(source);
    }

    while(caractere != EOF)
    {
        fputc(caractere,destination);
        caractere = fgetc(source);
    }

    fclose(source);
    fclose(destination);

    sprintf(commande,"del %s",argv[1]);
    system(commande);
    sprintf(commande,"ren temp.txt %s",argv[1]);
    system(commande);

    printf("La premiere ligne du fichier \"%s\" est desormais vide!\n",argv[1]);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if(argc != 2 || argv[1][0] == '/')
    {
        afficheHelp();
        return EXIT_SUCCESS;
    }

    return emptyFirstLineFile(argv);
}