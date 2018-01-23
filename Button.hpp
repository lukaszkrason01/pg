#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED
#include "Texture.hpp"

class Button : public Texture
{
    private:
    //The attributes of the button
    SDL_Rect box;
    SDL_Rect clips[ 4 ];
    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;


    static const int CLIP_MOUSEOVER = 0;
    static const int CLIP_MOUSEOUT = 1;
    static const int CLIP_MOUSEDOWN = 2;
    static const int CLIP_MOUSEUP = 3;

    public:
    //Initialize the variables
    Button( int x, int y, int w, int h ,SDL_Surface* ,SDL_Surface* );

    bool pressed;
    bool clicked;

    //Handles events and set the button's sprite region
    void handle_events(SDL_Event);

    //Shows the button on the screen
    void show();
    void set_clips();

    bool action();
    void refresh();
};

#endif // BUTTON_HPP_INCLUDED
