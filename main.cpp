#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "Timer.hpp"
#include "Pause.hpp"
#include "game.hpp"
#include "Sizes.h"

#include "Hero.hpp"

#include <string>
#include <sstream>

//screen
const int FRAMES_PER_SECOND = 20;

//surfeces
SDL_Surface* screen = NULL;
SDL_Surface* herosprite = NULL;
SDL_Surface* floortexture=NULL;
SDL_Surface* bg = NULL;
SDL_Surface* game_over=NULL;

SDL_Surface* pause_screen=NULL;
SDL_Surface* pause_menu = NULL;
SDL_Surface* back_button_pause_menu = NULL;
SDL_Surface* restart_button_pause_menu = NULL;
SDL_Surface* quit_button_pause_menu = NULL;
SDL_Surface* main_menu_button_pause_menu = NULL;

TTF_Font *messages_font = NULL;
SDL_Event event;


enum STATE{
    QUIT,
    GAME,
    PAUSE,
    GAME_OVER,
    MAIN_MENU
};

STATE state;
Game *game = NULL;
PauseMenu *pause = NULL;
Timer *game_time = NULL;

SDL_Surface *load_image( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );
    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0xFF, 0x00, 0xFF ) );
        }
    }
    return optimizedImage;
}

//////////////////
bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1) return false;

    screen= SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (screen==NULL) return false;

    pause_screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if(pause_screen == NULL) return false;
    if( TTF_Init() == -1 ) return false;

    SDL_WM_SetCaption( "Studnia", NULL );
    return true;
}

bool load_files()
{
    herosprite=load_image("jpg//hero3.png");
    if(herosprite == NULL) return false;

    bg=load_image("jpg//background.png");
    if(bg == NULL) return false;

    floortexture=load_image("jpg//floor.png");
    if(floortexture==NULL) return false;

    game_over=load_image("jpg//game-over.png");
    if(game_over== NULL) return false;

    pause_menu = load_image("jpg//PAUSE.png");
    if(pause_menu == NULL) return false;

    back_button_pause_menu = load_image("jpg//pausebuttonback1.png");
    if(back_button_pause_menu == NULL) return false;

    restart_button_pause_menu= load_image("jpg//restartbutton.png");
    if(restart_button_pause_menu == NULL) return false;

    quit_button_pause_menu= load_image("jpg//quit.png");
    if(quit_button_pause_menu == NULL) return false;

    main_menu_button_pause_menu=load_image("jpg//mainmenu.png");
    if(main_menu_button_pause_menu == NULL) return false;

    messages_font=TTF_OpenFont("font//vademecum.ttf",32);
    if(messages_font == NULL) return false;

    return true;
}

void clean_up()
{
    SDL_FreeSurface( herosprite );
    SDL_FreeSurface( bg );
    SDL_FreeSurface( floortexture );
    SDL_FreeSurface( game_over );
    SDL_FreeSurface (pause_menu );
    SDL_FreeSurface( back_button_pause_menu );
    SDL_FreeSurface(restart_button_pause_menu);
    SDL_FreeSurface(quit_button_pause_menu);
    SDL_FreeSurface(main_menu_button_pause_menu);

    TTF_CloseFont( messages_font );
    TTF_Quit();
    SDL_Quit();
}
void unpause()
{
    pause->refresh();
    state = GAME;
    game_time->unpause();
}
void restart()
{
    delete game;
    game= new Game(herosprite,
                   floortexture,
                   bg,
                   messages_font,
                   screen);
}

void handle_event()
{
    switch (state)
    {
    case GAME:
        game->hero->handle_event(event,game_time->is_paused());
        break;
    case PAUSE:
        game->hero->handle_event(event,game_time->is_paused());
        pause->handle_event(event);
        break;
    default : break;
    }

    if (event.type == SDL_KEYDOWN)
        if(event.key.keysym.sym == SDLK_ESCAPE)
        {
            switch (state)
            {
            case GAME:
                state = PAUSE;
                game_time->pause();
                break;
            case PAUSE:
                unpause();
                break;
            case GAME_OVER:
                restart();
                unpause();
                break;
            default : break;
            }
        }

    if( event.type == SDL_QUIT ) state = QUIT;
}

void behavior()
{
    switch (state)
    {
        case GAME:
            game->setHud(game_time);
            game->setCamera(game_time);
            game->newFloor();
            game->draw();
            game->behavior(game_time);

            if(game->hero->box.y > SCREEN_HEIGHT)
                state= GAME_OVER;
            if( SDL_Flip( screen ) == -1 ) exit(EXIT_FAILURE);
            break;
        case PAUSE:
            pause->show();
            switch(pause->action())
            {
                case PauseMenu::RESTART:
                    restart();
                case PauseMenu::BACK_TO_GAME:
                    unpause();
                    break;
                case PauseMenu::QUIT:
                    state = QUIT;
                default: break;
            }
            if( SDL_Flip( pause_screen ) == -1 ) exit(EXIT_FAILURE);
            break;
        case GAME_OVER:
            game_time->stop();
            game->draw();
            Texture::apply_surface(120,40,game_over,screen);
            game->hero->box.y = 700;
            if( SDL_Flip( screen ) == -1 ) exit(EXIT_FAILURE);
            break;
        default : break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////main
int main( int argc, char* args[] )
{
    if(!init())         exit(EXIT_FAILURE);
    if(!load_files())   exit(EXIT_FAILURE);

    Timer fps;

    game= new Game(herosprite,floortexture,bg,messages_font,screen);

    pause=new PauseMenu(pause_menu,pause_screen);
    pause->setBack(back_button_pause_menu);
    pause->setRestart(restart_button_pause_menu);
    pause->setMainmenu (main_menu_button_pause_menu);
    pause->setQuit(quit_button_pause_menu);

    state = GAME;

    game_time = new Timer();
    game_time -> start();

    Hero h= *game->hero;

    while( state != QUIT )
    {
        fps.start();
        //////////////////////////////////handlers
        while( SDL_PollEvent( &event ) )
        {
            handle_event();
        }

        behavior();
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
        ////////testing

        std::stringstream caption;
        caption << "test = " << event.key.keysym.sym;
        SDL_WM_SetCaption( caption.str().c_str(), NULL );
    }

    delete game;
    delete pause;
    clean_up();

    return 0;
}
