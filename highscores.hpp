#ifndef HIGHSCORES_HPP_INCLUDED
#define HIGHSCORES_HPP_INCLUDED

#include "Texture.hpp"
#include "HUDMessege.hpp"
#include "Button.hpp"
#include "filehs.hpp"

#include "SDL/SDL_mixer.h"

#include <sstream>

class HighScores : Texture
{
    private:
    Button *back;
    Messege *player[5];

    Mix_Music *music;

    int widthofscore[5];
    TTF_Font *Font;
    SDL_Color Color;

    public:
    Filehs *scores;
    Messege *score[5];
    static const int BACK = 1;

    HighScores(SDL_Surface* ,
               SDL_Surface* ,
               SDL_Surface* ,
               TTF_Font *f);

    HighScores(SDL_Surface* ,
               SDL_Surface* ,
               SDL_Surface* ,
               TTF_Font *f ,
               Mix_Chunk *s ,
               Mix_Chunk *s2,
               Mix_Music *m);
    ~HighScores();
    void show();
    int action();
    void refresh();
    void handle_event(SDL_Event event);
    void update();
    void clean_up();
    int getWorst();
    void addRecord(std::string player, int score);
};


#endif // HIGHSCORES_HPP_INCLUDED
