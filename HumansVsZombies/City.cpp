#include <windows.h>
#include <iostream>
#include "City.h"
#include "Organism.h"
#include "Human.h"
#include "Zombie.h"
#include "GameSpecs.h"

//Default city constructor (set all grids to null Organism)
City::City() {
    for (int i=0; i<GRIDSIZE; i++)
    {
        for (int j=0; j<GRIDSIZE; j++)
        {
            grid[i][j]=nullptr;
        }
    }
}

//Default City destructor (delete all organisms from grid)
City::~City() {
    for (int i=0; i<GRIDSIZE; i++)
    {
        for (int j=0; j<GRIDSIZE; j++)
        {
            if (grid[i][j]!=nullptr) delete (grid[i][j]);
        }
    }
}

//City Organism getter
Organism *City::getAt(int x, int y) {
    if ((x>=0) && (x<GRIDSIZE) && (y>=0) && (y<GRIDSIZE))
        return grid[x][y];
    return nullptr;
}

//City Organism setter
void City::setAt(Organism *organism, int x, int y) {
    if ((x>=0) && (x<GRIDSIZE) && (y>=0) && (y<GRIDSIZE))
    {
        grid[x][y] = organism;
    }
}

//Method to change text colour
void City::color(int c)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
}

//Output stream override
ostream &operator<<(ostream &output, City &city) {
    //Loop through each space on grid and output appropriate char
    for (int i=0; i<GRIDSIZE; i++)
    {
        for (int j=0; j<GRIDSIZE; j++)
        {
            if (city.getAt(j, i) == nullptr)
                output << SPACE_CH;
            else if (city.getAt(j, i)->getType()==HUMAN_CH){
                city.color(HUMAN_COLOR);
                output << HUMAN_CH;
            }
            else{
                city.color(ZOMBIE_COLOR);
                output << ZOMBIE_CH;
            }
            city.color(BASIC_COLOR);
        }
        output << endl;
    }
    //Output running totals
    city.color(HUMAN_COLOR);
    output << "HUMANS REMAINING: " << city.humanCount << endl;
    city.color(ZOMBIE_COLOR);
    output << "ZOMBIES REMAINING: " << city.zombieCount << endl;
}

//Method to populate city with Organisms
void City::create() {
    //Loop to create new Zombies at random poitns
    zombieCount = 0;
    while (zombieCount < ZOMBIE_STARTCOUNT)
    {
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;

        if (this->getAt(x,y)==nullptr)
        {
            zombieCount++;
            Zombie *z1 = new Zombie(this,x,y);
        }
    }

    //Loop to create new Humans at random points
    humanCount = 0;
    while (humanCount < HUMAN_STARTCOUNT)
    {
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;

        if (this->getAt(x,y)==nullptr)
        {
            humanCount++;
            Human *h1 = new Human(this,x,y);
        }
    }
}

//Method to reset running totals & move bools
void City::reset() {
    humanCount = 0;
    zombieCount = 0;
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if (grid[i][j] != nullptr){
                grid[i][j]->moved = false;
            }
        }
    }
}

//Method to move all Organisms
void City::moveOrganisms() {
    //Loop through Zombies; if Zombie has not yet been moved this turn, move it
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if ((grid[i][j]!= nullptr) && (grid[i][j]->getType()==ZOMBIE_CH)){
                if (grid[i][j]->moved == false)
                {
                    grid[i][j]->moved = true;
                    grid[i][j]->move();
                }
            }
        }
    }
    //Loop through Humans; if Human has not yet been moved this turn, move it
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if ((grid[i][j] != nullptr) && (grid[i][j]->getType() == HUMAN_CH)) {
                if (grid[i][j]->moved == false)
                {
                    grid[i][j]->moved = true;
                    grid[i][j]->move();
                }
            }
        }
    }
    //Loop through Zombies to check if any have starved this turn
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if ((grid[i][j]!=nullptr) &&
                (grid[i][j]->getType()==ZOMBIE_CH))
            {
                if (grid[i][j]->starve())
                {
                    //Delete Zombie at grid space
                    delete (grid[i][j]);
                    //Create new Human to replace Zombie
                    Human *newHuman = new Human(this, i, j);
                }
            }
        }
    }

}

//Method to breed Organisms (call Breed method for each)
void City::breedOrganisms() {
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if ((grid[i][j]!=nullptr) && (grid[i][j]->moved==true))
            {
                grid[i][j]->breed();
            }
        }
    }
}

//Method to loop through every space on grid and count total of Humand and Zombies
void City::countOrganisms() {
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if ((grid[i][j] != nullptr) && (grid[i][j]->getType() == ZOMBIE_CH)) {
                zombieCount++;
            }
            else if ((grid[i][j] != nullptr) && (grid[i][j]->getType() == HUMAN_CH)){
                humanCount++;
            }
        }
    }
}

//Loss Condition Method
bool City::hasDiversity() {
    bool hasHuman;
    bool hasZombie;
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if ((grid[i][j] != nullptr) && (grid[i][j]->getType()==ZOMBIE_CH)){
                hasZombie = true;
            }
            else if ((grid[i][j] != nullptr) && (grid[i][j]->getType()==HUMAN_CH)){
                hasHuman = true;
            }
        }
    }
    //As long as one of each Zombie and Humans exist, method will return true
    if (hasHuman && hasZombie){
        return true;
    }
    //If only one type remains, return false
    else{
        return false;
    }
}

//References:
//I followed this as a starting guide:
//https://scholaron.com/textbook-solutions/solutions-for-absolute-c-5th-edition-chapter-15-2-97198-9780132989923







