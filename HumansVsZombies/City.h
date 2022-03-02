#ifndef _CITY_H
#define _CITY_H

#include <iostream>

using namespace std;

class Organism;

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

class City {
private:
    int humanCount;
    int zombieCount;
public:
	City();
	virtual ~City();

    Organism *getAt(int x, int y );
    void setAt(Organism *organism, int x, int y );

    void moveOrganisms();
    void create();
    void reset();
    void breedOrganisms();
    void countOrganisms();
    bool hasDiversity();
    void color(int);

    friend ostream& operator<<( ostream &output, City &city );

    Organism *grid[GRID_HEIGHT][GRID_WIDTH];
};

#endif

