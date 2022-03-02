//Header File for Cursor Class
#ifndef ASSIGNMENT_2_CURSOR_H
#define ASSIGNMENT_2_CURSOR_H

#include <iostream>

class Cursor {
public:
    int x_pos;
    int y_pos;

    Cursor();
    Cursor(int x_pos, int y_pos);

    int get_x_pos() const;
    void set_x_pos(int x_pos_);

    int get_y_pos() const;
    void set_y_pos(int y_pos_);

    bool operator!=(Cursor cursor);
};

#endif //ASSIGNMENT_2_CURSOR_H