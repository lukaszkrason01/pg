#ifndef PAUSE_HPP_INCLUDED
#define PAUSE_HPP_INCLUDED

#include "Texture.hpp"
#include "Button.hpp"

class PauseMenu :
    public Texture
{
    private:
        Button *back;
        Button *restart;
        Button *mainmenu;
        Button *quit;

    public:
    static const int BACK_TO_GAME = 1;
    static const int RESTART = 2;
    static const int MAIN_MENU=3;
    static const int QUIT = 4;

    PauseMenu(SDL_Surface*,SDL_Surface*);

    void setBack(SDL_Surface*);
    void setRestart(SDL_Surface *);
    void setQuit(SDL_Surface *);
    void setMainmenu(SDL_Surface *);
    void show();
    void handle_event(SDL_Event event);
    int action();
    void refresh();
};

#endif
