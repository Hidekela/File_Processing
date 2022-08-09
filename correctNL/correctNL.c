#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficheHelp()
{
    puts("Efface les sauts de ligne qui ne devrait y apparaitre, ecrase la source.\n");
    puts("Exemple: correctNL sour.txt \n\n");
    puts("Contenues de sour.txt:\n");
    puts("Lorem ipsum\nDolor\nsit\nAmet goril\nblabla titi\nKroukrou\n");
    puts("Contenues de sour.txt apres:\n");
    puts("Lorem ipsum\nDolor sit\nAmet goril blabla titi\nKroukrou\n");
}

int correctNewLine(char *argv[])
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

    destination = fopen("tmp_","w");
    if(destination == NULL)
    {
        puts("Erreur d'ecriture de fichier\n");
        fclose(source);
        return EXIT_FAILURE;
    }

    caractere = fgetc(source);

    while (caractere != EOF)
    {
        while (caractere != '\n' && caractere != EOF)
        {
            fputc(caractere,destination);
            caractere = fgetc(source);
        }

        if(caractere == EOF)
            break;
        
        // Lire le premier caractère de la ligne courante
        caractere = fgetc(source);

        // Si c'est la fin, on met de suite le dernier saut de ligne
        if(caractere == EOF)
        {
            fputc('\n',destination);
            break;
        }

        // Excusez-moi pour le dérangement
        if(('A' <= caractere && caractere <= 'Z') || caractere == '\n')
            fputc('\n',destination);
        else // Got you
            fputc(' ',destination);

        // On met enfin la suite
        fputc(caractere,destination);
        
        caractere = fgetc(source);
    }
    
    fclose(source);
    fclose(destination);

    sprintf(commande,"del %s",argv[1]);
    system(commande);
    sprintf(commande,"ren tmp_ %s",argv[1]);
    if(system(commande) != 0) // system(ren...) renvoie 0 en cas de succès, system(del...) renvoie toujours 0 :/
    {
        printf("Le fichier \"%s\" ne peut pas etre modifie! Le resultat est dans le fichier \"tmp_\"\n",argv[1]);
        return EXIT_FAILURE;
    }
    
    printf("Le fichier \"%s\" a ete traite avec success!\n",argv[1]);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if(argc != 2 || argv[1][0] == '/')
    {
        afficheHelp();
        return EXIT_SUCCESS;
    }

    return correctNewLine(argv);
}