#include "mainmenu.hpp"

MainMenu::MainMenu(SDL_Surface *sur,SDL_Surface *scr):Texture(sur,scr)
{
}

MainMenu::MainMenu(SDL_Surface *sur,SDL_Surface *scr, Mix_Chunk *s,Mix_Chunk* s2,Mix_Music *m):Texture(sur,scr)
{
    sound = s;
    sound2 = s2;
    music = m;
}
MainMenu::~MainMenu()
{
    delete newGame;
    delete highscore;
    delete quit;
}
void MainMenu::setnewgame(SDL_Surface *sur)
{
    newGame=new Button(143,142,330,60,sur,screen,sound,sound2);
    newGame->set_clips();
}
void MainMenu::sethighscore(SDL_Surface *sur)
{
    highscore = new Button(143,242,330,60,sur,screen,sound,sound2);
    highscore -> set_clips();
}

void MainMenu::setquit(SDL_Surface *sur)
{
    quit = new Button(143,342,330,60,sur,screen,sound,sound2);
    quit -> set_clips();
}
int MainMenu::action()
{
    if(newGame->action())return NEW_GAME;
    if(highscore->action()) return HIGHSCORE;
    if(quit->action()) return QUIT;

    return 0;
}

void MainMenu::handle_event(SDL_Event event)
{
    newGame->handle_events(event);
    highscore->handle_events(event);
    quit->handle_events(event);
}

void MainMenu::refresh()
{
    newGame->refresh();
    highscore->refresh();
    quit->refresh();
    Mix_HaltMusic();
}
void MainMenu::show()
{
    SDL_Rect offset;
    offset.x=0;
    offset.y=0;
    apply_surface(&offset);

    newGame->show();
    highscore->show();
    quit->show();
}

void MainMenu::play_music()
{
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( music, -1 );
    }
}
