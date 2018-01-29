#include "Pause.hpp"

PauseMenu::PauseMenu(SDL_Surface *sur,SDL_Surface *scr):Texture(sur,scr)
{
    sound = NULL;
    sound2 = NULL;
}

PauseMenu::PauseMenu(SDL_Surface *sur,SDL_Surface *scr,Mix_Chunk *s,Mix_Chunk *s2):Texture(sur,scr)
{
    sound = s;
    sound2 = s2;
}

PauseMenu::~PauseMenu()
{
    delete back;
    delete restart;
    delete mainmenu;
    delete quit;
}
void PauseMenu::setBack(SDL_Surface *sur)
{
    back=new Button(143,112,330,60,sur,screen,sound,sound2);
    back->set_clips();
}

void PauseMenu::setRestart(SDL_Surface *sur)
{
    restart = new Button(143,187,330,60,sur,screen,sound,sound2);
    restart -> set_clips();
}
void PauseMenu::setMainmenu(SDL_Surface *sur)
{
    mainmenu = new Button(143,262,330,60,sur,screen,sound,sound2);
    mainmenu -> set_clips();
}
void PauseMenu::setQuit(SDL_Surface *sur)
{
    quit = new Button (142,357,330,60,sur,screen,sound,sound2);
    quit -> set_clips();
}
void PauseMenu::handle_event(SDL_Event event)
{
    back->handle_events(event);
    restart -> handle_events(event);
    mainmenu -> handle_events(event);
    quit -> handle_events(event);
}
int PauseMenu::action()
{
    if(back->action())return BACK_TO_GAME;
    if(restart -> action() ) return RESTART;
    if( mainmenu -> action() ) return MAIN_MENU;
    if( quit -> action() ) return QUIT;
    return 0;
}
void PauseMenu::refresh()
{
    back -> refresh();
    restart -> refresh();
    mainmenu -> refresh();
    quit -> refresh();
}

void PauseMenu::show()
{
    SDL_Rect offset;
    offset.x=0;
    offset.y=0;
    apply_surface(&offset);
    back->show();
    restart -> show();
    mainmenu -> show();
    quit -> show();
}

