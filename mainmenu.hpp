#ifndef MAINMENU_HPP_INCLUDED
#define MAINMENU_HPP_INCLUDED

#include "Button.hpp"
#include "Texture.hpp"

#include "SDL/SDL_mixer.h"

class MainMenu : public Texture
{
    private :
        Mix_Chunk *sound;
        Mix_Chunk *sound2;
        Mix_Music *music;

        Button *newGame;
        Button *highscore;
        Button *quit;
    public:

        static const int NEW_GAME = 1;
        static const int HIGHSCORE = 2;
        static const int QUIT=3;

        MainMenu(SDL_Surface*,SDL_Surface*);
        MainMenu(SDL_Surface*,SDL_Surface*,Mix_Chunk*,Mix_Chunk*,Mix_Music*);
        ~MainMenu();

        int action();
        void setnewgame(SDL_Surface*);
        void sethighscore(SDL_Surface*);
        void setquit(SDL_Surface*);
        void show();
        void handle_event(SDL_Event event);
        void refresh();
        void play_music();
};

#endif // MAINMENU_HPP_INCLUDED
