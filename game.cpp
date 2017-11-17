#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Timer.hpp"
#include <string>
#include <cstdlib>
#include <sstream>

//screen
const int SCREEN_WIDTH =640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 21;

//dims of textures
const int FLOOR_HEIGHT_WIDTH = 32;
const int FLOOR_MAX_LENGHT = 20;
const int HERO_WIDTH = 30;
const int HERO_HEIGHT = 60;

const int HERO_SPRITES = 15;
const int NUMBER_OF_FLOORS  = 10;

//hero cpils
const int HERO_STAND      = 0;
const int HERO_RUN_RIGHT  = 3;
const int HERO_RUN_LEFT   = 6;
const int HERO_JUMP       = 9;
const int HERO_JUMP_RIGHT =10;
const int HERO_JUMP_LEFT  =11;
const int HERO_FALL_RIGHT =12;
const int HERO_FALL_LEFT  =13;
const int HERO_FALL_DOWN  =14;

//game rules
const int GRAVITY=8;
const int HERO_SPEED=10;
const int HERO_JUMP_LEVEL1=11;
const int HERO_JUMP_LEVEL2=15;
const int HERO_JUMP_LEVEL3=21;

int DIFFICULT=1;
const int MAX_DIFFICULT = 4;
const int TIME_TO_MORE_DIFFICULT=30000;

int FLOOR_LEVEL=0;

//floor
const int FLOOR_LEVEL1_MAX_LENGHT=13;
const int FLOOR_LEVEL1_MIN_LENGHT=6;
const int FLOOR_LEVEL2_MAX_LENGHT=9;
const int FLOOR_LEVEL2_MIN_LENGHT=6;
const int FLOOR_LEVEL3= 6;

const int NEXT_FLOOR=20;


//surfeces
SDL_Surface* screen = NULL;
SDL_Surface* herosprite = NULL;
SDL_Surface* floortexture=NULL;
SDL_Surface* bg = NULL;
SDL_Surface* game_over=NULL;

SDL_Surface* messege_score = NULL;
SDL_Surface* messege_time = NULL;
SDL_Surface* messege_level=NULL;
SDL_Surface* messege_floor=NULL;



TTF_Font *messages_font = NULL;
SDL_Color messegeTextColor = { 255, 255, 255 };

//The event structure
SDL_Event event;

//hero sprite
SDL_Rect hero_clips[ HERO_SPRITES ];
SDL_Rect floor_clips [NUMBER_OF_FLOORS];


///////suport classes

class Hero
{
public:
    int slide;
    int jumpAltitude;
    int whichclip;
    int changeclip;
    int jumpDuration;
    int fallDuration;
    int xVel,yVel;
    int runDuration;
    int lastxVel;
    int level;
    SDL_Rect box;

    bool jumping,falling,jumpingOn;

    bool slidingLeft,slidingRight;
    Hero();

    void moveUp(int);
    void show();
    void handleevent();
    void move(bool p);
    void set_camera(int offset);
};

class Floor
{
    public:
    int length;
    int counter;
    int whichfloor;
    bool change_floor;
    SDL_Rect box;

    Floor(int l,int x,int y);
    Floor(int y);
    void show();
    void set_camera(int offset);
    bool isDisappear();
    void newfloor(int level);
    void init();
    void newSuperFloor();
    void floorToChange();
};
///////////////////suport functions

SDL_Surface *load_image( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );
    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0xFF, 0x00, 0xFF ) );
        }
    }
    return optimizedImage;
}


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

//////////////////
bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1) return false;

    screen= SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (screen==NULL) return false;

    if( TTF_Init() == -1 ) return false;

    SDL_WM_SetCaption( "Studnia", NULL );
    return true;
}

bool load_files()
{
    herosprite=load_image("jpg//hero3.png");
    if(herosprite == NULL) return false;

    bg=load_image("jpg//background.png");
    if(bg == NULL) return false;

    floortexture=load_image("jpg//floor.png");
    if(floortexture==NULL) return false;

    game_over=load_image("jpg//game-over.png");
    if(game_over== NULL) return false;

    messages_font=TTF_OpenFont("font//vademecum.ttf",32);
    if(messages_font == NULL) return false;

    return true;
}

void clean_up()
{
    SDL_FreeSurface( herosprite );
    SDL_FreeSurface( bg );
    SDL_FreeSurface( floortexture );
    SDL_FreeSurface( game_over );
    SDL_FreeSurface( messege_score );
    SDL_FreeSurface( messege_time );
    SDL_FreeSurface( messege_level );
    SDL_FreeSurface( messege_floor );


    TTF_CloseFont( messages_font );
    TTF_Quit();
    SDL_Quit();
}
void clip_hero()
{
    //Clip the sprite sheet
    hero_clips[ HERO_STAND ].x = 0;
    hero_clips[ HERO_STAND ].y = 0;
    hero_clips[ HERO_STAND ].w = HERO_WIDTH;
    hero_clips[ HERO_STAND ].h = HERO_HEIGHT;

    hero_clips[ HERO_STAND +1].x = 30;
    hero_clips[ HERO_STAND +1].y = 0;
    hero_clips[ HERO_STAND +1].w = HERO_WIDTH;
    hero_clips[ HERO_STAND +1].h = HERO_HEIGHT;

    hero_clips[ HERO_STAND +2].x = 60;
    hero_clips[ HERO_STAND +2].y = 0;
    hero_clips[ HERO_STAND +2].w = HERO_WIDTH;
    hero_clips[ HERO_STAND +2].h = HERO_HEIGHT;

    hero_clips[ HERO_RUN_RIGHT ].x = 90;
    hero_clips[ HERO_RUN_RIGHT ].y = 0;
    hero_clips[ HERO_RUN_RIGHT ].w = HERO_WIDTH;
    hero_clips[ HERO_RUN_RIGHT ].h = HERO_HEIGHT;

    hero_clips[ HERO_RUN_RIGHT +1].x = 120;
    hero_clips[ HERO_RUN_RIGHT +1].y = 0;
    hero_clips[ HERO_RUN_RIGHT +1].w = HERO_WIDTH;
    hero_clips[ HERO_RUN_RIGHT +1].h = HERO_HEIGHT;

    hero_clips[ HERO_RUN_RIGHT +2].x = 150;
    hero_clips[ HERO_RUN_RIGHT +2].y = 0;
    hero_clips[ HERO_RUN_RIGHT +2].w = HERO_WIDTH;
    hero_clips[ HERO_RUN_RIGHT +2].h = HERO_HEIGHT;

    hero_clips[ HERO_RUN_LEFT ].x = 180;
    hero_clips[ HERO_RUN_LEFT ].y = 0;
    hero_clips[ HERO_RUN_LEFT ].w = HERO_WIDTH;
    hero_clips[ HERO_RUN_LEFT ].h = HERO_HEIGHT;

    hero_clips[ HERO_RUN_LEFT +1].x = 210;
    hero_clips[ HERO_RUN_LEFT +1].y = 0;
    hero_clips[ HERO_RUN_LEFT +1].w = HERO_WIDTH;
    hero_clips[ HERO_RUN_LEFT +1].h = HERO_HEIGHT;

    hero_clips[ HERO_RUN_LEFT +2].x = 240;
    hero_clips[ HERO_RUN_LEFT +2].y = 0;
    hero_clips[ HERO_RUN_LEFT +2].w = HERO_WIDTH;
    hero_clips[ HERO_RUN_LEFT +2].h = HERO_HEIGHT;

    hero_clips[ HERO_JUMP ].x = 270;
    hero_clips[ HERO_JUMP ].y = 0;
    hero_clips[ HERO_JUMP ].w = HERO_WIDTH;
    hero_clips[ HERO_JUMP ].h = HERO_HEIGHT;

    hero_clips[ HERO_JUMP_RIGHT ].x = 300;
    hero_clips[ HERO_JUMP_RIGHT ].y = 0;
    hero_clips[ HERO_JUMP_RIGHT ].w = HERO_WIDTH;
    hero_clips[ HERO_JUMP_RIGHT ].h = HERO_HEIGHT;

    hero_clips[ HERO_JUMP_LEFT ].x = 330;
    hero_clips[ HERO_JUMP_LEFT ].y = 0;
    hero_clips[ HERO_JUMP_LEFT ].w = HERO_WIDTH;
    hero_clips[ HERO_JUMP_LEFT ].h = HERO_HEIGHT;

    hero_clips[ HERO_FALL_RIGHT ].x = 360;
    hero_clips[ HERO_FALL_RIGHT ].y = 0;
    hero_clips[ HERO_FALL_RIGHT ].w = HERO_WIDTH;
    hero_clips[ HERO_FALL_RIGHT ].h = HERO_HEIGHT;

    hero_clips[ HERO_FALL_LEFT ].x = 390;
    hero_clips[ HERO_FALL_LEFT ].y = 0;
    hero_clips[ HERO_FALL_LEFT ].w = HERO_WIDTH;
    hero_clips[ HERO_FALL_LEFT ].h = HERO_HEIGHT;

    hero_clips[ HERO_FALL_DOWN ].x = 420;
    hero_clips[ HERO_FALL_DOWN ].y = 0;
    hero_clips[ HERO_FALL_DOWN ].w = HERO_WIDTH;
    hero_clips[ HERO_FALL_DOWN ].h = HERO_HEIGHT;
}

void clip_floor()
{
    for(int i=0;i<NUMBER_OF_FLOORS;++i)
    {
        floor_clips[i].x = i*32;
        floor_clips[i].y = 0;
        floor_clips[i].h = 32;
        floor_clips[i].w = 32;
    }
}
int whereIsFloor(SDL_Rect A,SDL_Rect B)
{
    int heroBottom,floorTop;
    heroBottom=A.y+A.h;
    floorTop=B.y;
    return heroBottom-floorTop-1;
}

bool check_collision( SDL_Rect A, SDL_Rect B )
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

SDL_Surface* make_messege(SDL_Surface *surf,const char *desc)
{
    SDL_FreeSurface(surf);
    surf = TTF_RenderText_Solid( messages_font, desc, messegeTextColor );
    return surf;
}
/////////////////////////////timer fuctions

//////////////////////////////////////////////////////////////////////////////////////floor functions
Floor::Floor(int l,int x,int y)
{
    counter=0;
    whichfloor=0;
    change_floor=false;

    box.y=y;
    length=l;
    box.x=x;
    box.w=FLOOR_HEIGHT_WIDTH*l;
}

Floor::Floor(int y)
{
    counter=0;
    whichfloor=0;
    change_floor=false;
    box.y=y;
    init();
}

void Floor::init()
{
    length = rand() % (FLOOR_LEVEL1_MAX_LENGHT - FLOOR_LEVEL1_MIN_LENGHT) + FLOOR_LEVEL1_MIN_LENGHT;
    box.w = FLOOR_HEIGHT_WIDTH * length;
    box.x = rand() % (SCREEN_WIDTH - box.w);
 }
void Floor::show()
{
    for(int i=0;i<length;++i)
    {
        apply_surface(box.x + FLOOR_HEIGHT_WIDTH * i,box.y, floortexture, screen, &floor_clips[whichfloor]);
    }
}

void Floor::set_camera(int offset)
{
    box.y+=DIFFICULT+offset;
}

bool Floor::isDisappear()
{
    if(box.y>SCREEN_HEIGHT) return true;
    else return false;
}

void Floor::newfloor(int level)
{
    switch(level)
    {
        case 0:
            length = rand() % (FLOOR_LEVEL1_MAX_LENGHT - FLOOR_LEVEL1_MIN_LENGHT) + FLOOR_LEVEL1_MIN_LENGHT;
            box.w = FLOOR_HEIGHT_WIDTH * length;
            box.x = rand() % (SCREEN_WIDTH - box.w);
            break;
        case 1:
            length = rand() % (FLOOR_LEVEL2_MAX_LENGHT - FLOOR_LEVEL2_MIN_LENGHT) + FLOOR_LEVEL2_MIN_LENGHT;
            box.w = FLOOR_HEIGHT_WIDTH * length;
            box.x = rand() % (SCREEN_WIDTH - box.w);
            break;
        case 2:
            length = FLOOR_LEVEL3;
            box.w = FLOOR_HEIGHT_WIDTH * length;
            box.x = rand() % (SCREEN_WIDTH - box.w);
            break;
        default : break;
    }
    box.y -= 600;
    ++counter;

    box.x = rand() % (SCREEN_WIDTH - box.w);
    floorToChange();
 }

 void Floor::newSuperFloor()
 {

     box.y -= 600;
     length = 20;
     box.w = length * FLOOR_HEIGHT_WIDTH;
     box.x = 0;
     ++counter;
    floorToChange();
 }

void Floor::floorToChange()
{
    if(change_floor)
    {
        change_floor=false;
        whichfloor++;
        if(whichfloor==NUMBER_OF_FLOORS) whichfloor=0;
    }
}
//////////////////////////////////////////////////////////////////////////////////////hero functions
Hero::Hero()
{
    whichclip=0;
    changeclip=0;
    xVel=yVel=0;
    box.x=320;
    box.y=SCREEN_HEIGHT - FLOOR_HEIGHT_WIDTH - HERO_HEIGHT;
    box.w=HERO_WIDTH;
    box.h=HERO_HEIGHT;

    jumping=false;
    falling=false;
    jumpingOn=false;

    runDuration=0;
    level=0;

    fallDuration=GRAVITY;

}

void Hero::show()
{
    if ((xVel == 0) && (whichclip > HERO_STAND + 3)) whichclip = HERO_STAND;

    if ((xVel > 0) && ((whichclip < HERO_RUN_RIGHT) || (whichclip >= HERO_RUN_RIGHT + 3))) whichclip = HERO_RUN_RIGHT;
    if ((xVel < 0) && ((whichclip < HERO_RUN_LEFT) || (whichclip >= HERO_JUMP_LEFT + 3))) whichclip = HERO_RUN_LEFT;
    if (changeclip++ > 3)
    {
        changeclip = 0;
        if (++whichclip % 3 == 0) whichclip -= 3;
    }

    if ((jumping || falling) && xVel == 0) whichclip = HERO_JUMP;
    if (jumping && (xVel > 0)) whichclip = HERO_JUMP_RIGHT;
    if (jumping && (xVel < 0)) whichclip = HERO_JUMP_LEFT;

    if (falling && (xVel > 0)) whichclip = HERO_FALL_RIGHT;
    if (falling &&( xVel < 0)) whichclip = HERO_FALL_LEFT;

    if (box.y>SCREEN_HEIGHT-HERO_HEIGHT) whichclip=14;

    apply_surface( box.x, box.y, herosprite, screen ,&hero_clips[whichclip]);

}
void Hero::handleevent()
{
        //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_SPACE:
                jumpingOn=true;
                if(!falling)
                {
                  jumping=true;
                }
                break;

            case SDLK_LEFT:

                xVel -= HERO_SPEED;
                break;

            case SDLK_RIGHT:
                xVel +=HERO_SPEED;
                break;

            default : break;
        }
    }
    else if( event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_SPACE:
                jumpingOn=false;
                break;

            case SDLK_LEFT:
                xVel += HERO_SPEED;
                slidingLeft=true;
                break;

            case SDLK_RIGHT:
                xVel -= HERO_SPEED;
                slidingRight=true;
                break;

            default : break;
        }
    }
}
void Hero::move(bool pause){
    if (!pause)
    {

        //left right
        if(runDuration > 10)
        {
            box.x += xVel /2;
            level = 1;

            if(runDuration > 25)
            {
                box.x += xVel /2;
                level = 2;
            }
        }else level = 0;

        box.x += xVel;
        bool outOfScreen = ( box.x < 0 ) || ( box.x + HERO_WIDTH > SCREEN_WIDTH );

        if((xVel !=0 ) && (xVel == lastxVel) && !outOfScreen) ++runDuration;
        else runDuration=0;
        lastxVel = xVel;

        if( outOfScreen )
        {
            switch (level)
            {
                case 0 :
                    box.x -= xVel;
                    break;
                case 1 :
                    box.x -=( xVel + xVel/2);
                    break;
                case 2 :
                    box.x -= 2 * xVel;
                default: break;
            }

        }

        //up down
        if(!jumping)
            switch (level)
            {
                case 0:
                    jumpDuration=HERO_JUMP_LEVEL1;
                    jumpAltitude=HERO_JUMP_LEVEL1;
                    break;
                case 1:
                    jumpDuration=HERO_JUMP_LEVEL2;
                    jumpAltitude=HERO_JUMP_LEVEL2;
                    break;
                case 2:
                    jumpDuration=HERO_JUMP_LEVEL3;
                    jumpAltitude=HERO_JUMP_LEVEL3;
                    break;
                default : break;
            }
        if (jumping){
            box.y-=(--jumpAltitude)*2;
            if(!--jumpDuration){
                jumping=false;
                falling=true;
            }
        }

        if(falling) { //colision
            box.y+=(++fallDuration)/2;
            box.y += yVel;
        }else fallDuration=GRAVITY;
        if(!falling&&!jumping&&jumpingOn)jumping=true;
    }
}

void Hero::moveUp(int fc)
{
    box.y-=fc;
}

void Hero::set_camera(int offset)
{
    box.y+=DIFFICULT+offset;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////main
int main( int argc, char* args[] )
{
    bool quit=false;
    bool collision=false;
    bool checkCol;
    int inWhichFloorHeroIs=0;
    int offset=0;
    int counterFloors;
    int floors=6;
    int score=0;
    int time_game=0;
    int backbroundY=0;
    std::stringstream sstm;

    if(!init())         exit(EXIT_FAILURE);
    if(!load_files())   exit(EXIT_FAILURE);

    srand(SDL_GetTicks());

    Timer game_time;
    Timer fps;
    Hero hero;
    clip_hero();
    clip_floor();

    Floor *base[floors];
    base[0]= new Floor(20,0  ,SCREEN_HEIGHT-FLOOR_HEIGHT_WIDTH);

    for(int i = 1 ; i < floors ; ++i)
    {
        base[i] = new Floor(SCREEN_HEIGHT - FLOOR_HEIGHT_WIDTH - i * 100);
    }
    counterFloors=5;

    while( quit==false )
    {
        fps.start();
        //////////////////////////////////handlers
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT ) quit = true;
            if (!game_time.is_paused())hero.handleevent();
            if (event.type == SDL_KEYDOWN)
                if(event.key.keysym.sym == SDLK_p)
                    if(!game_time.is_paused())game_time.pause();
                    else game_time.unpause();
        }

        ////////////////////behavior
        hero.move(game_time.is_paused());

        collision=false;
        for(int i=0;i<floors;++i){
            checkCol=check_collision(hero.box,base[i]->box);
            collision|=checkCol;
            if(checkCol)inWhichFloorHeroIs=i;
        }
        if(hero.falling && collision )
            hero.moveUp(whereIsFloor(hero.box,base[inWhichFloorHeroIs]->box));

        if(!hero.jumping)
            hero.falling=!collision;


        /////////////////////////camera
        if(!game_time.is_started() && (hero.box.y<HERO_HEIGHT/3))
            game_time.start();

        if((game_time.is_started() && !game_time.is_paused())
           && (game_time.get_ticks()>TIME_TO_MORE_DIFFICULT)
           && (DIFFICULT < MAX_DIFFICULT))
        {
            ++DIFFICULT;
            FLOOR_LEVEL=DIFFICULT/2;
            game_time.start();
        }

        if((hero.box.y<HERO_HEIGHT))
        {
            if(hero.falling)offset--;
            else offset++;
            if(hero.box.y<HERO_HEIGHT/2) ++offset;
            if(hero.box.y<HERO_HEIGHT/3) ++offset;
        } else offset=0;

        if(game_time.is_started() && !game_time.is_paused()){
            for(int i=0;i<floors;++i)
                base[i]->set_camera(offset);
            hero.set_camera(offset);
        }

        if(game_time.is_started() && !game_time.is_paused())backbroundY-=(DIFFICULT/2+1+(offset/16));
        if( backbroundY <= -bg->w )
        {
            backbroundY = 0;
        }

        /////////////////////////new floors
        for(int i=0;i<floors;++i)
        {
            if(base[i]->isDisappear())
            {
                ++counterFloors;
                if(counterFloors % NEXT_FLOOR)base[i]->newfloor(FLOOR_LEVEL);
                else
                {
                    for(int j=0;j<floors;++j)
                    {
                        base[j]->change_floor=true;
                    }
                     base[i]->newSuperFloor();
                }
            }
        }

        ///////////////////////////set navigation

        if(!hero.jumping && !hero.falling)
        if(score<base[inWhichFloorHeroIs]->counter * floors + inWhichFloorHeroIs)
            score=base[inWhichFloorHeroIs]->counter * floors + inWhichFloorHeroIs;
        sstm << "Score : " << score;
        messege_score=make_messege(messege_score,sstm.str().c_str());
        sstm.str("");

        if(game_time.is_started()) time_game=(DIFFICULT*TIME_TO_MORE_DIFFICULT + game_time.get_ticks() - TIME_TO_MORE_DIFFICULT)/1000;
        sstm << "Time: " << time_game << "s" ;
        messege_time = make_messege(messege_time,sstm.str().c_str());
        sstm.str("");

        sstm << "Level : " << DIFFICULT;
        messege_level = make_messege(messege_level, sstm.str().c_str());
        sstm.str("");

        switch (FLOOR_LEVEL)
        {
            case 0:
                sstm << "Large";
                break;
            case 1:
                sstm << "Medium";
                break;
            case 2:
                sstm << "Small";
                break;
            default:break;
        }

        sstm << " floor!";
        messege_floor= make_messege(messege_floor, sstm.str().c_str());
        sstm.str("");

        /////////////////////////////drawing
        apply_surface(0,backbroundY,bg,screen);
        apply_surface(0,backbroundY+bg->w,bg,screen);
        for(int i=0;i<floors;++i)
            base[i]->show();

        hero.show();

        apply_surface( 0, 0, messege_score, screen );
        apply_surface( 0, 30,messege_time, screen );
        apply_surface( 0, 60,messege_level, screen );
        apply_surface( 0, 90,messege_floor,screen );


        //////////////////// end of game
        if(hero.box.y > SCREEN_HEIGHT)
        {
            game_time.stop();
            apply_surface(120,40,game_over,screen);
            hero.box.y = 700;
        }

        if(!game_time.is_paused())
            if( SDL_Flip( screen ) == -1 ) exit(EXIT_FAILURE);

        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
        ////////testing
//        std::stringstream caption;
//        caption << "test" << score;
//        SDL_WM_SetCaption( caption.str().c_str(), NULL );
    }

    clean_up();

    return 0;
}
