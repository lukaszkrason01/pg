#include "highscores.hpp"

#include <string>

HighScores::HighScores(SDL_Surface *but, SDL_Surface *sur,SDL_Surface *scr,TTF_Font *f):Texture(sur,scr)
{
    Font = f;
    Color.b=255;
    Color.g=255;
    Color.r=255;

    back = new Button(143,400,330,60,but,scr);
    back->set_clips();

    scores= new Filehs();
    for (int i = 0 ; i < scores->MAX_SIZE ; ++i)
    {
        player[i] = new Messege(screen);
        score [i] = new Messege(screen);
    }
}

HighScores::~HighScores()
{
    for (int i = 0 ; i < scores->size ; ++i)
    {
        delete player[i];
        delete score[i];
    }
    delete scores;
    delete back;
}

void HighScores::addRecord(std::string player, int score)
{
    scores -> addRecord(player, score);
}

int HighScores::getWorst()
{
    return scores -> getWorst();
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

void HighScores::update()
{
    for(int i=0;i<scores->size;i++)
    {
        player[i] -> make_messege(scores->getGamer(i),Font, Color);
        score[i] -> make_messege(scores->getScore(i),Font,Color);
    }
}

void HighScores::clean_up()
{
    for(int i=0;i<scores->size;i++)
    {
        player[i] -> clean_up();
        score[i] -> clean_up();
    }
}

void HighScores::show()
{

    SDL_Rect offset;
    offset.x=0;
    offset.y=0;
    apply_surface(&offset);
    for(int i=0;i<scores->size;i++)
    {
        player[i] -> show(100,100+50*i);
        score[i] -> show(500-score[i]->text->w,100+50*i);
    }
    back->show();
}

void HighScores::handle_event(SDL_Event event)
{
    back->handle_events(event);
}
