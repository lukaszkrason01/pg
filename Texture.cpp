#include "Texture.hpp"

Texture::Texture(SDL_Surface* sur,SDL_Surface* sc)
{
    surface= sur;
    screen = sc;
}

void Texture::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}
void Texture::apply_surface(SDL_Rect* box,SDL_Rect* clip)
{
    SDL_BlitSurface(surface, clip, screen, box);
}
