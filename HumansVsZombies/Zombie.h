//
// Created by cassa on 2021-12-14.
//

#ifndef HUMANSVSZOMBIES_ZOMBIE_H
#define HUMANSVSZOMBIES_ZOMBIE_H

#include "Organism.h"

class Zombie : public Organism
{
public:
    Zombie();
    Zombie( City *city, int width, int height );
    virtual ~Zombie();

    void move() override;
    void breed() override;
    char getType() override;
    void checkSurroundings();
    void checkForPeople();

    bool starve() override;

private:
    int starvePoints;
    int breedPoints;
    vector<directions> peopleVector;
};
#endif //HUMANSVSZOMBIES_ZOMBIE_H
