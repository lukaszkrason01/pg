#include "highscores.hpp"

#include <string>

HighScores::HighScores(SDL_Surface *but, SDL_Surface *sur,SDL_Surface *scr, std::stringstream *s,TTF_Font *f):Texture(sur,scr)
{
    Font = f;
    Color.b=255;
    Color.g=255;
    Color.r=255;

    back = new Button(143,400,330,60,but,scr);
    for (int i = 0 ; i < 5 ; ++i)
    {
     //   player[i] = new Messege(screen);
       // score [i] = new Messege(screen);
    }

    back->set_clips();

    for(int j=0;j<5;j++)
    {
    //    player[j] -> make_messege(s[j*2].str().c_str(),Font, Color);
    //    score[j] -> make_messege(s[j*2+1].str().c_str(),Font,Color);
    }
}

int HighScores::action()
{
    if(back->action()) return 1;
    return 0;
}

void HighScores::refresh()
{
    back->refresh();
}
void HighScores::show()
{
    SDL_Rect offset;
    offset.x=0;
    offset.y=0;
    apply_surface(&offset);
    for (int i = 0 ; i < 5 ; ++i)
    {
    //    player[i]->show(10,50*i+100);
     //   score [i]->show(500,50*i+100);
    }

    back->show();
}

void HighScores::handle_event(SDL_Event event)
{
    back->handle_events(event);
}
