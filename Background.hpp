#ifndef BACKGROUND_HPP_INCLUDED
#define BACKGROUND_HPP_INCLUDED

#include "Texture.hpp"

class Background : public Texture
{
    public:
    int y;
    Background(SDL_Surface* sur, SDL_Surface *sc );
    ~Background();
    void show();
    void move(int offset);
};

#endif // BACKGROUND_HPP_INCLUDED
