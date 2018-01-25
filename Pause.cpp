#include "Pause.hpp"

PauseMenu::PauseMenu(SDL_Surface *sur,SDL_Surface *scr):Texture(sur,scr)
{
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
    back=new Button(143,112,330,60,sur,screen);
    back->set_clips();
}

void PauseMenu::setRestart(SDL_Surface *sur)
{
    restart = new Button(143,187,330,60,sur,screen);
    restart -> set_clips();
}
void PauseMenu::setMainmenu(SDL_Surface *sur)
{
    mainmenu = new Button(143,262,330,60,sur,screen);
    mainmenu -> set_clips();
}
void PauseMenu::setQuit(SDL_Surface *sur)
{
    quit = new Button (142,357,330,60,sur,screen);
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

