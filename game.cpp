#include "game.hpp"

Game::Game(SDL_Surface *heroSpr,SDL_Surface *floorSpr, SDL_Surface *backgroudSpr, TTF_Font *messegeFont, SDL_Surface *screen)
{
    srand(SDL_GetTicks());

    hero = new Hero(heroSpr,screen);
    hero -> clip();

    base[0]= new Floor(20,0 ,SCREEN_HEIGHT-FLOOR_HEIGHT_WIDTH, floorSpr,screen);
    base[0]->clip_floor();
    for(int i = 1 ; i < FLOORS ; ++i)
    {
        base[i] = new Floor(SCREEN_HEIGHT - FLOOR_HEIGHT_WIDTH - i * 100,floorSpr,screen);
    }

    corner = new RightCorner(screen,messegeFont);
    background = new Background(backgroudSpr,screen);

    counterFloors=5;
    difficult = 1;
    inWhichFloorHeroIs=0;
    floor_level=0;
    camera_offset=0;
    start_game = false;
}

Game::Game()
{
    hero=NULL;
    background = NULL;
    corner = NULL;
    counterFloors=5;
    difficult = 1;
    inWhichFloorHeroIs=0;
    floor_level=0;
}
Game::~Game()
{
    delete hero;
    delete background;  //błąd
    delete corner;      //ok
    for(int i=0;i<FLOORS;++i) //błąd
        delete base[i];
    delete *base;       //błąd
}
void Game::setHud(Timer *t)
{
    if(!hero->jumping && !hero->falling)
    {
        corner->updateScore(base[inWhichFloorHeroIs]->counter * FLOORS + inWhichFloorHeroIs);
    }

    if(t->is_started())
    {
        corner->updateTime((difficult*TIME_TO_MORE_DIFFICULT + t->get_ticks() - TIME_TO_MORE_DIFFICULT)/1000);
    }

    corner->updateLevel(difficult);

    corner->updateFloor(floor_level);
}

void Game::draw()
{
    background->show();
    for(int i=0;i<FLOORS;++i)
        base[i]->show();
    corner->show();
    hero->show();
}

void Game::setCamera(Timer *t)
{
    bool game_run = (t->is_started()) && (!t->is_paused());

    //czy ruszaæ plansz¹
    if(!start_game && (hero->box.y<HERO_HEIGHT/3)){
        start_game=true;
    }

    //czy przyœpieszyæ
    if(game_run
        && (t->get_ticks()>TIME_TO_MORE_DIFFICULT)
        && (difficult < MAX_DIFFICULT))
    {
        ++difficult;
        floor_level=difficult/2;
        t->start();
    }

    //bohater zawsze na ekranie
    if((hero->box.y<HERO_HEIGHT))
    {
        if(hero->falling)camera_offset--;
        else camera_offset++;
        if(hero->box.y<HERO_HEIGHT/2) ++camera_offset;
        if(hero->box.y<HERO_HEIGHT/3) ++camera_offset;
    } else camera_offset=0;

    //ruch kamer¹
    if(game_run && start_game)
    {
        for(int i=0;i<FLOORS;++i)
            base[i]->set_camera(camera_offset+difficult);
        hero->set_camera(camera_offset+difficult);
        background->move(difficult/2+1+(camera_offset/16));
    }
}

void Game::newFloor()
{
    for(int i=0;i<FLOORS;++i)
    {
        if(base[i]->isDisappear(SCREEN_HEIGHT))
        {
            ++counterFloors;
            if(counterFloors % NEXT_FLOOR)base[i]->newfloor(difficult);
            else
            {
                for(int j=0;j<FLOORS;++j)
                {
                    base[j]->change_floor=true;
                }
                base[i]->newSuperFloor();
            }
        }
    }
}

void Game::behavior(Timer *tim)
{
    bool collision=false;
    bool checkCol=false;

    hero->move();

    for(int i=0;i<FLOORS;++i){
        checkCol=check_collision(hero->box,base[i]->box);
        collision|=checkCol;
        if(checkCol)inWhichFloorHeroIs=i;
    }
    if(hero->falling && collision )
        hero->moveUp(whereIsFloor(hero->box,base[inWhichFloorHeroIs]->box));

    if(!hero->jumping)
        hero->falling=!collision;

    if(!start_game && (hero->box.y<HERO_HEIGHT/3)){
        start_game=true;
    }
    if(!start_game && !tim->is_paused()) tim->start();
}

bool Game::check_collision( SDL_Rect A, SDL_Rect B )
{
    int heroLeftFoot,heroRightFoot,heroBottom;
    int floorLeft,floorRight,floorTop;
    heroBottom=A.y+A.h;
    heroLeftFoot=A.x+HERO_WIDTH/4;
    heroRightFoot=A.x+A.w-HERO_WIDTH/4;

    floorTop=B.y;
    floorLeft=B.x;
    floorRight=B.x+B.w;

    if(heroBottom>floorTop+32)return false;
    if(heroLeftFoot>floorRight)return false;
    if(heroRightFoot<floorLeft)return false;
    if(heroBottom<floorTop)return false;
    return true;
}

int Game::whereIsFloor(SDL_Rect A,SDL_Rect B)
{
    int heroBottom,floorTop;
    heroBottom=A.y+A.h;
    floorTop=B.y;
    return heroBottom-floorTop-1;
}
