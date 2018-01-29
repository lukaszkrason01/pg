#include "HUDMessege.hpp"

Messege::Messege(SDL_Surface *scr)
{
    screen = scr;
    text=NULL;
}


void Messege::make_messege(const char *desc,TTF_Font *f,SDL_Color c)
{
    clean_up();
    text=TTF_RenderText_Solid(f,desc,c);
}


void Messege::show(int x,int y)
{
    if(text != NULL)Texture::apply_surface(x,y,text,screen);
}

void Messege::clean_up()
{
    SDL_FreeSurface(text);
}

Messege::~Messege()
{
    clean_up();
}

RightCorner::RightCorner(SDL_Surface * src,TTF_Font *f)
{
    screen = src;
    Font = f;
    score_messege=new Messege(screen);
    time_messege=new Messege(screen);
    level_messege=new Messege(screen);
    floor_messege=new Messege(screen);
    score = 0;
    Color.r=255;
    Color.g=255;
    Color.b=255;
}

RightCorner::~RightCorner()
{
    delete score_messege;
    delete time_messege;
    delete level_messege;
    delete floor_messege;
}
void RightCorner::updateScore(int s)
{
    std::stringstream sstm;
    if(s>score)score=s;
    sstm << "Score : " << score;
    score_messege->make_messege(sstm.str().c_str(),Font,Color);
}

void RightCorner::updateTime(int time)
{
    std::stringstream sstm;
    sstm << "Time: " << time << "s" ;
    time_messege->make_messege(sstm.str().c_str(),Font,Color);
}

void RightCorner::updateLevel(int lev)
{
    std::stringstream sstm;
    sstm << "Level : " << lev;
    level_messege -> make_messege(sstm.str().c_str(),Font,Color);
}

void RightCorner::updateFloor(int f)
{
    std::stringstream sstm;

    switch (f)
        {
            case 0:
                sstm << "Large";
                break;
            case 1:
                sstm << "Medium";
                break;
            default :
                sstm << "Small";
                break;
        }
    sstm << " floor!";
    floor_messege->make_messege(sstm.str().c_str(),Font,Color);
}

void RightCorner::show()
{
    score_messege->show(0,0);
    time_messege->show(0,30);
    level_messege->show(0,60);
    floor_messege->show(0,90);
}


void RightCorner::clean_up()
{
    score_messege->clean_up();
    time_messege->clean_up();
    level_messege->clean_up();
    floor_messege->clean_up();
}
