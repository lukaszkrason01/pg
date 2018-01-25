#ifndef FILEHS_HPP_INCLUDED
#define FILEHS_HPP_INCLUDED

#include <string>

class Filehs
{
    public:
    static const int MAX_SIZE = 5;

    int size;
    std::string gamer[MAX_SIZE];
    int score[MAX_SIZE];

    Filehs();
};

#endif // FILEHS_HPP_INCLUDED
