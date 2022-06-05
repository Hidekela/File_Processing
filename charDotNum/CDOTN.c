#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficheHelp()
{
    puts("Separe une caractere alphabetique d'un nombre par ':', cree un nouveau fichier mais n'ecrase pas la source.\n");
    puts("Exemple: CDOTN sourc.txt dest.txt\n\n");
    puts("Contenues de sour.txt:\n");
    puts("Lorem1ipsum34Dolor\nSit\n3Amet111goril2\n");
    puts("Contenues de dest.txt:\n");
    puts("Lorem:1:ipsum:34:Dolor\nSit\n3:Amet:111:goril:2\n");
}

int separeAlphabetNombre(char *argv[])
{
    int change = -1;
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
        if((caractere >= 'a' && caractere <= 'z') || (caractere >= 'A' && caractere <= 'Z'))
        {
            if(change == 1)
            {
                putc(':',destination);
            }
            change = 0;
        }
        else if(caractere >= '0' && caractere <= '9')
        {
            if(change == 0)
            {
                putc(':',destination);
            }
            change = 1;
        }

        fputc(caractere,destination);
        caractere = fgetc(source);
        if(caractere == '\n')
        {
            fputc(caractere,destination);
            change = -1;
            caractere = fgetc(source);
        }
    }

    printf("Le fichier \"%s\" a ete traite avec success!\n",argv[2]);

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

    return separeAlphabetNombre(argv);
}