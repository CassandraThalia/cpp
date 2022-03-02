#include "Human.h"
#include "City.h"
#include "GameSpecs.h"
#include <algorithm>
#include <random>

//Human default constructor (set breed points to 0)
Human::Human() {
    breedPoints = 0;
}

//Human constructor w/ City parameters
Human::Human(City *city, int width, int height) : Organism(city, width, height) {
    breedPoints = 0;
}

//Method to move Human
void Human::move() {
    //Call method to return vector of possible directions to move
    checkSurroundings();
    auto rng = default_random_engine {};
    shuffle(begin(dirVector), end(dirVector), rng);
    //If the vector is not empty
    if (!dirVector.empty()){
        //Select first direction from shuffled vector and move Human
        if(dirVector.front() == directions(NORTH)) {
            city->setAt(city->getAt(x, y), x, y - 1);
            city->setAt(nullptr, x, y);
            y--;
        }
        else if(dirVector.front() == directions(SOUTH)) {
            city->setAt(city->getAt(x, y), x, y + 1);
            city->setAt(nullptr, x, y);
            y++;
        }
        else if(dirVector.front() == directions(WEST)) {
            city->setAt(city->getAt(x, y), x - 1, y);
            city->setAt(nullptr, x, y);
            x--;
        }
        else if(dirVector.front() == directions(EAST)) {
            city->setAt(city->getAt(x, y), x + 1, y);
            city->setAt(nullptr, x, y);
            x++;
        }
    }
    dirVector.clear();
}

//Method to check if Organism is Human
char Human::getType() {
    return HUMAN_CH;
}

//Method to breed Human
void Human::breed() {
    //Increase breed points each turn
    breedPoints++;
    if (breedPoints == HUMAN_BREED){
        //Set breed points to 0 even if Human doesn't move
        breedPoints = 0;

        //Call method to return vector of possible directions to move
        checkSurroundings();
        auto rng = default_random_engine {};
        shuffle(begin(dirVector), end(dirVector), rng);

        //If the vector is not empty
        if (!dirVector.empty()) {
            //Select direction and create new Human in that grid space
            if (dirVector.front() == directions(NORTH)) {
                Human *newHuman = new Human(city, x, y - 1);
            } else if (dirVector.front() == directions(SOUTH)) {
                Human *newHuman = new Human(city, x, y + 1);
            } else if (dirVector.front() == directions(WEST)) {
                Human *newHuman = new Human(city, x - 1, y);
            } else if (dirVector.front() == directions(EAST)) {
                Human *newHuman = new Human(city, x + 1, y);
            }
        }
        dirVector.clear();
    }
}

//Method to check each space around Human (excluding Diagonals) and return a vector of possible directions to move or breed
void Human::checkSurroundings() {
    //Check North
    if ((y > 0) && (city->getAt(x, y - 1) == nullptr)) {
        dirVector.push_back(directions(NORTH));
    }
    //Check South
    if ((y > GRIDSIZE - 1) && (city->getAt(x, y + 1) == nullptr)) {
        dirVector.push_back(directions(SOUTH));
    }
    //Check West
    if ((x > 0) && (city->getAt(x - 1, y) == nullptr)) {
        dirVector.push_back(directions(WEST));
    }
    //Check East
    if ((x < GRIDSIZE - 1) && (city->getAt(x + 1, y) == nullptr)) {
        dirVector.push_back(directions(EAST));
    }
}

bool Human::starve() {
    return false;
}

Human::~Human() = default;



