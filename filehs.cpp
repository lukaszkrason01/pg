#include "filehs.hpp"

#include <fstream>
#include <cstdlib>

Filehs::Filehs()
{
    gamer = new std::string[MAX_SIZE];
    score = new int[MAX_SIZE];
    std::ifstream load( "data//fame.txt" );

    if(load != NULL)
    {
        std::string temp;
        int i;
        for ( i = 0 ; i < MAX_SIZE*2 ; ++i)
        {
            if( load.eof()  )
            {
                break;
                for (int j=i/2 ; j<MAX_SIZE;++j)
                {
                     score[j] = 0;
                     gamer[j] = "";
                }

            }
            else
            {
                getline ( load , temp );
                if(i % 2 == 0) gamer[i/2] = temp;
                if(i % 2 == 1) score[i/2] = atoi(temp.c_str());
            }
        }
        load.close();

        size = i/2;
        sort();
    }
    else
        for (int j=0 ; j<MAX_SIZE;++j)
        {
            score[j] = 0;
            gamer[j] = "";
        }

}
Filehs::~Filehs()
{
    save();
    delete gamer;
    delete score;
}

const char* Filehs::getGamer(int i)
{
    return gamer[i].c_str();
}

const char* Filehs::getScore(int i)
{
    char *result= new char[16];
    if(score[i]>0)itoa(score[i],result,10);
    else result[0]='\0';
    return result;
}
void Filehs::save()
{
    std::ofstream save( "data//fame.txt" );

    for (int i = 0 ; i < size ; ++i)
    {
        save << gamer[i] << "\n";
        save << score[i] << "\n";
    }

    save.close();
}

int Filehs::getWorst()
{
    return score[size-1];
}
void Filehs::sort()
{
    std::string new_gamer = "";
    int swap=0;

    int places;
    for (int i = 0; i < size ; ++i)
    {
        places = getmax(i);

        swap = score [i];
        score[i] = score[places];
        score[places] = swap;

        new_gamer = gamer [i];
        gamer[i] = gamer[places];
        gamer[places] = new_gamer;
    }
}


int Filehs::getmax(int i)
{
    int max = 0;
    int p=0;
    for ( ; i < size ; ++i)
    {
        if(max < score[i] )
        {
            max = score[i];
            p=i;
        }
    }

    return p;
}
