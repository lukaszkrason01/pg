#include "Button.hpp"

Button::Button( int x, int y, int w, int h ,SDL_Surface *sur,SDL_Surface *scr)
:Texture(sur,scr)
{
    //Set the button's attributes
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    pressed = false;
    clicked = false;
    focused = false;

    //Set the default sprite
    clip = &clips[ CLIP_MOUSEOUT ];

    sound = NULL;
    sound2 = NULL;
}

Button::Button(int x, int y, int w, int h ,SDL_Surface *sur,SDL_Surface *scr, Mix_Chunk *s, Mix_Chunk *s2)
:Texture(sur,scr)
{
    //Set the button's attributes
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    pressed = false;
    clicked = false;
    focused = false;

    //Set the default sprite
    clip = &clips[ CLIP_MOUSEOUT ];
    sound = s;
    sound2 = s2;
}
void Button::set_clips()
{
    //Clip the sprite sheet
    clips[ CLIP_MOUSEOVER ].x = 0;
    clips[ CLIP_MOUSEOVER ].y = 0;
    clips[ CLIP_MOUSEOVER ].w = 330;
    clips[ CLIP_MOUSEOVER ].h = 60;

    clips[ CLIP_MOUSEOUT ].x = 0;
    clips[ CLIP_MOUSEOUT ].y = 60;
    clips[ CLIP_MOUSEOUT ].w = 330;
    clips[ CLIP_MOUSEOUT ].h = 60;

    clips[ CLIP_MOUSEDOWN ].x = 0;
    clips[ CLIP_MOUSEDOWN ].y = 120;
    clips[ CLIP_MOUSEDOWN ].w = 330;
    clips[ CLIP_MOUSEDOWN ].h = 60;

    clips[ CLIP_MOUSEUP ].x = 0;
    clips[ CLIP_MOUSEUP ].y = 180;
    clips[ CLIP_MOUSEUP ].w = 330;
    clips[ CLIP_MOUSEUP ].h = 60;
}
void Button::handle_events(SDL_Event event)
{
    clicked = false;
    //The mouse offsets
    int x , y;

    //If the mouse moved
    if( event.type == SDL_MOUSEMOTION )
    {
        //Get the mouse offsets
        x = event.motion.x;
        y = event.motion.y;

        //If the mouse is over the button
        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ))
        {
            //Set the button sprite
            clip = &clips[ CLIP_MOUSEOVER ];
            if(focused == false)
                Mix_PlayChannel( -1, sound, 0 );
            focused = true;
        }
        //If not
        else
        {
            //Set the button sprite
            clip = &clips[ CLIP_MOUSEOUT ];
            pressed=false;
            focused = false;
        }
    }
    //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN || pressed)
    {
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                //Set the button sprite
                clip = &clips[ CLIP_MOUSEDOWN ];
                pressed = true;
            }
        }
    }
    //If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP && pressed)
    {
        //If the left mouse button was released
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ))
            {
                //Set the button sprite
                Mix_PlayChannel(-1, sound2, 0);
                clip = &clips[ CLIP_MOUSEUP ];
                clicked = true;
            }
        }
    }
}

bool Button::action()
{
    return clicked;
}

void Button::refresh()
{
    focused = false;
    pressed = false;
    clicked = false;
    clip = &clips[CLIP_MOUSEOUT];
}
void Button::show()
{
    //Show the button
    apply_surface( &box,  clip);
}
