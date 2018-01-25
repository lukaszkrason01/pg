#include "filehs.hpp"

#include <fstream>

Filehs::Filehs()
{
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
            }
            else
            {
                getline ( load , temp );
               // if(i % 2 == 0)
            }
        }
        size = i/2;
        load.close();
    }
}
