#include "Floor.hpp"

SDL_Rect Floor::floor_clips[NUMBER_OF_FLOORS];

Floor::Floor(int l,int x,int y, SDL_Surface* sur,SDL_Surface* sc) : Texture(sur,sc)
{
    counter=0;
    whichfloor=0;
    change_floor=false;

    box.y=y;
    length=l;
    box.x=x;
    box.w=FLOOR_HEIGHT_WIDTH*l;
}

Floor::Floor(int y, SDL_Surface* sur,SDL_Surface* sc) : Texture(sur,sc)
{
    counter=0;
    whichfloor=0;
    change_floor=false;
    box.y=y;
    init();
}

Floor::~Floor()
{

}
void Floor::init()
{
    length = rand() % (FLOOR_LEVEL1_MAX_LENGHT - FLOOR_LEVEL1_MIN_LENGHT) + FLOOR_LEVEL1_MIN_LENGHT;
    box.w = FLOOR_HEIGHT_WIDTH * length;
    box.x = rand() % (SCREEN_WIDTH - box.w);
 }
void Floor::show()
{

    if(box.y>-FLOOR_HEIGHT_WIDTH && box.y<480)
    {
        SDL_Rect offset;

        for(int i=0;i<length;++i)
        {
            offset=box;
            offset.x+=FLOOR_HEIGHT_WIDTH*i;
            apply_surface(&offset,&floor_clips[whichfloor]);

        }
    }

}

void Floor::set_camera(int offset)
{
    box.y+=offset;
}

bool Floor::isDisappear(int sh)
{
    if(box.y>sh) return true;
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
        default:
            length = FLOOR_LEVEL3;
            box.w = FLOOR_HEIGHT_WIDTH * length;
            box.x = rand() % (SCREEN_WIDTH - box.w);
        break;
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

void Floor::clip_floor()
{
    for(int i=0;i<NUMBER_OF_FLOORS;++i)
    {
        floor_clips[i].x = i*32;
        floor_clips[i].y = 0;
        floor_clips[i].h = 32;
        floor_clips[i].w = 32;
    }
}
