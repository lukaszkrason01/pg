#ifndef MAINMENU_HPP_INCLUDED
#define MAINMENU_HPP_INCLUDED

#include "Button.hpp"
#include "Texture.hpp"

class MainMenu : public Texture
{
    private :
        Button *newGame;
        Button *highscore;
        Button *quit;
    public:

        static const int NEW_GAME = 1;
        static const int HIGHSCORE = 2;
        static const int QUIT=3;

        MainMenu(SDL_Surface*,SDL_Surface*);
        ~MainMenu();

        int action();
        void setnewgame(SDL_Surface*);
        void sethighscore(SDL_Surface*);
        void setquit(SDL_Surface*);
        void show();
        void handle_event(SDL_Event event);
        void refresh();
};

#endif // MAINMENU_HPP_INCLUDED
