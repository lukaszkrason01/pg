#ifndef HIGHSCORES_HPP_INCLUDED
#define HIGHSCORES_HPP_INCLUDED

#include "Texture.hpp"
#include "HUDMessege.hpp"
#include "Button.hpp"
#include "filehs.hpp"

#include <sstream>

class HighScores : Texture
{
    private:
    Button *back;
    Messege *player[5];
    Messege *score[5];
    Filehs *scores;
    int widthofscore[5];
    TTF_Font *Font;
    SDL_Color Color;

    public:
    static const int BACK = 1;

    HighScores(SDL_Surface* ,SDL_Surface* ,SDL_Surface* , TTF_Font *f);
    ~HighScores();
    void show();
    int action();
    void refresh();
    void handle_event(SDL_Event event);
    void update();
    void clean_up();
};


#endif // HIGHSCORES_HPP_INCLUDED
