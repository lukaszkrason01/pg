#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include "SDL/SDL.h"


class Texture
{
    public:
    SDL_Surface *surface;
    SDL_Surface *screen;

    Texture(SDL_Surface* sur, SDL_Surface *sc);
    static void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip=NULL);
    void apply_surface( SDL_Rect *box, SDL_Rect* clip=NULL);

};


#endif // TEXTURE_HPP_INCLUDED
