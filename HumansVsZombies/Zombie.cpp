#include "Zombie.h"
#include "City.h"
#include "GameSpecs.h"
#include <algorithm>
#include <random>

//Default constructor
Zombie::Zombie() {
    breedPoints = 0;
    starvePoints = 0;
}

//Constructor with City parameters
Zombie::Zombie(City *city, int width, int height) : Organism(city, width, height) {
    breedPoints = 0;
    starvePoints = 0;
}

//Method to move Zombie
void Zombie::move() {
    //Call method to return vector of directions containing Humans
    checkForPeople();
    //If the vector is not empty
    if (!peopleVector.empty()) {
        auto rng1 = default_random_engine {};
        shuffle(begin(peopleVector), end(peopleVector), rng1);

        if(peopleVector.front() == directions(NORTH)) {
            //Delete Human being eaten
            delete (city->grid[x][y-1]);
            //Set Zombie in that space
            city->grid[x][y-1] = this;
            //Set current Zombie space to null
            city->setAt(nullptr,x,y);
            //Reset starvePoints
            starvePoints = 0;
            y--;
            peopleVector.clear();
            return;
        }
        else if (peopleVector.front() == directions(NORTH_EAST)){
            delete (city->grid[x+1][y-1]);
            city->grid[x+1][y-1] = this;
            city->setAt(nullptr,x,y);
            starvePoints = 0;
            x++;
            y--;
            peopleVector.clear();
            return;
        }
        else if (peopleVector.front() == directions(EAST)){
            delete (city->grid[x+1][y]);
            city->grid[x+1][y] = this;
            city->setAt(nullptr,x,y);
            starvePoints = 0;
            x++;
            peopleVector.clear();
            return;
        }
        else if(peopleVector.front() == directions(SOUTH_EAST)){
            delete (city->grid[x+1][y+1]);
            city->grid[x+1][y+1] = this;
            city->setAt(nullptr,x,y);
            starvePoints = 0;
            x++;
            y++;
            peopleVector.clear();
            return;
        }
        else if (peopleVector.front() == directions(SOUTH)){
            delete (city->grid[x][y+1]);
            city->grid[x][y+1] = this;
            city->setAt(nullptr,x,y);
            starvePoints = 0;
            y++;
            peopleVector.clear();
            return;
        }
        else if (peopleVector.front() == directions(SOUTH_WEST)){
            delete (city->grid[x-1][y+1]);
            city->grid[x-1][y+1] = this;
            city->setAt(nullptr,x,y);
            starvePoints = 0;
            x--;
            y++;
            peopleVector.clear();
            return;
        }
        else if (peopleVector.front() == directions(WEST)){
            delete (city->grid[x-1][y]);
            city->grid[x-1][y] = this;
            city->setAt(nullptr,x,y);
            starvePoints = 0;
            x--;
            peopleVector.clear();
            return;
        }
        else if (peopleVector.front() == directions(NORTH_WEST)){
            delete (city->grid[x-1][y-1]);
            city->grid[x-1][y-1] = this;
            city->setAt(nullptr,x,y);
            starvePoints = 0;
            x--;
            y--;
            peopleVector.clear();
            return;
        }
    }

    //If we reach here it means there were no humans to eat...
    //Call method to return vector of possible directions to move
    checkSurroundings();
    if (!dirVector.empty()) {
        auto rng2 = default_random_engine {};
        shuffle(begin(dirVector), end(dirVector), rng2);
        //Move Zombie to randomly selected direction
        if(dirVector.front() == directions(NORTH)) {
            city->setAt(city->getAt(x, y), x, y - 1);
            city->setAt(nullptr, x, y);
            y--;
        }
        else if (dirVector.front() == directions(NORTH_EAST)){
            city->setAt(city->getAt(x, y), x + 1, y - 1);
            city->setAt(nullptr, x, y);
            x++;
            y--;
        }
        else if (dirVector.front() == directions(EAST)){
            city->setAt(city->getAt(x, y), x + 1, y);
            city->setAt(nullptr, x, y);
            x++;
        }
        else if(dirVector.front() == directions(SOUTH_EAST)){
            city->setAt(city->getAt(x, y), x + 1, y + 1);
            city->setAt(nullptr, x, y);
            x++;
            y++;
        }
        else if (dirVector.front() == directions(SOUTH)){
            city->setAt(city->getAt(x, y), x, y + 1);
            city->setAt(nullptr, x, y);
            y++;
        }
        else if (dirVector.front() == directions(SOUTH_WEST)){
            city->setAt(city->getAt(x, y), x - 1, y + 1);
            city->setAt(nullptr, x, y);
            x--;
            y++;
        }
        else if (dirVector.front() == directions(WEST)){
            city->setAt(city->getAt(x, y), x - 1, y);
            city->setAt(nullptr, x, y);
            x--;
        }
        else if (dirVector.front() == directions(NORTH_WEST)){
            city->setAt(city->getAt(x, y), x - 1, y - 1);
            city->setAt(nullptr, x, y);
            x--;
            y--;
        }
        dirVector.clear();
    }
    starvePoints++;
}

//Method to return Organizm type of Zombie
char Zombie::getType() {
    return ZOMBIE_CH;
}

//Method to breed Zombies
void Zombie::breed() {
    breedPoints++;
    if (breedPoints > ZOMBIE_BREED){
        //Call method to return vector of directions containing Humans
        checkForPeople();
        if (!peopleVector.empty()) {
            auto rng2 = default_random_engine {};
            shuffle(begin(dirVector), end(dirVector), rng2);

            //Select random direction containing a Human, delete the Human, create a new Zombie there
            if(peopleVector.front() == directions(NORTH)) {
                delete (city->grid[x][y-1]);
                Zombie *newZombie = new Zombie(city,x,y-1);
            }
            else if (peopleVector.front() == directions(NORTH_EAST)){
                delete (city->grid[x+1][y-1]);
                Zombie *newZombie = new Zombie(city,x+1,y-1);
            }
            else if (peopleVector.front() == directions(EAST)){
                delete (city->grid[x+1][y]);
                Zombie *newZombie = new Zombie(city,x+1,y);
            }
            else if(peopleVector.front() == directions(SOUTH_EAST)){
                delete (city->grid[x+1][y+1]);
                Zombie *newZombie = new Zombie(city,x+1,y+1);
            }
            else if (peopleVector.front() == directions(SOUTH)){
                delete (city->grid[x][y+1]);
                Zombie *newZombie = new Zombie(city,x,y+1);
            }
            else if (peopleVector.front() == directions(SOUTH_WEST)){
                delete (city->grid[x-1][y+1]);
                Zombie *newZombie = new Zombie(city,x-1,y+1);
            }
            else if (peopleVector.front() == directions(WEST)){
                delete (city->grid[x-1][y]);
                Zombie *newZombie = new Zombie(city,x-1,y);
            }
            else if (peopleVector.front() == directions(NORTH_WEST)){
                delete (city->grid[x-1][y-1]);
                Zombie *newZombie = new Zombie(city, x - 1, y - 1);
            }
            breedPoints = 0;
            peopleVector.clear();
        }
    }
}

bool Zombie::starve(){
    if (starvePoints > ZOMBIE_STARVE){
        return true;
    }
    else{
        return false;
    }
}

//Method to check all directions for a space to move
void Zombie::checkSurroundings() {
    //Check North
    if ((y > 0) && (city->getAt(x, y - 1) == nullptr)) {
        dirVector.push_back(directions(NORTH));
    }
    //Check North-East
    if ((y>0 && x<GRIDSIZE - 1) && (city->getAt(x+1,y-1) == nullptr)){
        dirVector.push_back(directions(NORTH_EAST));
    }
    //Check East
    if ((x < GRIDSIZE - 1) && (city->getAt(x + 1, y) == nullptr)) {
        dirVector.push_back(directions(EAST));
    }
    //Check South-East
    if ((y<GRIDSIZE - 1 && x<GRIDSIZE - 1) && (city->getAt(x+1,y+1) == nullptr)){
        dirVector.push_back(directions(SOUTH_EAST));
    }
    //Check South
    if ((y > GRIDSIZE - 1) && (city->getAt(x, y + 1) == nullptr)) {
        dirVector.push_back(directions(SOUTH));
    }
    //Check South-West
    if ((y<GRIDSIZE - 1 && x>0) && (city->getAt(x-1,y+1) == nullptr)){
        dirVector.push_back(directions(SOUTH_WEST));
    }
    //Check West
    if ((x > 0) && (city->getAt(x - 1, y) == nullptr)) {
        dirVector.push_back(directions(WEST));
    }
    //Check North-West
    if ((y>0 && x>0) && (city->getAt(x-1,y-1) == nullptr)){
        dirVector.push_back(directions(NORTH_WEST));
    }
}

//Method to check all directions for a Human
void Zombie::checkForPeople() {
    if ((y > 0) && (city->getAt(x, y - 1) != nullptr) && (city->getAt(x,y-1)->getType() == HUMAN_CH)) {
        peopleVector.push_back(directions(NORTH));
    }
    //Check North-East
    if ((y > 0 && x < (GRIDSIZE - 1)) && (city->getAt(x+1, y - 1) != nullptr) && (city->getAt(x+1,y-1)->getType() == HUMAN_CH)){
        peopleVector.push_back(directions(NORTH_EAST));
    }
    //Check East
    if ((x < GRIDSIZE - 1) && (city->getAt(x+1, y) != nullptr) && (city->getAt(x+1,y)->getType() == HUMAN_CH)) {
        peopleVector.push_back(directions(EAST));
    }
    //Check South-East
    if ((y<GRIDSIZE - 1 && x<GRIDSIZE - 1) && (city->getAt(x+1, y+1) != nullptr) && (city->getAt(x+1,y+1)->getType() == HUMAN_CH)){
        peopleVector.push_back(directions(SOUTH_EAST));
    }
    //Check South
    if ((y > GRIDSIZE - 1) && (city->getAt(x, y+1) != nullptr) && (city->getAt(x,y+1)->getType() == HUMAN_CH)) {
        peopleVector.push_back(directions(SOUTH));
    }
    //Check South-West
    if ((y<GRIDSIZE - 1 && x>0) && (city->getAt(x-1, y+1) != nullptr) && (city->getAt(x-1,y+1)->getType() == HUMAN_CH)){
        peopleVector.push_back(directions(SOUTH_WEST));
    }
    //Check West
    if ((x > 0) && (city->getAt(x-1, y) != nullptr) && (city->getAt(x-1,y)->getType() == HUMAN_CH)) {
        peopleVector.push_back(directions(WEST));
    }
    //Check North-West
    if ((y>0 && x>0) && (city->getAt(x-1, y - 1) != nullptr) && (city->getAt(x-1,y-1)->getType() == HUMAN_CH)){
        peopleVector.push_back(directions(NORTH_WEST));
    }
}

Zombie::~Zombie() = default;

