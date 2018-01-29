#ifndef HERO_HPP_INCLUDED
#define HERO_HPP_INCLUDED

#include "Texture.hpp"
#include "SDL/SDL.h"
#include "Sizes.h"

class Hero
    : public Texture
{
public:
    //game rules
    static const int GRAVITY=8;
    static const int HERO_SPEED=10;
    static const int SPEED_DURATION_1 = 10;
    static const int SPEED_DURATION_2 = 25;
    static const int HERO_JUMP_LEVEL1=11;
    static const int HERO_JUMP_LEVEL2=15;
    static const int HERO_JUMP_LEVEL3=23;

    //hero clips
    static const int HERO_STAND      = 0;
    static const int HERO_RUN_RIGHT  = 3;
    static const int HERO_RUN_LEFT   = 6;
    static const int HERO_JUMP       = 9;
    static const int HERO_JUMP_RIGHT =10;
    static const int HERO_JUMP_LEFT  =11;
    static const int HERO_FALL_RIGHT =12;
    static const int HERO_FALL_LEFT  =13;
    static const int HERO_FALL_DOWN  =14;

    static const int HERO_SPRITES = 15;

    int runDuration;

    int whichclip;
    int changeclip;

    int jumpDuration;
    int jumpAltitude;
    int fallDuration;

    int xVel,yVel;

    int lastxVel;
    int level;
    SDL_Rect box;

    SDL_Rect hero_clips[ HERO_SPRITES ];
    bool jumping,falling,jumpingOn;

    Hero(SDL_Surface* sur,SDL_Surface* sc);
    Hero();
    ~Hero();

    void moveUp(int);
    void show();
    void handle_event(SDL_Event event,bool pause);
    void move();
    void set_camera(int offset);
    void clip();
    void dont_go();
};
#endif // HERO_HPP_INCLUDED
