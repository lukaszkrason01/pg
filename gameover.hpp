#ifndef GAMEOVER_HPP_INCLUDED
#define GAMEOVER_HPP_INCLUDED

#include "Texture.hpp"
#include "Sizes.h"
#include "HUDMessege.hpp"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#include <string>

//The key press interpreter
class StringInput
{
    private:
    //The storage string
    std::string str;
    SDL_Surface* screen;

    //The text surface
    SDL_Surface *text;

    public:
    //Initializes variables
    StringInput(SDL_Surface *scr);

    //Does clean up
    ~StringInput();

    //Handles input
    void handle_input(SDL_Event event,TTF_Font *font, SDL_Color textColor);

    //Shows the message on screen
    void show_centered();
    void refresh(TTF_Font *f,SDL_Color c);
    std::string getStr();
};

class GameOver
{
private:

public:
    TTF_Font *font;
    SDL_Color color;
    SDL_Surface *screen;
    Messege *desc;
    Messege *press;
    StringInput *player;
    bool nameEntered;

    Mix_Chunk *yeah;
    Mix_Chunk *loose;

    GameOver(SDL_Surface* scr , TTF_Font *f, Mix_Chunk *y,Mix_Chunk *l);

    void show();
    void update();
    void handle_event(SDL_Event event);
    bool isRekord(int current, int worst);
    void newRecord();
    void refresh();
    bool nameWriting();
    void play_sound();
};

#endif // GAMEOVER_HPP_INCLUDED
