#include "gameover.hpp"

GameOver::GameOver(SDL_Surface *screen,TTF_Font *f)
{
    font = f;
    color.r=color.g=color.b=255;
    nameEntered = true;

    desc = new Messege(screen);
    press = new Messege(screen);
    player = new StringInput(screen);
}

void GameOver::update()
{
    if(nameEntered)
    {
        desc->make_messege("G A M E    O V E R !",font,color);
        press -> make_messege("Press ESC to back to Menu",font,color);
    }
    else
    {
        desc->make_messege("H I G H    S C O R E !",font,color);
        press -> make_messege("Enter your name",font,color);
    }

}

void GameOver::refresh()
{
    nameEntered = true;
    player -> refresh(font,color);
}

void GameOver::newRecord()
{
    nameEntered = false;
}

bool GameOver::nameWriting()
{
    return nameEntered;
}

void GameOver::show()
{
    desc -> show((SCREEN_WIDTH - desc->text->w ) / 2, ( ( SCREEN_HEIGHT / 2 ) - desc->text->h ) / 2);
    press -> show((SCREEN_WIDTH - press->text->w ) / 2, ( ( SCREEN_HEIGHT / 2 ) - press->text->h ) / 2 + 100);

    if(!nameEntered)
        player -> show_centered();
}
void GameOver::handle_event(SDL_Event event)
{
    std::string temp = player->getStr();
    if(!nameEntered)
    {
        player -> handle_input(event,font,color);
        if( ( event.type == SDL_KEYDOWN ) &&
           ( event.key.keysym.sym == SDLK_RETURN ) &&
           ( player -> getStr().length() > 0 ) )
        {
            nameEntered = true;
            update();
        }
    }
}

StringInput::StringInput(SDL_Surface *scr)
{
    screen = scr;
    //Initialize the string
    str = "";

    //Initialize the surface
    text = NULL;

    //Enable Unicode
    SDL_EnableUNICODE( SDL_ENABLE );
}

StringInput::~StringInput()
{
    //Free text surface
    SDL_FreeSurface( text );

    //Disable Unicode
    SDL_EnableUNICODE( SDL_DISABLE );
}

void StringInput::handle_input(SDL_Event event,TTF_Font *font, SDL_Color textColor)
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Keep a copy of the current version of the string
        std::string temp = str;

        //If the string less than maximum size
        if( str.length() <= 16 )
        {
            //If the key is a space
            if( event.key.keysym.unicode == (Uint16)' ' )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
            //If the key is a number
            else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
            //If the key is a uppercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
            //If the key is a lowercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
        }

        //If backspace was pressed and the string isn't blank
        if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
        {
            //Remove a character from the end
            str.erase( str.length() - 1 );
        }

        //If the string was changed
        if( str != temp )
        {
            //Free the old surface
            SDL_FreeSurface( text );

            //Render a new text surface
            text = TTF_RenderText_Solid( font, str.c_str(), textColor );
        }
    }
}

void StringInput::show_centered()
{
    //If the surface isn't blank
    if( text != NULL )
    {
        //Show the name
       Texture::apply_surface( ( SCREEN_WIDTH - text->w ) / 2, ( SCREEN_HEIGHT - text->h ) / 2 + 50, text, screen );
    }
}

void StringInput::refresh(TTF_Font *f,SDL_Color c)
{
    str = "";
    SDL_FreeSurface(text);
    text = TTF_RenderText_Solid(f,"",c);
}

std::string StringInput::getStr()
{
    return str;
}
