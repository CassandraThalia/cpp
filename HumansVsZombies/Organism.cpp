//
// Created by cassa on 2021-12-14.
//

#include "Organism.h"
#include "City.h"
#include "GameSpecs.h"

//Default constructor
Organism::Organism() {
    city = nullptr;
    moved = false;
    x = 0;
    y = 0;
}

//Consctructor with City parameters
Organism::Organism(City *city, int x, int y) {
    this->city = city;
    moved = false;
    this->x=x;
    this->y=y;
    city->setAt(this, x, y);
}

Organism::~Organism() = default;

