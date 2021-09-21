#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include<time.h>

#define ROW 17
#define COL 26

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
    int nombrE;
    int totalE;
    int temp = 1;
    int laser = 1;
    char frappe;
    int score = 0;
    int vie = 5;
    int defeat = 0;
    int position_E = 2;
    char tab2D[ROW][COL]=
    {
        "*-------------------------*",
        "|   E E E E E E E E E E  |",
        "|                        |",
        "|   E E E E E E E E E E  |",
        "|                        |",
        "|   E E E E E E E E E E  |",
        "|                        |",
        "|                        |",
        "|                        |",
        "|                        |",
        "|                        |",
        "|                        |",
        "|                        |",
        "|                        |",
        "|                        |",
        "|            J           |",
        "*------------------------*"
    };

    /* -------------------------------------------------------------------------- */
    /*                         INITIALISATION POSITION JOUEUR                     */
    /* -------------------------------------------------------------------------- */
    for ( int y = 0 ; y < ROW; y++ )
    {
        for ( int x = 0 ; x < COL; x++ )
        {
            switch (tab2D[y][x])
            {
            case 'J' :
                joueur.x = x;
                joueur.y = y;
                break;
            case 'E' :
                nombrE++;
                totalE++;
                break;
            }
        }
    }

    /*
    printf("\n \n                Salutation soldat, \n \n \n ");
    Sleep(900);
    printf("     Vous devez vaincre les invaders de quelques manières que ce soit. \n \n \n");
    Sleep(2000);
    printf("      Votre survie ne dépend que de vous. \n \n \n \n");
    Sleep(2000);
    printf("                 Bonne chance.");
    Sleep(900);
    printf("\n \n \n \n Appuyer sur une touche pour commencer...");
    getch();
    */

    do
    {
        temp++;
        if(temp > 11)
        {
            temp = 0;
        }
        system("cls");
        laser++;
        temp++;
        int moove_E = 0;
        int speed = 10* nombrE / totalE;
        printf("SCORE : %d\n", score);

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

                else
                {
                    switch (tab2D[y][x])
                    {
                    case  '|' :
                        printf ("█");
                        break;
                    case  '-' :
                        printf ("█");
                        break;
                    case  'E' :
                        printf ("Æ");
                        break;
                    case  '*' :
                        printf ("█");
                        break;
                    case  '^' :
                        printf ("▪");
                        break;
                    case  'u' :
                        printf ("u");
                        break;
                    case  'v' :
                        printf ("v");
                        break;
                    case  'X' :
                        printf ("X");
                        break;
                    case  'x' :
                        printf ("x");
                        break;
                    case  ' ' :
                    case  'J' :
                        printf (" ");
                        break;
                    }
                }
            }

            printf ("\n");
        }

        printf("HP : ");
        switch (vie)
        {
        case  0 :
            printf (" ");
            break;
        case  1 :
            printf ("■■");
            break;
        case  2 :
            printf ("■■■■");
            break;
        case  3 :
            printf ("■■■■■■");
            break;
        case  4 :
            printf ("■■■■■■■■");
            break;
        case  5 :
            printf ("■■■■■■■■■■");
            break;
        }
        printf("\n");
        /* Cela devrait marcher, pourtant ce n'est pas le cas. Visiblement la boucle ne s'exécute qu'une seule fois.
        for (int y; y < vie; y++) {
            printf("■■");
            Sleep(200);
        }
        */

        printf ("\n");
        printf ("Q : GAUCHE\n");
        printf ("Z : TIRER\n");
        printf ("D : DROITE\n");
        printf ("P : EXIT\n");
        printf ("\n");

        printf ("Action : ");

        printf ("\n\n");

        /* ------------------------------------------------------------------------- */
        /*                                LASER ENNEMI                               */
        /* ------------------------------------------------------ ------------------ */
        //SUPPRIMER LASER
        for(int x=0; x<COL; x++)
        {
            if(tab2D[ROW-2][x] == 'v')
            {
                tab2D[ROW-2][x]=' ';
            }
        }

        //LASER DESCENDANT
        for(int y=ROW-2; y>0; y--)
        {
            for(int x=COL; x>0; x--)
            {
                if(tab2D[y][x]== 'v')
                {
                    tab2D[y][x]=' ';
                    tab2D[y+1][x]='v';
                }
            }
        }

        //SUPPRIMER IMPACT MISSILE
        for(int y=0; y <ROW; y++)
        {
            for(int x=0; x<COL; x++)
            {
                if(tab2D[y][x]== 'X')
                {
                    tab2D[y][x]=' ';
                }
                else if(tab2D[y][x]== 'x')
                {
                    tab2D[y][x]=' ';
                }
            }
        }

        //LASERS ALEATOIRES
        for(int y=0; y<ROW-2; y++)
        {
            for(int x=0; x < COL; x++)
            {
                if ( (rand() % 30) > 15 && (tab2D[y][x] == 'E') && (rand() % 30) > 28 && (tab2D[y+2][x] != 'E') && (tab2D[y+1][x] != '^'))
                {
                    tab2D[y+1][x] ='v';
                }
            }
        }

        /* ------------------------------------------------------------------------- */
        /*                                MISSILE ALIER                              */
        /* ------------------------------------------------------ ------------------ */

        //MISSILE IMPACT
        for(int y=0; y <ROW; y++)
        {
            for(int x=0; x<COL; x++)
            {
                if(tab2D[y][x]== '^' && tab2D[y-1][x]=='E' )
                {
                    tab2D[y-1][x]='X';
                    tab2D[y][x]=' ';
                    nombrE--;
                    score = score + 100;

                }
                else if (tab2D[y][x]=='^' && tab2D[y-1][x]=='v')
                {
                    tab2D[y-1][x]='x';
                    tab2D[y][x]=' ';
                }
            }
        }

        //SUPPRIMER MISSILE
        for(int x=0; x<COL; x++)
        {
            if(tab2D[1][x]== '^')
            {
                tab2D[1][x]=' ';
            }
        }


        //MISSILE MONTANT
        for(int y=0; y <ROW; y++)
        {
            for(int x=0; x<COL; x++)
            {
                if(tab2D[y][x]== '^')
                {
                    tab2D[y-1][x]='^';
                    tab2D[y][x]=' ';
                }
            }
        }

        //MISSILE IMPACTE JOUEUR
        for(int x=1; x < COL; x++)
        {
            if(tab2D[ROW-2][x] == 'v' && joueur.x == x )
            {
                Sleep(700);
                vie--;
            }
        }

        /* ------------------------------------------------------------------------- */
        /*                             MOUVEMENT ENNEMI                              */
        /* ------------------------------------------------------ ------------------ */

        //POSITION ENNEMI
        for (int y = 0; y < ROW; y ++)
        {
            //SI UN ENNEMI TOUCHE LE MUR DROIT
            if (tab2D[y][COL-2] == 'E')
            {
                position_E = 2;
                moove_E = 1;
                break;
            }
            //SI UN ENNEMI TOUCHE LE MUR GAUCHE
            if (tab2D[y][1] == 'E')
            {
                position_E = 1;
                moove_E = 1;
                break;
            }
        }

        //MOOVE ENNEMI
        if (temp % 7 == 0)
        {
            if(position_E == 2)
            {
                for (int x = 1; x < COL-1; x ++)
                {
                    for (int y = 1; y < ROW; y ++)
                    {
                        if (moove_E == 1 && (tab2D[y-1][x+1] == 'E'))
                        {
                            tab2D[y][x] = tab2D[y-1][x+1];
                            tab2D[y-1][x+1] = ' ';
                        }
                        else if (moove_E == 0 && (tab2D[y][x+1] == 'E'))
                        {
                            tab2D[y][x] = tab2D[y][x+1];
                            tab2D[y][x+1] = ' ';
                        }
                    }
                }
            }
            else
            {
                for (int x = COL-2; x > 0; x --)
                {
                    for (int y = 0; y < ROW; y ++)
                    {
                        if (moove_E == 1 && (tab2D[y-1][x-1] == 'E'))
                        {
                            tab2D[y][x] = tab2D[y-1][x-1];
                            tab2D[y-1][x-1] = ' ';
                        }
                        else if (moove_E == 0 && tab2D[y][x-1] == 'E')
                        {
                            tab2D[y][x] = tab2D[y][x-1];
                            tab2D[y][x-1] = ' ';
                        }
                    }
                }
            }
        }

        for (int x = 0; x < COL; x ++)
        {
            if (tab2D[ROW - 2][x] == 'E')
            {
                defeat = 1;
            }
        }




        /* ------------------------------------------------------------------------- */
        /*     GESTION DES TOUCHES + GESTION DE MURS + GESTION DE MISSILES ALIERS    */
        /* ------------------------------------------------------ ------------------ */

        if(_kbhit())
        {
            frappe=getch();
        }
        else
        {
            frappe = ' ';
        }


        switch ( frappe )
        {
        //GAUCHE
        case 'q' :
            if ( tab2D[joueur.y][joueur.x - 1] != '|' )
            {
                joueur.x--;
            }
            break;

        //TIRER
        case 'z' :
            if( laser >= 2)   //GERER 1 TIR SUR DEUX
            {
                tab2D[joueur.y-1][joueur.x] = '^';
                laser= 0;
            }
            break;

        //DROITE
        case 'd' :
            if (tab2D[joueur.y    ][joueur.x + 1] != '|' )
            {
                joueur.x++;
            }
            break;
        }

        Sleep(50);

        /* ------------------------------------------------------------------------- */
        /*                                  TEST DEV                                 */
        /* ------------------------------------------------------ ------------------ *

        for ( int y = 0 ; y < ROW; y++ ) {
            for ( int x = 0 ; x < COL; x++ ) {
                printf("%c", tab2D[y][x]);

            }
            printf ("\n");
        }
        */

    }
    while(vie > 0 && frappe != 'p' && nombrE > 0 && defeat != 1);
    printf("END");


    return 0;
}
