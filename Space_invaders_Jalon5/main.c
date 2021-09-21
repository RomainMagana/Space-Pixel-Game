#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <windows.h>


#include <stdio.h>


#define ROW 24
#define COL 26
#define E_total_1 18

typedef struct
{
    int x; // Abscisses
    int y; // Ordonnées
} Coordonnees;


void afficherSurface ( int           x,
                       int           y,
                       SDL_Renderer* renderer,
                       SDL_Surface*  surface  )
{
    if ( surface )
    {
        SDL_Texture* image = SDL_CreateTextureFromSurface ( renderer, surface );

        if ( image )
        {
            SDL_SetRenderTarget ( renderer, image );

            SDL_Rect r;

            r.x = x;
            r.y = y;

            SDL_QueryTexture ( image, NULL, NULL, &(r.w), &(r.h));

            //printf ("On rend la surface dans le rectangle %d %d %d %d\n", r.x, r.y, r.w, r.h);

            SDL_RenderCopy ( renderer, image, NULL, &r);

            SDL_SetRenderTarget ( renderer, NULL );

            SDL_DestroyTexture (image);
        }
        else
        {
            fprintf (stderr, "Erreur de creation de la texture\n");
        }
    }
}

void afficherTexte ( int           x,
                     int           y,
                     SDL_Renderer* renderer,
                     char*         fichierPolice,
                     char*         texte         )
{
    TTF_Font* police = TTF_OpenFont ( fichierPolice, 14);

    if ( police )
    {
        SDL_Color couleurNoire = {247, 222, 188};

        SDL_Surface* surface_texte = TTF_RenderText_Blended ( police, texte, couleurNoire );

        afficherSurface ( x,
                          y,
                          renderer,
                          surface_texte );

        SDL_FreeSurface ( surface_texte );

        TTF_CloseFont ( police );
    }
    else
    {
        fprintf (stderr, "Erreur de chargement de la police %s\n", fichierPolice);
    }
}

void afficherTexteBig ( int           x,
                        int           y,
                        SDL_Renderer* renderer,
                        char*         fichierPolice,
                        char*         texte         )
{
    TTF_Font* police = TTF_OpenFont ( fichierPolice, 24);

    if ( police )
    {
        SDL_Color couleurNoire = {247, 222, 188};

        SDL_Surface* surface_texte = TTF_RenderText_Blended ( police, texte, couleurNoire );

        afficherSurface ( x,
                          y,
                          renderer,
                          surface_texte );

        SDL_FreeSurface ( surface_texte );

        TTF_CloseFont ( police );
    }
    else
    {
        fprintf (stderr, "Erreur de chargement de la police %s\n", fichierPolice);
    }
}


void afficherImage ( int           x,
                     int           y,
                     SDL_Renderer* renderer,
                     char*         nomFichier )
{
    SDL_Surface* surface_image = IMG_Load (nomFichier);

    if ( surface_image )
    {
        afficherSurface ( x,
                          y,
                          renderer,
                          surface_image );

        SDL_FreeSurface (surface_image);
    }
    else
    {
        fprintf (stderr, "Erreur de chargement de l'image %s\n", nomFichier);
    }
}

int main(int argc, char *argv[])
{
    int quit = 0;
    int skin_tab[9] = {1,0,0,0,0,0,0,0,0};
    //if (!SetConsoleOutputCP(65001))
    //   printf("ERREUR\n");

    if ( SDL_Init (SDL_INIT_VIDEO) != 0 )
    {
        fprintf (stderr, "Erreur d'initialisation du m�canisme SDL : %s\n", SDL_GetError() );

        return EXIT_FAILURE;
    }

    TTF_Init();

    SDL_Window* fenetre = SDL_CreateWindow ( "SDL 2.0.14 - Exemple 06",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          780,
                          700,
                          SDL_WINDOW_SHOWN          );

    if ( fenetre == NULL )
    {
        fprintf (stderr, "Erreur de cr�ation de la fen�tre : %s\n",SDL_GetError());

        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer ( fenetre, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;
    do
    {
        Coordonnees joueur;
        int nombrE;
        int temp = 1;
        char stage_affiche[50];
        char score_affiche[50];
        int rejouer = 0;
        int play = 0;
        int rule = 0;
        int fin = 0;
        int pause = 0;
        int skin = 0;
        int laser = 1;
        int score = 0;
        int vie = 6;
        int niveau_final = 100;
        int nmap = 3;
        int defeat = 0;
        int temp2;
        int sdl_Right = 0;
        int sdl_Left = 0;
        int sdl_Up = 0;

        int position_E = 2;
        char tab2D[4][ROW][COL] =
        {
            {

                "*------------------------*",
                "|                        |",
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
                "|                        |",
                "|   w_              w_   |",
                "|  tmil            tmil  |",
                "|                        |",
                "|                        |",
                "|                        |",
                "|            J           |",
                "*------------------------*"
            },
            {
                "*-------------------------*",
                "|                        |",
                "|     E E E E E E E E    |",
                "|                        |",
                "|     F F F F F F F F    |",
                "|                        |",
                "|     E E E E E E E E    |",
                "|                        |",
                "|     F F F F F F F F    |",
                "|                        |",
                "|     B B B B B B B B    |",
                "|     B B B B B B B B    |",
                "|                        |",
                "|                        |",
                "|                        |",
                "|                        |",
                "|   w_              w_   |",
                "|  tmil            tmil  |",
                "|                        |",
                "|                        |",
                "|                        |",
                "|                        |",
                "|            J           |",
                "*------------------------*"
            },
            {
                "*-------------------------*",
                "|                        |",
                "|     B B B B B B B B B  |",
                "|     B F E F E F E F B  |",
                "|     B E F E F E F E B  |",
                "|     B F E F E F E F B  |",
                "|     B E F E F E F E B  |",
                "|     B F E F E F E F B  |",
                "|     B E F E F E F E B  |",
                "|     B B B B B B B B B  |",
                "|     B B B B B B B B B  |",
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
                "*------------------------*"
            },
            {
                "*------------------------*",
                "|                        |",
                "|                        |",
                "|                        |",
                "|   ++++++++++++++++++   |",
                "|   ++++++++++++++++++   |",
                "|   ++++++++S+++++++++   |",
                "|   ++++++++++++++++++   |",
                "|   ++++++++++++++++++   |",
                "|    ++++++++++++++++    |",
                "|       ++++++++++       |",
                "|        ++++++++        |",
                "|         ++++++         |",
                "|                        |",
                "|                        |",
                "|                        |",
                "|                        |",
                "|   w_              w_   |",
                "|  tmil            tmil  |",
                "|                        |",
                "|                        |",
                "|                        |",
                "|            J           |",
                "*------------------------*"
            }
        };

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
        do
        {
            do
            {
                afficherImage (-10, 0, renderer, "./BMP/Debut.bmp");

                SDL_WaitEvent (&event);

                switch ( event.type )
                {
                case SDL_MOUSEBUTTONDOWN  :
                    switch ( event.button.button )
                    {
                    case SDL_BUTTON_LMASK  :
                        if(event.button.x > 203 && event.button.x < 306 && event.button.y > 500 && event.button.y < 549)
                        {
                            rule = 1;
                            break;
                        }
                        if(event.button.x > 337 && event.button.x < 438 && event.button.y > 500 && event.button.y < 549)
                        {
                            play = 1;
                            break;
                        }
                        if(event.button.x > 469 && event.button.x < 572 && event.button.y > 500 && event.button.y < 549)
                        {
                            skin = 1;
                            break;
                        }
                        break;
                    }
                    break;

                case SDL_QUIT          :
                    quit = 1;
                    break;
                }

                SDL_RenderPresent(renderer);
                SDL_RenderClear(renderer);
            }
            while(rule != 1 && skin != 1 && play != 1 && quit == 0);

            while(rule == 1 && play != 1 && quit == 0)
            {
                afficherImage (0, 0, renderer, "./BMP/Rule.bmp");
                SDL_WaitEvent (&event);

                switch ( event.type )
                {
                case SDL_MOUSEBUTTONDOWN  :
                    switch ( event.button.button )
                    {
                    case SDL_BUTTON_LMASK  :
                        if(event.button.x > 37 && event.button.x < 66 && event.button.y > 33 && event.button.y < 63)
                        {
                            rule = 0;
                        }
                    }
                    break;
                case SDL_QUIT          :
                    quit = 1;
                }
                SDL_RenderPresent(renderer);
                SDL_RenderClear(renderer);
            }

            while(skin >= 1 && play != 1 && quit !=1)
            {
                for (int i = 0; i <= 8; i++)
                {
                    if(skin_tab[i] == 1)
                    {
                        switch(skin)
                        {
                        case 1:
                            afficherImage (0, 0, renderer, "./BMP/Skin/page_1.bmp");
                            switch(i)
                            {
                            case 0 :
                                afficherImage (0, 0, renderer, "./BMP/Skin/skin_1.bmp");
                                break;
                            case 1 :
                                afficherImage (0, 0, renderer, "./BMP/Skin/skin_2.bmp");
                                break;
                            case 2 :
                                afficherImage (0, 0, renderer, "./BMP/Skin/skin_3.bmp");
                                break;
                            };
                            break;
                        case 2:

                            afficherImage (0, 0, renderer, "./BMP/Skin/page_2.bmp");
                            switch(i)
                            {
                            case 3 :
                                afficherImage (0, 0, renderer, "./BMP/Skin/skin_4.bmp");
                                break;
                            case 4 :
                                afficherImage (0, 0, renderer, "./BMP/Skin/skin_5.bmp");
                                break;
                            case 5 :
                                afficherImage (0, 0, renderer, "./BMP/Skin/skin_6.bmp");
                                break;
                            };
                            break;
                        case 3:
                            afficherImage (0, 0, renderer, "./BMP/Skin/page_3.bmp");
                            switch(i)
                            {
                            case 6 :
                                afficherImage (0, 0, renderer, "./BMP/Skin/skin_7.bmp");
                                break;
                            case 7 :
                                afficherImage (0, 0, renderer, "./BMP/Skin/skin_8.bmp");
                                break;
                            case 8 :
                                afficherImage (0, 0, renderer, "./BMP/Skin/skin_9.bmp");
                                break;
                            };
                            break;
                        }
                    }
                }

                SDL_WaitEvent (&event);

                switch ( event.type )
                {
                case SDL_MOUSEBUTTONDOWN  :
                    switch ( event.button.button )
                    {
                    case SDL_BUTTON_LMASK  :
                        if(event.button.x > 37 && event.button.x < 66 && event.button.y > 33 && event.button.y < 63)
                        {
                            skin = 0;
                        }

                        if(event.button.x >= 690 && event.button.x <= 739 && event.button.y >= 591 && event.button.y <= 640)
                        {
                            if (skin == 2)
                            {
                                skin = 3;
                            }
                            else if(skin == 1)
                            {
                                skin = 2;
                            }
                        }

                        if(event.button.x >= 59 && event.button.x <= 109 && event.button.y >= 591 && event.button.y <= 640)
                        {
                            if (skin == 2)
                            {
                                skin = 1;
                            }
                            else if(skin == 3)
                            {
                                skin = 2;
                            }
                        }

                        if(event.button.x >= 66 && event.button.x <= 269 && event.button.y >= 243 && event.button.y <= 551)
                        {
                            for (int i = 0; i <= 8; i++)
                            {
                                skin_tab[i] = 0;
                            }
                            if(skin == 1)
                            {
                                skin_tab[0] = 1;
                            }
                            if(skin == 2)
                            {
                                skin_tab[3] = 1;
                            }
                            if(skin == 3)
                            {
                                skin_tab[6] = 1;
                            }
                        }

                        if(event.button.x >= 300 && event.button.x <= 501 && event.button.y >= 243 && event.button.y <= 551)
                        {
                            for (int i = 0; i <= 8; i++)
                            {
                                skin_tab[i] = 0;
                            }
                            if(skin == 1)
                            {
                                skin_tab[1] = 1;
                            }
                            if(skin == 2)
                            {
                                skin_tab[4] = 1;
                            }
                            if(skin == 3)
                            {
                                skin_tab[7] = 1;
                            }
                        }

                        if(event.button.x >= 530 && event.button.x <= 733 && event.button.y >= 243 && event.button.y <= 551)
                        {
                            for (int i = 0; i <= 8; i++)
                            {
                                skin_tab[i] = 0;
                            }
                            if(skin == 1)
                            {
                                skin_tab[2] = 1;
                            }
                            if(skin == 2)
                            {
                                skin_tab[5] = 1;
                            }
                            if(skin == 3)
                            {
                                skin_tab[8] = 1;
                            }
                        }
                    }
                    break;

                case SDL_QUIT          :
                    quit = 1;
                }

                //  printf (" - x         = %d\n",  event.button.x);
                //  printf (" - y         = %d\n",  event.button.y);
                SDL_RenderPresent(renderer);
                SDL_RenderClear(renderer);
            }
            SDL_RenderClear(renderer);
        }
        while(play != 1 && quit !=1);

        SDL_RenderClear(renderer);

        do
        {
            fin = 0;
            nombrE = 0;
            temp++;
            if (temp > 20)
            {
                temp = 0;
            }
            temp2++;
            if (temp2 > 1)
            {
                temp2 = 0;
            }
            laser++;
            int moove_E = 0;

            afficherImage (0, 0, renderer, "./BMP/background.bmp");

            sprintf(stage_affiche, "STAGE : %d", nmap+1);
            sprintf(score_affiche, "POINTS : %d", score);
            //printf("%s\n", score_affiche);
            //printf("%s\n", stage_affiche);
            afficherTexte ( 293, 24, renderer, "polices/PressStart2P.ttf", score_affiche);
            afficherTexte ( 513, 24, renderer, "polices/PressStart2P.ttf", stage_affiche);



            /* -------------------------------------------------------------------------- */
            /*                             AFFICHER TABLEAU                               */
            /* -------------------------------------------------------------------------- */
            for (int y = 0; y < ROW; y++)
            {
                for (int x = 0; x < COL; x++)
                {
                    if (x == joueur.x && y == joueur.y)
                    {
                        //printf("▲");
                        for (int i = 0; i <= 8; i++)
                        {
                            if(skin_tab[i] == 1)
                            {
                                switch(i)
                                {
                                case 0:
                                    afficherImage (x*30-15, y*30-60, renderer, "./BMP/Fusee/Fusee_1.bmp");
                                    break;
                                case 1:
                                    afficherImage (x*30-15, y*30-60, renderer, "./BMP/Fusee/Fusee_2.bmp");
                                    break;
                                case 2:
                                    afficherImage (x*30-15, y*30-60, renderer, "./BMP/Fusee/Fusee_3.bmp");
                                    break;
                                case 3:
                                    afficherImage (x*30-15, y*30-60, renderer, "./BMP/Fusee/Fusee_4.bmp");
                                    break;
                                case 4:
                                    afficherImage (x*30-15, y*30-60, renderer, "./BMP/Fusee/Fusee_5.bmp");
                                    break;
                                case 5:
                                    afficherImage (x*30-15, y*30-60, renderer, "./BMP/Fusee/Fusee_6.bmp");
                                    break;
                                case 6:
                                    afficherImage (x*30-15, y*30-60, renderer, "./BMP/Fusee/Fusee_7.bmp");
                                    break;
                                case 7:
                                    afficherImage (x*30-15, y*30-60, renderer, "./BMP/Fusee/Fusee_8.bmp");
                                    break;
                                case 8:
                                    afficherImage (x*30-15, y*30-60, renderer, "./BMP/Fusee/Fusee_9.bmp");
                                    break;
                                }

                            }
                        }
                    }

                    else
                    {
                        switch (tab2D[nmap][y][x])
                        {
                        case '|':
                            //printf("█");
                            break;
                        case '-':
                            //printf("█");
                            break;
                        // BUNKER
                        case 'l':
                            //printf("‖");
                            afficherImage (x*30-6, y*30-32, renderer, "./BMP/Buncker/3.bmp");
                            break;
                        case 'L':
                            //printf("|");
                            afficherImage (x*30-6, y*30-32, renderer, "./BMP/Buncker/3.bmp");
                            break;

                        case '_':
                            //printf("‗");
                            afficherImage (x*30-7, y*30-35, renderer, "./BMP/Buncker/5.bmp");
                            break;
                        case 'H':
                            //printf("_");
                            afficherImage (x*30-7, y*30-35, renderer, "./BMP/Buncker/5.bmp");
                            break;

                        case 'i':
                            //printf("⁃");
                            afficherImage (x*30-10, y*30, renderer, "./BMP/Buncker/2.bmp");
                            break;
                        case 'I':
                            //printf("-");
                            afficherImage (x*30-10, y*30, renderer, "./BMP/Buncker/2.bmp");
                            break;

                        case 't':
                            //printf("‖");
                            afficherImage (x*30-5, y*30-32, renderer, "./BMP/Buncker/4.bmp");
                            break;
                        case 'T':
                            //printf("|");
                            afficherImage (x*30-5, y*30-32, renderer, "./BMP/Buncker/4.bmp");
                            break;

                        case 'w':
                            //printf("‗");
                            afficherImage (x*30-7, y*30-35, renderer, "./BMP/Buncker/6.bmp");
                            break;
                        case 'W':
                            //printf("_");
                            afficherImage (x*30-7, y*30-35, renderer, "./BMP/Buncker/6.bmp");
                            break;

                        case 'm':
                            //printf("⁃");
                            afficherImage (x*30-6, y*30, renderer, "./BMP/Buncker/1.bmp");
                            break;
                        case 'M':
                            //printf("-");
                            afficherImage (x*30-6, y*30, renderer, "./BMP/Buncker/1.bmp");
                            break;
                        // ENNEMIS
                        case 'B':
                            //printf("Ӂ");
                            afficherImage (x*30, y*30, renderer, "./BMP/Aliens/soucoupe.bmp");
                            break;
                        case 'E':
                            //printf("Ѫ");
                            afficherImage (x*30, y*30, renderer, "./BMP/Aliens/aliens_blue.bmp");
                            nombrE++;
                            break;
                        case 'F':
                            //printf("Ѫ");
                            afficherImage (x*30, y*30, renderer, "./BMP/Aliens/aliens_liane.bmp");
                            nombrE++;
                            break;
                        case '+':
                            //printf("•");
                            nombrE++;
                            break;
                        case 'S':
                            afficherImage (x*30-245, y*30-120, renderer, "./BMP/Aliens/bigboss.bmp");
                        //MAP
                        case '*':
                            //printf("█");
                            break;
                        case '^':
                            //printf("▪");
                            afficherImage (x*30+16, y*30, renderer, "./BMP/Laser2.bmp");
                            break;
                        case 'v':
                            //printf("ѽ");
                            afficherImage (x*30+6, y*30, renderer, "./BMP/path16-1.bmp");
                            break;
                        case 'X':
                            //printf("Ӿ");
                            afficherImage (x*30, y*30, renderer, "./BMP/explosion.bmp");
                            break;
                        case 'x':
                            //printf("ӿ");
                            afficherImage (x*30, y*30, renderer, "./BMP/explosion.bmp");
                            break;
                        case ' ':
                        case 'J':
                            //printf(" ");
                            break;
                        }
                    }
                }

                //printf("\n");
            }

            //printf("HP : ");
            switch (vie)
            {
            case 0:
                //printf(" ");
                break;
            case 1:
                //printf("■■");
                afficherImage (19,17, renderer, "./BMP/Life/life_low.bmp");
                break;
            case 2:
                //printf("■■");
                afficherImage (19,17, renderer, "./BMP/Life/life_2-4.bmp");
                break;
            case 3:
                //printf("■■■■");
                afficherImage (19,17, renderer, "./BMP/Life/life_mid.bmp");
                break;
            case 4:
                //printf("■■■■■■");
                afficherImage (19,17, renderer, "./BMP/Life/life_3-4_moins.bmp");
                break;
            case 5:
                //printf("■■■■■■■■");
                afficherImage (19,17, renderer, "./BMP/Life/life_3-4.bmp");
                break;
            case 6:
                //printf("■■■■■■■■■■");
                afficherImage (19,17, renderer, "./BMP/Life/life_full.bmp");
                break;
            }
            //printf("\n");
            afficherImage (675, 17, renderer, "./BMP/pause.bmp");

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
                        if (tab2D[nmap][y + 1][x] != 'l' && tab2D[nmap][y + 1][x] != 'i' && tab2D[nmap][y + 1][x] != 'M' && tab2D[nmap][y + 1][x] != 'm' && tab2D[nmap][y + 1][x] != 'T' && tab2D[nmap][y + 1][x] != 't' && tab2D[nmap][y + 1][x] != 'W' && tab2D[nmap][y + 1][x] != 'w' && tab2D[nmap][y + 1][x] != '_' && tab2D[nmap][y + 1][x] != 'L' && tab2D[nmap][y + 1][x] != 'H' && tab2D[nmap][y + 1][x] != 'I' && tab2D[nmap][y + 1][x] != 'B' && tab2D[nmap][y + 1][x] != '+')
                        {
                            if(temp2 == 1)
                            {
                                tab2D[nmap][y][x] = ' ';
                                tab2D[nmap][y + 1][x] = 'v';
                            }
                        }
                        else if (tab2D[nmap][y + 1][x] == '_')
                        {
                            tab2D[nmap][y][x] = ' ';
                            tab2D[nmap][y + 1][x] = 'H';
                        }
                        else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y + 1][x] == 'i')
                        {
                            tab2D[nmap][y][x] = ' ';
                            tab2D[nmap][y + 1][x] = 'I';
                        }
                        else if (tab2D[nmap][y][x] == '^' &&tab2D[nmap][y + 1][x] == 'l')
                        {
                            tab2D[nmap][y][x] = ' ';
                            tab2D[nmap][y + 1][x] = 'L';
                        }
                        else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y + 1][x] == '_')
                        {
                            tab2D[nmap][y][x] = ' ';
                            tab2D[nmap][y + 1][x] = 'H';
                        }
                        else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y + 1][x] == 'w')
                        {
                            tab2D[nmap][y][x] = ' ';
                            tab2D[nmap][y + 1][x] = 'W';
                        }
                        else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y + 1][x] == 't')
                        {
                            tab2D[nmap][y][x] = ' ';
                            tab2D[nmap][y + 1][x] = 'T';
                        }
                        else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y + 1][x] == 'm')
                        {
                            tab2D[nmap][y][x] = ' ';
                            tab2D[nmap][y + 1][x] = 'M';
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
                    if ((rand() % 30) > 22 && (tab2D[nmap][y][x] == 'E' || tab2D[nmap][y][x] == 'F' || tab2D[nmap][y][x] == 'B' || tab2D[nmap][y][x] == '+') &&
                            (rand() % 30) > 28 && (tab2D[nmap][y + 2][x] != 'E') && (tab2D[nmap][y + 2][x] != 'B') && tab2D[nmap][y + 2][x] != 'F' && (tab2D[nmap][y + 1][x] != '+') && (tab2D[nmap][y + 2][x] != '+')
                            && (tab2D[nmap][y + 1][x] != 'E') && (tab2D[nmap][y + 1][x] != 'F') && (tab2D[nmap][y + 1][x] != 'B') && (tab2D[nmap][y + 1][x] != '^'))
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
                    else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y - 1][x] == 'F')
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
                    else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y - 1][x] == 'w')
                    {
                        tab2D[nmap][y][x] = ' ';
                        tab2D[nmap][y - 1][x] = 'W';
                    }
                    else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y - 1][x] == 't')
                    {
                        tab2D[nmap][y][x] = ' ';
                        tab2D[nmap][y - 1][x] = 'T';
                    }
                    else if (tab2D[nmap][y][x] == '^' && tab2D[nmap][y - 1][x] == 'm')
                    {
                        tab2D[nmap][y][x] = ' ';
                        tab2D[nmap][y - 1][x] = 'M';
                    }
                    else if (tab2D[nmap][y][x] == '^' && (tab2D[nmap][y - 1][x] == 'L' || tab2D[nmap][y - 1][x] == 'H' || tab2D[nmap][y - 1][x] == 'I' || tab2D[nmap][y - 1][x] == 'M' || tab2D[nmap][y - 1][x] == 'T' || tab2D[nmap][y - 1][x] == 'W' ))
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
                    SDL_Delay(700);
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
                if (tab2D[nmap][y][COL - 2] == 'E' || tab2D[nmap][y][COL - 2] == 'B' || tab2D[nmap][y][COL - 2] == 'F')
                {
                    position_E = 2;
                    moove_E = 1;
                    break;
                }
                //SI UN ENNEMI TOUCHE LE MUR GAUCHE
                if (tab2D[nmap][y][1] == 'E' || tab2D[nmap][y][1] == 'B' || tab2D[nmap][y][1] == 'F'  )
                {
                    position_E = 1;
                    moove_E = 1;
                    break;
                }
            }

            //MOOVE ENNEMI
            if (temp > 19 && nmap != 3)
            {
                if (position_E == 2)
                {
                    for (int x = 1; x < COL - 1; x++)
                    {
                        for (int y = 1; y < ROW; y++)
                        {
                            if (moove_E == 1 && (tab2D[nmap][y - 1][x + 1] == 'E' || tab2D[nmap][y - 1][x + 1] == 'B' || tab2D[nmap][y - 1][x + 1] == 'F'))
                            {
                                tab2D[nmap][y][x] = tab2D[nmap][y - 1][x + 1];
                                tab2D[nmap][y - 1][x + 1] = ' ';
                            }
                            else if (moove_E == 0 && (tab2D[nmap][y][x + 1] == 'E' || tab2D[nmap][y][x + 1] == 'B' || tab2D[nmap][y][x + 1] == 'F'))
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
                            if (moove_E == 1 && (tab2D[nmap][y - 1][x - 1] == 'E' || tab2D[nmap][y - 1][x - 1] == 'B' || tab2D[nmap][y - 1][x - 1] == 'F'))
                            {
                                tab2D[nmap][y][x] = tab2D[nmap][y - 1][x - 1];
                                tab2D[nmap][y - 1][x - 1] = ' ';
                            }
                            else if (moove_E == 0 && (tab2D[nmap][y][x - 1] == 'E' || tab2D[nmap][y][x - 1] == 'B' || tab2D[nmap][y][x - 1] == 'F'))
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
                if (tab2D[nmap][ROW - 4][x] == 'E' || tab2D[nmap][ROW - 4][x] == 'B'|| tab2D[nmap][ROW - 4][x] == 'F')
                {
                    defeat = 1;
                    fin = 1;
                }
            }

            if (vie == 0 || niveau_final <= 0 )
            {
                fin = 1;
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

            SDL_PollEvent(&event);

            switch(event.type)
            {
            case SDL_QUIT :
                quit  = 1;
                break;

            case SDL_KEYDOWN :
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    defeat = 0;
                }

                if(event.key.keysym.sym == SDLK_RIGHT)
                {
                    sdl_Right = 1;
                }

                if(event.key.keysym.sym == SDLK_LEFT)
                {
                    sdl_Left = 1;
                }

                if(event.key.keysym.sym == SDLK_UP)
                {
                    sdl_Up = 1;
                }
                break;

            case SDL_KEYUP :
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    defeat = 0;
                }

                if(event.key.keysym.sym == SDLK_RIGHT)
                {
                    sdl_Right = 0;
                }

                if(event.key.keysym.sym == SDLK_LEFT)
                {
                    sdl_Left = 0;
                }

                if(event.key.keysym.sym == SDLK_UP)
                {
                    sdl_Up = 0;
                }
                break;

            case SDL_MOUSEBUTTONDOWN  :
                switch ( event.button.button )
                {
                case SDL_BUTTON_LMASK  :
                    if(event.button.x >= 678 && event.button.x <= 756 && event.button.y >= 20 && event.button.y <= 39)
                    {
                        pause = 1;
                        while(pause == 1 && quit != 1)
                        {
                            afficherImage (-5, 0, renderer, "./BMP/frame25.bmp");
                            SDL_WaitEvent (&event);

                            switch ( event.type )
                            {
                            case SDL_MOUSEBUTTONDOWN  :
                                switch ( event.button.button )
                                {
                                case SDL_BUTTON_LMASK  :
                                    if(event.button.x >= 678 && event.button.x <= 756 && event.button.y >= 20 && event.button.y <= 39)
                                    {
                                        SDL_Delay(100);
                                        pause = 0;
                                    }

                                    break;
                                }
                                break;

                            case SDL_QUIT          :
                                quit = 1;
                            }

                            SDL_RenderPresent(renderer);
                            SDL_RenderClear(renderer);
                        }

                    }
                    break;
                }
            }

            if(sdl_Right == 1)
            {
                if (tab2D[nmap][joueur.y][joueur.x + 1] != '|')
                {
                    joueur.x++;
                }
            }

            if(sdl_Left == 1)
            {
                if (tab2D[nmap][joueur.y][joueur.x - 1] != '|')
                {
                    joueur.x--;
                }
            }

            if(sdl_Up == 1)
            {
                if (laser >= 6)
                {
                    tab2D[nmap][joueur.y - 1][joueur.x] = '^';
                    laser = 0;
                }
            }
            if(fin == 1)
            {
                while( quit !=1 && rejouer == 0)
                {
                    afficherImage (-10, 0, renderer, "./BMP/fin.bmp");
                    afficherTexteBig(232,299,renderer, "polices/PressStart2P.ttf", score_affiche);
                    afficherTexteBig(282,368,renderer, "polices/PressStart2P.ttf", stage_affiche);
                    SDL_PollEvent(&event);

                    switch(event.type)
                    {
                    case SDL_QUIT :
                        quit  = 1;
                        break;
                    case SDL_MOUSEBUTTONDOWN  :
                        switch ( event.button.button )
                        {
                        case SDL_BUTTON_LMASK  :
                            if(event.button.x >= 261 && event.button.x <= 510 && event.button.y >= 506 && event.button.y <= 541)
                            {
                                rejouer = 1;
                            }
                            break;
                        }
                    }
                    SDL_RenderPresent(renderer);
                    SDL_RenderClear(renderer);
                }
            }
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
            SDL_Delay(25);
            ShowWindow(FindWindow("tty",NULL),SW_HIDE);
        }
        while (rejouer != 1 && quit != 1);
    }
    while(quit != 1);
    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (fenetre);
    SDL_Quit();
    TTF_Quit();

    return EXIT_SUCCESS;
}

