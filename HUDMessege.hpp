#ifndef HUDMESSEGE_HPP_INCLUDED
#define HUDMESSEGE_HPP_INCLUDED

#include "Texture.hpp"

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <sstream>


class Messege
{
    SDL_Surface *screen;


    public:
    SDL_Surface *text;
    Messege(SDL_Surface *scr);

    void clean_up();
    void make_messege(const char *desc,TTF_Font *f,SDL_Color c);
    void show(int,int);
    ~Messege();
};

class RightCorner
{
    public:

    SDL_Surface *screen;
    TTF_Font *Font;

    SDL_Color Color;
    Messege *score_messege;
    Messege *time_messege;
    Messege* level_messege;
    Messege* floor_messege;

    int score;

    RightCorner(SDL_Surface*,TTF_Font*);
    ~RightCorner();
    void updateScore(int);
    void updateTime(int);
    void updateLevel(int);
    void updateFloor(int);
    void show();

    void clean_up();
};

#endif // HUDMESSEGE_HPP_INCLUDED
