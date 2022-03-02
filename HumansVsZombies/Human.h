#ifndef HUMANSVSZOMBIES_HUMAN_H
#define HUMANSVSZOMBIES_HUMAN_H

#include "Organism.h"
#include <vector>

class Human : public Organism
{
public:
    Human();
    Human( City *city, int width, int height );
    virtual ~Human();

    void move() override;
    char getType() override;
    void breed() override;
    bool starve() override;

    void checkSurroundings();

private:
    int breedPoints;
};

#endif //HUMANSVSZOMBIES_HUMAN_H
