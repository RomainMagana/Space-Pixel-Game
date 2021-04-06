#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define ROW 20
#define COL 26

typedef struct
{
    int x; // Abscisses
    int y; // Ordonnées
} Coordonnees;

int main()
{
    if (!SetConsoleOutputCP(65001))
        printf("ERREUR\n");
    Coordonnees joueur;
    int nombrE;
    int temp = 1;
    int exit = 0;
    int laser = 1;
    char frappe;
    char touche;
    int score = 0;
    int vie = 5;
    int niveau_final = 50;
    int nmap = 0;
    int continuer = 0;
    int defeat = 0;

    int position_E = 2;
    char tab2D[4][ROW][COL] =
        {
            {"*-------------------------*",
             "|                        |",
             "|       E E E E E E      |",
             "|       E E E E E E      |",
             "|       B B B B B B      |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|                        |",
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
             "*------------------------*"},
            {"*-------------------------*",
             "|    E E E E   E E E E   |",
             "|    E E E E E E E E E   |",
             "|      E E E E E E E     |",
             "|        E E E E E       |",
             "|         E B B E        |",
             "|           B B          |",
             "|            B           |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|    __            __    |",
             "|   liil          liil   |",
             "|                        |",
             "|            J           |",
             "*------------------------*"},
            {"*------------------------*",
             "|     E E E E E E E E    |",
             "|                        |",
             "|     E E E E E E E E    |",
             "|                        |",
             "|     B B B B B B B B    |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|    __     __     __    |",
             "|   liil   liil   liil   |",
             "|                        |",
             "|            J           |",
             "*------------------------*"},
            {"*------------------------*",
             "|                        |",
             "|       ++      ++       |",
             "|      ++        ++      |",
             "|     ++          ++     |",
             "|    ++    ++++    ++    |",
             "|   ++++++++++++++++++   |",
             "|     ++   ++++   ++     |",
             "|     ++    ++    ++     |",
             "|           ++           |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|                        |",
             "|   __      __      __   |",
             "|  liil    liil    liil  |",
             "|                        |",
             "|            J           |",
             "*------------------------*"}};

    /* -------------------------------------------------------------------------- */
    /*                         INITIALISATION POSITION JOUEUR                     */
    /* -------------------------------------------------------------------------- */
    for (int y = 0; y < ROW; y++)
    {
        for (int x = 0; x < COL; x++)
        {
            switch (tab2D[nmap][y][x])
            {
            case 'J':
                joueur.x = x;
                joueur.y = y;
                break;
            }
        }
    }

    printf("\n \n                Salutation soldat, \n \n \n ");
    Sleep(900);
    printf("     Vous devez vaincre les envahisseurs de quelques manières que ce soit. \n \n \n");
    Sleep(2000);
    printf("      Votre survie ne dépend que de vous. \n \n \n \n");
    Sleep(2000);
    printf("                 Bonne chance.");
    Sleep(900);
    printf("\n \n \n \n Appuyer sur une touche pour commencer...");
    getch();

    do
    {
        nombrE = 0;
        temp++;
        if (temp > 11)
        {
            temp = 0;
        }
        system("cls");
        laser++;
        temp++;
        int moove_E = 0;
        printf("SCORE : %d", score);
        printf("     NIVEAU : %d\n", nmap + 1);

        /* -------------------------------------------------------------------------- */
        /*                             AFFICHER TABLEAU                               */
        /* -------------------------------------------------------------------------- */
        for (int y = 0; y < ROW; y++)
        {
            for (int x = 0; x < COL; x++)
            {
                if (x == joueur.x && y == joueur.y)
                {
                    printf("▲");
                }

                else
                {
                    switch (tab2D[nmap][y][x])
                    {
                    // BUNKER
                    case '|':
                        printf("█");
                        break;
                    case '-':
                        printf("█");
                        break;
                    case 'l':
                        printf("‖");
                        break;
                    case 'L':
                        printf("|");
                        break;
                    case '_':
                        printf("‗");
                        break;
                    case 'i':
                        printf("⁃");
                        break;
                    case 'I':
                        printf("-");
                        break;
                    case 'H':
                        printf("_");
                        break;
                    // ENNEMIS
                    case 'B':
                        printf("Ӂ");
                        break;
                    case 'E':
                        printf("Ѫ");
                        nombrE++;
                        break;
                    case '+':
                        printf("•");
                        nombrE++;
                        break;
                    //MAP
                    case '*':
                        printf("█");
                        break;
                    case '^':
                        printf("▪");
                        break;
                    case 'v':
                        printf("ѽ");
                        break;
                    case 'X':
                        printf("Ӿ");
                        break;
                    case 'x':
                        printf("ӿ");
                        break;
                    case ' ':
                    case 'J':
                        printf(" ");
                        break;
                    }
                }
            }

            printf("\n");
        }

        printf("HP : ");
        switch (vie)
        {
        case 0:
            printf(" ");
            break;
        case 1:
            printf("■■");
            break;
        case 2:
            printf("■■■■");
            break;
        case 3:
            printf("■■■■■■");
            break;
        case 4:
            printf("■■■■■■■■");
            break;
        case 5:
            printf("■■■■■■■■■■");
            break;
        }
        printf("\n");
        /* Cela devrait marcher, pourtant ce n'est pas le cas. Visiblement la boucle ne s'exécute qu'une seule fois.
        for (int y; y < vie; y++) {
            printf("■■");
            Sleep(200);
        }
        */

        printf("\n");
        printf("Q : GAUCHE\n");
        printf("Z : TIRER\n");
        printf("D : DROITE\n");
        printf("P : EXIT\n");
        printf("\n");

        /* ------------------------------------------------------------------------- */
        /*                                LASER ENNEMI                               */
        /* ------------------------------------------------------ ------------------ */
        //SUPPRIMER LASER
        for (int x = 0; x < COL; x++)
        {
            if (tab2D[nmap][ROW - 2][x] == 'v')
            {
                tab2D[nmap][ROW - 2][x] = ' ';
            }
        }

        //SUPPRIMER IMPACT MISSILE
        for (int y = 0; y < ROW; y++)
        {
            for (int x = 0; x < COL; x++)
            {
                if (tab2D[nmap][y][x] == 'X')
                {
                    tab2D[nmap][y][x] = ' ';
                }
                else if (tab2D[nmap][y][x] == 'x')
                {
                    tab2D[nmap][y][x] = ' ';
                }
            }
        }

        //LASER DESCENDANT BUNCKER / ENNEMI / ENNEMI BOOSTED
        for (int y = ROW - 2; y > 0; y--)
        {
            for (int x = COL; x > 0; x--)
            {
                if (tab2D[nmap][y][x] == 'v')
                {
                    if (tab2D[nmap][y + 1][x] != 'l' && tab2D[nmap][y + 1][x] != 'i' && tab2D[nmap][y + 1][x] != '_' && tab2D[nmap][y + 1][x] != 'L' && tab2D[nmap][y + 1][x] != 'H' && tab2D[nmap][y + 1][x] != 'I' && tab2D[nmap][y + 1][x] != 'B' && tab2D[nmap][y + 1][x] != '+')
                    {
                        tab2D[nmap][y][x] = ' ';
                        tab2D[nmap][y + 1][x] = 'v';
                    }
                    else if (tab2D[nmap][y + 1][x] == '_')
                    {
                        tab2D[nmap][y][x] = ' ';
                        tab2D[nmap][y + 1][x] = 'H';
                    }
                    else if (tab2D[nmap][y + 1][x] == 'l')
                    {
                        tab2D[nmap][y][x] = ' ';
                        tab2D[nmap][y + 1][x] = 'L';
                    }
                    else if (tab2D[nmap][y + 1][x] == 'i')
                    {
                        tab2D[nmap][y][x] = ' ';
                        tab2D[nmap][y + 1][x] = 'I';
                    }
                    else if (tab2D[nmap][y + 1][x] == '+')
                    {
                        tab2D[nmap][y][x] = ' ';
                    }
                    else
                    {
                        tab2D[nmap][y][x] = ' ';
                        tab2D[nmap][y + 1][x] = ' ';
                    }
                }
            }
        }

        //LASERS ALEATOIRES
        for (int y = 0; y < ROW - 2; y++)
        {
            for (int x = 0; x < COL; x++)
            {
                if ((rand() % 30) > 15 && (tab2D[nmap][y][x] == 'E' || tab2D[nmap][y][x] == 'B' || tab2D[nmap][y][x] == '+') && (rand() % 30) > 28 && (tab2D[nmap][y + 2][x] != 'E' && tab2D[nmap][y + 2][x] != 'B') && tab2D[nmap][y + 1][x] != '+' && tab2D[nmap][y + 2][x] != '+' && (tab2D[nmap][y + 1][x] != 'E') && (tab2D[nmap][y + 1][x] != '^'))
                {
                    tab2D[nmap][y + 1][x] = 'v';
                }
            }
        }

        /* ------------------------------------------------------------------------- */
        /*                                MISSILE ALIER                              */
        /* ------------------------------------------------------ ------------------ */

        //MISSILE IMPACT BUNKER / ENNEMIS / LASERS
        for (int y = 0; y < ROW; y++)
        {
            for (int x = 0; x < COL; x++)
            {
                if (tab2D[nmap][y][x] == '^' && (tab2D[nmap][y - 1][x] == 'E'))
                {
                    tab2D[nmap][y][x] = ' ';
                    tab2D[nmap][y - 1][x] = 'X';
                    nombrE--;
                    score = score + 100;
                }
                else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y - 1][x] == 'v')
                {
                    tab2D[nmap][y][x] = ' ';
                    tab2D[nmap][y - 1][x] = 'x';
                }
                else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y - 1][x] == 'B')
                {
                    tab2D[nmap][y][x] = ' ';
                    tab2D[nmap][y - 1][x] = 'E';
                }
                else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y - 1][x] == 'i')
                {
                    tab2D[nmap][y][x] = ' ';
                    tab2D[nmap][y - 1][x] = 'I';
                }
                else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y - 1][x] == 'l')
                {
                    tab2D[nmap][y][x] = ' ';
                    tab2D[nmap][y - 1][x] = 'L';
                }
                else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y - 1][x] == '_')
                {
                    tab2D[nmap][y][x] = ' ';
                    tab2D[nmap][y - 1][x] = 'H';
                }
                else if (tab2D[nmap][y][x] == '^' && (tab2D[nmap][y - 1][x] == 'L' || tab2D[nmap][y - 1][x] == 'H' || tab2D[nmap][y - 1][x] == 'I'))
                {
                    tab2D[nmap][y][x] = ' ';
                    tab2D[nmap][y - 1][x] = ' ';
                }
                else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y - 1][x] == '+' && nmap == 3)
                {
                    tab2D[nmap][y][x] = ' ';
                    niveau_final--;
                    score += 100;
                }
            }
        }

        //SUPPRIMER MISSILE
        for (int x = 0; x < COL; x++)
        {
            if (tab2D[nmap][1][x] == '^')
            {
                tab2D[nmap][1][x] = ' ';
            }
        }

        //MISSILE MONTANT
        for (int y = 0; y < ROW; y++)
        {
            for (int x = 0; x < COL; x++)
            {
                if (tab2D[nmap][y][x] == '^')
                {
                    tab2D[nmap][y - 1][x] = '^';
                    tab2D[nmap][y][x] = ' ';
                }
            }
        }

        //LASER IMPACTE JOUEUR
        for (int x = 1; x < COL; x++)
        {
            if (tab2D[nmap][ROW - 2][x] == 'v' && joueur.x == x)
            {
                Sleep(700);
                vie--;
            }
        }

        /* ------------------------------------------------------------------------- */
        /*                             MOUVEMENT ENNEMI                              */
        /* ------------------------------------------------------ ------------------ */

        //POSITION ENNEMI
        for (int y = 0; y < ROW; y++)
        {
            //SI UN ENNEMI TOUCHE LE MUR DROIT
            if (tab2D[nmap][y][COL - 2] == 'E' || tab2D[nmap][y][COL - 2] == 'B')
            {
                position_E = 2;
                moove_E = 1;
                break;
            }
            //SI UN ENNEMI TOUCHE LE MUR GAUCHE
            if (tab2D[nmap][y][1] == 'E' || tab2D[nmap][y][1] == 'B')
            {
                position_E = 1;
                moove_E = 1;
                break;
            }
        }

        //MOOVE ENNEMI
        if (temp % 7 == 0 && nmap != 3)
        {
            if (position_E == 2)
            {
                for (int x = 1; x < COL - 1; x++)
                {
                    for (int y = 1; y < ROW; y++)
                    {
                        if (moove_E == 1 && (tab2D[nmap][y - 1][x + 1] == 'E') || (tab2D[nmap][y - 1][x + 1] == 'B'))
                        {
                            tab2D[nmap][y][x] = tab2D[nmap][y - 1][x + 1];
                            tab2D[nmap][y - 1][x + 1] = ' ';
                        }
                        else if (moove_E == 0 && (tab2D[nmap][y][x + 1] == 'E' || tab2D[nmap][y][x + 1] == 'B'))
                        {
                            tab2D[nmap][y][x] = tab2D[nmap][y][x + 1];
                            tab2D[nmap][y][x + 1] = ' ';
                        }
                    }
                }
            }
            else
            {
                for (int x = COL - 2; x > 0; x--)
                {
                    for (int y = 0; y < ROW; y++)
                    {
                        if (moove_E == 1 && (tab2D[nmap][y - 1][x - 1] == 'E' || tab2D[nmap][y - 1][x - 1] == 'B'))
                        {
                            tab2D[nmap][y][x] = tab2D[nmap][y - 1][x - 1];
                            tab2D[nmap][y - 1][x - 1] = ' ';
                        }
                        else if (moove_E == 0 && (tab2D[nmap][y][x - 1] == 'E' || tab2D[nmap][y][x - 1] == 'B'))
                        {
                            tab2D[nmap][y][x] = tab2D[nmap][y][x - 1];
                            tab2D[nmap][y][x - 1] = ' ';
                        }
                    }
                }
            }
        }

        for (int x = 0; x < COL; x++)
        {
            if (tab2D[nmap][ROW - 2][x] == 'E' || tab2D[nmap][ROW - 2][x] == 'B')
            {
                defeat = 1;
            }
        }

        if (nombrE == 0)
        {
            if (nmap == 0)
            {
                nmap = 1;
            }
            else if (nmap == 1)
            {
                nmap = 2;
            }
            else
            {
                nmap = 3;
            }
        }

        /* ------------------------------------------------------------------------- */
        /*     GESTION DES TOUCHES + GESTION DE MURS + GESTION DE MISSILES ALIERS    */
        /* ------------------------------------------------------ ------------------ */

        if (_kbhit())
        {
            frappe = getch();
        }
        else
        {
            frappe = ' ';
        }

        switch (frappe)
        {
        //GAUCHE
        case 'q':
            if (tab2D[nmap][joueur.y][joueur.x - 1] != '|')
            {
                joueur.x--;
            }
            break;

        //TIRER
        case 'z':
            if (laser >= 2) //GERER 1 TIR SUR DEUX
            {
                tab2D[nmap][joueur.y - 1][joueur.x] = '^';
                laser = 0;
            }
            break;

        //DROITE
        case 'd':
            if (tab2D[nmap][joueur.y][joueur.x + 1] != '|')
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

    } while (vie > 0 && frappe != 'p' && defeat != 1 && niveau_final != 0);

    if (niveau_final == 0)
    {
        printf("\n \n                Bien joué soldat ! \n \n \n ");
        Sleep(900);
        printf("     Vous avez vaincu les envahisseurs !. \n \n \n");
        Sleep(2000);
        printf("      SCORE : %d. \n \n \n \n", score);
        Sleep(2000);
        printf("                Reposez vous bien, ce n'est que le début.");
        Sleep(900);
        printf("\n \n \n \n Appuyer sur une touche pour quiter...");
        getch();
    }
    else if (vie == 0)
    {
        printf("\n \n                STAGE : %d TERMINE ! \n \n \n ", nmap);
        Sleep(900);
        printf("      SCORE : %d. \n \n \n \n", score);
        Sleep(2000);
        printf("                Reposez vous bien, ce n'est que le début.");
        Sleep(2000);
        printf("\n \n \n \n Appuyer sur une touche pour quiter...");
        getch();
    }
    else if (frappe == 'p')
    {
        printf("\n \n                STAGE : %d TERMINE ! \n \n \n ", nmap);
        Sleep(900);
        printf("      SCORE : %d. \n \n \n \n", score);
        Sleep(2000);
        printf("                Reposez vous bien, ce n'est que le début.");
        Sleep(2000);
        printf("\n \n \n \n Appuyer sur une touche pour quiter...");
        getch();
    }
    else if (defeat == 1)
    {
        printf("\n \n                STAGE : %d TERMINE ! \n \n \n ", nmap);
        Sleep(900);
        printf("      SCORE : %d. \n \n \n \n", score);
        Sleep(2000);
        printf("                Reposez vous bien, ce n'est que le début.");
        Sleep(2000);
        printf("\n \n \n \n Appuyer sur une touche pour quiter...");
        touche = getch();
    }

    //Je personnaliserai les messages dans un second temps.

    return 0;
}
