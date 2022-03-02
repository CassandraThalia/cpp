#ifndef HUMANSVSZOMBIES_ORGANISM_H
#define HUMANSVSZOMBIES_ORGANISM_H

#include <iostream>
#include <vector>

using namespace std;

class City;

class Organism
{
protected:
    int x;
    int y;
    City *city;

    enum directions {WEST, NORTH_WEST, NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST};

public:
    Organism();
    Organism(City *city, int x, int y);
    virtual ~Organism();

    virtual void move() = 0;
    virtual char getType() = 0;
    virtual void breed() = 0;
    virtual bool starve() = 0;

    bool moved;
    vector<directions> dirVector;
};

#endif //HUMANSVSZOMBIES_ORGANISM_H
