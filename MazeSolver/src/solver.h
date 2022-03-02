//Header file for Solver Class
#include <string>
#include <vector>
#include "cursor.h"
#include "stack.h"

#ifndef ASSIGNMENT_2_SOLVER_H
#define ASSIGNMENT_2_SOLVER_H


class Solver {
public:
    Solver() = default;

    std::vector<std::string> maze;

    void load_maze(std::string fileName);
    void solve_maze();
    void clear_maze();
    void write_maze(std::string fileName);
};

#endif //ASSIGNMENT_2_SOLVER_H
