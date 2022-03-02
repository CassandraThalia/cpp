//C++ File for Solver Class
#include <iostream>
#include <fstream>
#include "solver.h"

using namespace std;

//Function to load maze from file
void Solver::load_maze(string fileName) {
    ifstream inFile;
    inFile.open(fileName);

    if (!inFile.fail()){
        string line;
        //Get each line of the maze and push it to a vector
        while (getline(inFile, line)) {
            if (!line.empty()){
                maze.push_back(line);
            }
        }
    }
    else {
        cout << "No file found." << endl;
    }
}

//Function to solve maze
void Solver::solve_maze() {
    auto cursor = new Cursor();
    auto stack = new Stack();
    bool done = false;

    //Until the cursor reaches the end of the maze, continue the pattern
    while (!done){
        //Set hash char at current cursor position
        maze[cursor->get_x_pos()][cursor->get_y_pos()] = '#';

        //Check above cursor for space
        if (maze[cursor->get_x_pos()][cursor->get_y_pos() - 1] == ' ') {
            //If space exists, set cursor data to new space
            cursor->set_y_pos(cursor->get_y_pos() - 1);
            //Push cursor data to the stack
            stack->push(*cursor);
        }
        //Check right of cursor for space
        else if (maze[cursor->get_x_pos() + 1][cursor->get_y_pos()] == ' ') {
            cursor->set_x_pos(cursor->get_x_pos() + 1);
            stack->push(*cursor);
        }
        //Check below cursor for space
        else if (maze[cursor->get_x_pos()][cursor->get_y_pos() + 1] == ' ') {
            cursor->set_y_pos(cursor->get_y_pos() + 1);
            stack->push(*cursor);
        }
        //Check left of cursor for space
        else if (maze[cursor->get_x_pos()- 1][cursor->get_y_pos()] == ' ') {
            cursor->set_x_pos(cursor->get_x_pos() - 1);
            stack->push(*cursor);
        }
        //If no spaces available, pop the last node off the stack and set cursor data to prev. node
        else {
            stack->pop();
            *cursor = stack->peek();
        }

        //Check for end condition
        if (cursor->get_x_pos() == 49 && cursor->get_y_pos() == 50) {
            done = true;
        }
    }

    //Clear all hash chars from maze
    clear_maze();

    //For each node data, set an x at the data position
    maze[1][0] = 'x';
    while (stack->peek() != Cursor(-1, -1)) {
        maze[stack->peek().get_x_pos()][stack->peek().get_y_pos()] = 'x';
        stack->pop();
    }
}

//Function to clear hash char from maze vector
void Solver::clear_maze() {
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++){
            if (maze[i][j] == '#') {
                maze[i][j] = ' ';
            }
        }
    }
}

//Function to write solved maze to new file
void Solver::write_maze(string filePath) {
    ofstream outFile;
    outFile.open(filePath, ios::app);
    if (!outFile.fail()) {
        for (int i = 0; i < maze.size(); i++) {
            outFile << maze[i] << endl;
        }
    } else {
        cout << "File save error" << endl;
    }
    outFile.close();
}