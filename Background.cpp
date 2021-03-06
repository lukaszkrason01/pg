#include "Background.hpp"

Background::Background(SDL_Surface* sur, SDL_Surface *sc) : Texture(sur,sc)
{
    y=0;
}

Background::~Background()
{

}
void Background::show()
{
    apply_surface(0,y,surface,screen);
    apply_surface(0,y+surface->h,surface,screen);
}


void Background::move(int offset)
{
    y-=offset;
    if( y <= -surface->h )
    {
        y = 0;
    }
}
