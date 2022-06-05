#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficheHelp()
{
    puts("Repete une chaine caractere entre le premier espace et le premier point trouves dans un fichier apres un tiret trouve, cree un nouveau fichier mais n'ecrase pas la source.\n");
    puts("Exemple: RBSM sour.txt dest.txt\n\n");
    puts("Contenues de sour.txt:\n");
    puts("2022 Matio:1.12-14\n2022 Marka3.1-23\n");
    puts("Contenues de dest.txt:\n");
    puts("2022 Matio:1.12#Matio:1.14\n2022 Marka3.1#Marka3.23\n");
}

int modifMofonaina(char *argv[])
{
    int len,i;
    char tmp[200] = {0};
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
        len = 0;
        // On cherche le premier ' '
        while(caractere != EOF && caractere != ' ')
        {
            fputc(caractere,destination);
            caractere = fgetc(source);
            if(caractere == EOF)
            {
                puts("Le fichier est sans espace!\n");
                fclose(source);
                fclose(destination);
                return EXIT_SUCCESS;
            }
        }
        // On sort du boucle lorsqu'on a caractere = ' ' et on copie ' ' dans destination
        fputc(caractere,destination);
        
        caractere = fgetc(source);
        // On prend le caractere suivant et on commence à copier dans la boucle
        // si ce n'est la fin du fichier ou un point

        while(caractere != EOF && caractere != '.')
        {
            tmp[len] = caractere;
            len++;
            fputc(caractere,destination);
            caractere = fgetc(source);
            if(caractere == EOF)
            {
                puts("Le fichier est sans point!\n");
                fclose(source);
                fclose(destination);
                return EXIT_SUCCESS;
            }
        }
        // On sort du boucle lorsqu'on a caractere = '.' et on copie '.' dans tmp et destination
        tmp[len] = caractere;
        len++;
        fputc(caractere,destination);

        caractere = fgetc(source);
        // On prend le caractere suivant et on cherche le premier '-'
        while(caractere != EOF && caractere != '-')
        {
            fputc(caractere,destination);
            caractere = fgetc(source);
            if(caractere == EOF)
            {
                puts("Le fichier est sans tiret!\n");
                fclose(source);
                fclose(destination);
                return EXIT_SUCCESS;
            }
        }
        // On ecrit '#' dans destination
        fputc('#',destination);

        // Puis on insere la valeur de tmp (contenant la valeur à repeter) dans destination
        for(i = 0; i < len; i++)
        {
            fputc(tmp[i],destination);
        }
        
        caractere = fgetc(source);
        // On prend le caractere apres '-' et on copie normalement jusqu'à la fin de la ligne
        while(caractere != EOF && caractere != '\n')
        {
            fputc(caractere,destination);
            caractere = fgetc(source);
            if(caractere == '\n')
            {
                fputc(caractere,destination);
                caractere = fgetc(source);
                break;
            }
        }
        // Puis on recommence
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

    return modifMofonaina(argv);
}