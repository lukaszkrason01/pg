#ifndef FLOOR_HPP_INCLUDED
#define FLOOR_HPP_INCLUDED

#include "Texture.hpp"
#include "Sizes.h"

#include "SDL/SDL.h"


class Floor : public Texture
{
    private:
    static const int NUMBER_OF_FLOORS  = 2;
    static const int FLOOR_LEVEL1_MAX_LENGHT=13;
    static const int FLOOR_LEVEL1_MIN_LENGHT=6;
    static const int FLOOR_LEVEL2_MAX_LENGHT=9;
    static const int FLOOR_LEVEL2_MIN_LENGHT=6;
    static const int FLOOR_LEVEL3= 6;

    public:
    int length;
    int counter;
    int whichfloor;
    bool change_floor;
    SDL_Rect box;
    static SDL_Rect floor_clips [];

    Floor(int l,int x,int y, SDL_Surface* sur,SDL_Surface* sc);
    Floor(int y, SDL_Surface* sur,SDL_Surface* sc);
    ~Floor();
    void show();
    void set_camera(int offset);
    bool isDisappear(int sh);
    void newfloor(int level);
    void init();
    void newSuperFloor();
    void floorToChange();

    void clip_floor();
};


#endif // FLOOR_HPP_INCLUDED
