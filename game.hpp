#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <cstdlib>

#include "SDL/SDL_ttf.h"
#include "Sizes.h"
#include "Hero.hpp"
#include "Floor.hpp"
#include "Background.hpp"
#include "HUDMessege.hpp"
#include "Timer.hpp"

class Game
{
    private:
    const static int MAX_DIFFICULT = 6;
    const static int TIME_TO_MORE_DIFFICULT=30000;
    const static int FLOORS=6;
    const static int NEXT_FLOOR=20;

    int counterFloors;
    int difficult;
    int inWhichFloorHeroIs;
    int floor_level;
    int camera_offset;
    int score;
    int time;
    bool start_game;

    bool check_collision( SDL_Rect A, SDL_Rect B );
    int whereIsFloor(SDL_Rect A,SDL_Rect B);

    public:
    Hero *hero;
    Background *background;
    RightCorner *corner;
    Floor *base[FLOORS];
    Game(SDL_Surface *heroSpr,SDL_Surface *floorSpr, SDL_Surface *backgroudSpr, TTF_Font *messegeFont, SDL_Surface *screen);

    Game();
    void setHud(Timer*);
    void setCamera(Timer*);
    void draw();
    void behavior(Timer *t);
    void newFloor();
    int getScore();
    void handle_event(SDL_Event event);

    virtual ~Game();
};

#endif // GAME_HPP_INCLUDED
