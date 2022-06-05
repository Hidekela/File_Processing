#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficheHelp()
{
    puts("Remplace une chaine de caractere (la premiere trouvee a chaque ligne) par une autre, ecrase la source.\n");
    puts("Exemple: strRF sour.txt \" 1:\" \" I \"\n\n");
    puts("Contenues de sour.txt:\n");
    puts(" 1:Lorem ipsum 1: Dolor\nSit\n 1:Amet goril\n");
    puts("Contenues de sour.txt apres:\n");
    puts(" I Lorem ipsum 1: Dolor\nSit\n I Amet goril\n");
    puts("\n\nSi vous voulez remplacer les sauts de ligne, mettez comme 2eme argument \"\\EOL\" au lieu de \"\\n\"!\n");
    puts("Vous pouvez seulement utiliser \"\\EOL\" (ou \"blabla\\EOLLorem ipsum\\EOLetc...\") comme 3eme argument si et seulement si vous mettez comme 2eme argument \"\\EOL\"!\n");
}

int replaceStringFile(char *argv[])
{
    int lenFname = strlen(argv[1]), lenOld =  strlen(argv[2]), lenNew = strlen(argv[3]), i, j;
    char commande[100] = {0};
    char caractere = 0;
    FILE *source = NULL, *destination = NULL;
   
    for(i = 0; i < lenFname; i++)
    {
        if(argv[1][i] == '/' || argv[1][i] == '\\')
        {
            puts("Placez vous dans le meme dossier que le fichier!\n");
            return EXIT_SUCCESS;
        }
    }

    if(lenOld == 0)
    {
        puts("Saisissez une chaine non vide!\n");
        return EXIT_SUCCESS;
    }

    source = fopen(argv[1],"r");
    if(source == NULL)
    {
        printf("Erreur d'ouverture de %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    destination = fopen("tempp","w");
    if(destination == NULL)
    {
        puts("Erreur d'ecriture de fichier\n");
        fclose(source);
        return EXIT_FAILURE;
    }

    caractere = fgetc(source);

    if(lenOld == 4 && argv[2][0] == '\\' && argv[2][1] == 'E' && argv[2][2] == 'O' && argv[2][3] == 'L')
    {
        while(caractere != EOF)
        {
            // On copie normalement jusqu'à la fin de la ligne
            while(caractere != EOF && caractere != '\n')
            {
                fputc(caractere,destination);
                caractere = fgetc(source);
                if(caractere == '\n')
                {
                    break;
                }
            }

            if(caractere == EOF)
            {
                puts("Fin du fichier! Fin du replacement des sauts de ligne!\n");
                fclose(source);
                fclose(destination);

                sprintf(commande,"del %s",argv[1]);
                system(commande);
                sprintf(commande,"ren tempp %s",argv[1]);
                system(commande);

                return EXIT_SUCCESS;
            }

            // On ajoute le remplacement (argv[3])
            for(i = 0; i < lenNew; i++)
            {
                if(argv[3][i] == '\\' && lenNew > i+3 && argv[3][i+1] == 'E' && argv[3][i+2] == 'O' && argv[3][i+3] == 'L')
                {
                    fputc('\n',destination);
                    i+=3;
                }
                else
                {
                    fputc(argv[3][i],destination);
                }
            }

            caractere = fgetc(source);
            // Puis on recommence
        }
    }
    else // Si argv[2] n'est pas une retour à la ligne
    {
        while(caractere != EOF)
        {
            // On cherche jusqu'à trouvé l'équivalent de argv[2] dans le fichier
            while(caractere != EOF)
            {
                // On cherche le premier caractere de l'old string (argv[2])
                while(caractere != EOF && caractere != argv[2][0])
                {
                    fputc(caractere,destination);
                    caractere = fgetc(source);
                    if(caractere == EOF)
                    {
                        puts("Fin du fichier!\n");
                        fclose(source);
                        fclose(destination);

                        sprintf(commande,"del %s",argv[1]);
                        system(commande);
                        sprintf(commande,"ren tempp %s",argv[1]);
                        system(commande);
        
                        return EXIT_SUCCESS;
                    }
                }

                for(i = 1; i < lenOld && caractere != EOF; i++)
                {
                    caractere = fgetc(source);
                    if(caractere != argv[2][i])
                    {
                        fseek(source,-i-1,SEEK_CUR);
                        // On revient et on copie normalement, désolé pour le dérangement
                        caractere = fgetc(source);
                        for(j = 0; j <= i; j++)
                        {
                            fputc(caractere,destination);
                            caractere = fgetc(source);
                        }
                        break;
                    }
                }

                if(caractere == EOF)
                {
                    puts("Fin du fichier!\n");
                    fclose(source);
                    fclose(destination);

                    sprintf(commande,"del %s",argv[1]);
                    system(commande);
                    sprintf(commande,"ren tempp %s",argv[1]);
                    system(commande);
    
                    return EXIT_SUCCESS;
                }

                // C'est a dire que caractere[<->] == argv[2]
                if(i == lenOld)
                {
                    break;
                }
            }
            
            // On ajoute le remplacement (argv[3])
            for(i = 0; i < lenNew; i++)
            {
                fputc(argv[3][i],destination);
            }

            caractere = fgetc(source);
            // On copie normalement jusqu'à la fin de la ligne
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
    }
    
    fclose(source);
    fclose(destination);

    sprintf(commande,"del %s",argv[1]);
    system(commande);
    sprintf(commande,"ren tempp %s",argv[1]);
    system(commande);
    
    printf("Le fichier \"%s\" a ete traite avec success!\n",argv[1]);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if(argc != 4 || argv[1][0] == '/')
    {
        afficheHelp();
        return EXIT_SUCCESS;
    }

    return replaceStringFile(argv);
}