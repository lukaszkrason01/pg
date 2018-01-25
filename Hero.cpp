#include "Hero.hpp"

Hero::Hero(SDL_Surface *sur,SDL_Surface *sc):Texture(sur,sc)
{

    whichclip=0;
    changeclip=0;
    xVel=yVel=0;
    box.x=320;
    box.y=480-HERO_HEIGHT-32;
    box.w=HERO_WIDTH;
    box.h=HERO_HEIGHT;

    jumping=false;
    falling=false;
    jumpingOn=false;

    runDuration=0;
    level=0;

    fallDuration=GRAVITY;
}

Hero::~Hero()
{

}
void Hero::show()
{

        if ((xVel == 0) && (whichclip > HERO_STAND + 3)) whichclip = HERO_STAND;

        if ((xVel > 0) && ((whichclip < HERO_RUN_RIGHT) || (whichclip >= HERO_RUN_RIGHT + 3))) whichclip = HERO_RUN_RIGHT;
        if ((xVel < 0) && ((whichclip < HERO_RUN_LEFT) || (whichclip >= HERO_RUN_LEFT + 3))) whichclip = HERO_RUN_LEFT;
        if (((changeclip++ > 3)))
        {
            changeclip = 0;
            if (++whichclip % 3 == 0) whichclip -= 3;
        }

        if ((jumping || falling) && (xVel == 0)) whichclip = HERO_JUMP;
        if ((jumping) && (xVel > 0)) whichclip = HERO_JUMP_RIGHT;
        if ((jumping) && (xVel < 0)) whichclip = HERO_JUMP_LEFT;

        if (falling && (xVel > 0)) whichclip = HERO_FALL_RIGHT;
        if (falling && (xVel < 0)) whichclip = HERO_FALL_LEFT;

        if (box.y>480-HERO_HEIGHT) whichclip=14;
    apply_surface(&box,&hero_clips[whichclip]);
}
void Hero::handle_event(SDL_Event event,bool pause)
{
        //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_SPACE:
                jumpingOn=true;
                if(!falling && !pause)
                {
                  jumping=true;
                }
                break;

            case SDLK_LEFT:
                xVel -= HERO_SPEED;
                break;

            case SDLK_RIGHT:
                xVel += HERO_SPEED;
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
                break;

            case SDLK_RIGHT:
                xVel -= HERO_SPEED;
                break;

            default : break;
        }
    }
}
void Hero::move(){
        //left right
        if(runDuration > SPEED_DURATION_1)
        {
            box.x += xVel /3;
            level = 1;

            if(runDuration > SPEED_DURATION_2)
            {
                box.x += xVel /2;
                level = 2;
            }
        }else level = 0;

        box.x += xVel;

        if((xVel !=0 ) &&
           (xVel == lastxVel) &&
           (( box.x > 0 ) || ( box.x + HERO_WIDTH < SCREEN_WIDTH )))
                ++runDuration;
        else runDuration=0;
        lastxVel = xVel;

        if( box.x < 0  )
        {
            box.x = 0;
        }

        if(box.x + HERO_WIDTH > SCREEN_WIDTH)
        {
            box.x = SCREEN_WIDTH-HERO_WIDTH;
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
        if(!falling&&jumpingOn)jumping=true;

}

void Hero::moveUp(int fc)
{
    box.y-=fc;
}

void Hero::set_camera(int offset)
{
    box.y+=offset;
}



void Hero::clip()
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
