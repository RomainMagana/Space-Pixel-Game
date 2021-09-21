#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>



#define ROW 9
#define COL 20

typedef struct
{
    int x; // Abscisses
    int y; // Ordonnées
}
Coordonnees;

int main()
{
    if (!SetConsoleOutputCP(65001)) printf ("ERREUR\n");

    Coordonnees joueur;
    Coordonnees missile;

    int touche;
    char tab2D[ROW][COL]={
                         "*------------------*",
                         "|   E E E E E E E  |",
                         "|   E E E E E E E  |",
                         "|     E E E E E    |",
                         "|                  |",
                         "|                  |",
                         "|                  |",
                         "|        J         |",
                         "*------------------*" };

    /* -------------------------------------------------------------------------- */
    /*                         INITIALISATION POSITION JOUEUR                     */
    /* -------------------------------------------------------------------------- */
    for ( int y = 0 ; y < ROW; y++ )
    {
        for ( int x = 0 ; x < COL; x++ )
        {
            switch (tab2D[y][x])
            {
                case 'J' : joueur.x = x;
                           joueur.y = y;
                           missile.x = x;
                           missile.y = y - 1;
            }
        }
    }

    printf (" x=%d et y=%d\n", joueur.x,joueur.y);
    printf (" x=%d et y=%d\n", missile.x,missile.y);


    do {


        /* -------------------------------------------------------------------------- */
        /*                             AFFICHER TABLEAU                               */
        /* -------------------------------------------------------------------------- */
        for ( int y = 0 ; y < ROW; y++ )
        {
            for ( int x = 0 ; x < COL; x++ )
            {
                if ( x == joueur.x && y == joueur.y )
                {
                   printf ("▲");
                }
                else if (x == missile.x && y == missile.y) {
                    printf ("•");
                }
                else {
                    switch (tab2D[y][x])
                    {
                        case  '|' : printf ("█"); break;
                        case  '-' : printf ("█"); break;
                        case  'E' : printf ("◊"); break;
                        case  '*' : printf ("█"); break;
                        case  '^' : printf ("•");break;
                        case  ' ' :
                        case  'X' :
                        case  'J' : printf (" "); break;
                    }
                }
            }

          printf ("\n");
         }

        printf ("\n");
        printf ("1 : GAUCHE\n");
        printf ("2 : TIRER\n");
        printf ("3 : DROITE\n");
        printf ("8 : EXIT\n");
        printf ("\n");

        printf ("Action : ");

        scanf ("%d", &touche);

        printf ("\n\n");


        /* ------------------------------------------------------------------------- */
        /*     GESTION DES TOUCHES + GESTION DE MURS + GESTION DE MISSILES ALIERS    */
        /* ------------------------------------------------------ ------------------ */

        switch ( touche )
        {
            //GAUCHE
            case 1 : if ( tab2D[joueur.y    ][joueur.x - 1] != '|' ) {
                        joueur.x--;
                        missile.x=joueur.x;
                     } break;

            //TIRER
            case 2 :  for(int y = ROW - 3; y > 0; y-- ) {
                        missile.y = y;
                        printf("%d", missile.y);

                        if( tab2D[missile.y][missile.x] == 'E') {
                            tab2D[missile.y][missile.x] = ' ';
                            missile.y = joueur.y -  1;
                            break;

                        } else if(tab2D[missile.y][missile.x] == '-'){
                            break;

                        }else {

                            }
                        missile.y = joueur.y -  1;
                    }
                    break;

            //DROITE
            case 3 : if ( tab2D[joueur.y    ][joueur.x + 1] != '|' ) {
                        joueur.x++;
                        missile.x = joueur.x;
                     } break;
        }

         for ( int y = 0 ; y < ROW; y++ )
         {
            for ( int x = 0 ; x < COL; x++ )
            {
                printf("%c", tab2D[y][x]);

                }
          printf ("\n");
         }

    }while(touche != 8);
    printf("END");


 return 0;
}
