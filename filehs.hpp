#ifndef FILEHS_HPP_INCLUDED
#define FILEHS_HPP_INCLUDED

#include <string>

class Filehs
{
    public:
    static const int MAX_SIZE = 5;
    int size;

    Filehs();
    ~Filehs();

    void sort();
    int getWorst();
    const char* getGamer(int i);
    const char* getScore(int i);
    int digits(int i);
    void save();
    void addRecord(std::string player, int score);
    private:

    std::string *gamer;
    int *score;

    int getmax(int x);
};

#endif // FILEHS_HPP_INCLUDED
