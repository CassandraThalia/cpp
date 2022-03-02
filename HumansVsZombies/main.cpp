#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include "Organism.h"
#include "City.h"


using namespace std;

int main() {

    int numPasses = 0;
    City *c = new City();
    chrono::seconds interval( 1 );

    c->create();
    cout << *c;
    c->reset();

    while (c->hasDiversity()) {
        numPasses++;
        c->moveOrganisms();
        c->breedOrganisms();
        c->countOrganisms();
        cout << *c;
        cout << "NUMBER OF PASSES: " << numPasses << endl << endl;
        this_thread::sleep_for(interval);
        c->reset();
    }

}