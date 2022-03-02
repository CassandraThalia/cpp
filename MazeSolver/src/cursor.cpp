//C++ File for Cursor Class
#include "cursor.h"

using namespace std;

//Constructors
Cursor::Cursor() { x_pos = 1, y_pos = 0; };
Cursor::Cursor(int x_pos, int y_pos) : x_pos(x_pos), y_pos(y_pos) {};

//Overloaded != operator
bool Cursor::operator!=(Cursor cursor) {
    return(this->x_pos != cursor.x_pos) && (this->y_pos != cursor.y_pos);
}

//Getters & Setters
int Cursor::get_x_pos() const { return x_pos; };
void Cursor::set_x_pos(int x_pos_) { x_pos = x_pos_; }

int Cursor::get_y_pos() const { return y_pos; }
void Cursor::set_y_pos(int y_pos_) { y_pos = y_pos_; };