//Main File to Run Program
#include <sstream>

#include "solver.h"

using namespace std;

int main() {
    //Create new Solver & solve maze
    auto solver = new Solver();

    solver->load_maze("../tests/test3.txt");

    solver->solve_maze();

    solver->write_maze("../solved/testsolution3.txt");
}