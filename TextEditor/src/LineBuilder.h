//
// Created by cassa on 2022-01-31.
//

#ifndef ASSIGNMENT1_LINEBUILDER_H
#define ASSIGNMENT1_LINEBUILDER_H


#include "LinkedList.h"

class LineBuilder {
private:
    bool m_exit;
    int line_to_edit;
    LinkedList list;

public:
    LineBuilder();
    virtual ~LineBuilder();

    void create_file(string file);
    void new_line(string data);
    void get_command(string);
    void get_command(string, int);
    void get_command(string, int, int);
    void open_file(string);
    void save_file(string);
};


#endif //ASSIGNMENT1_LINEBUILDER_H
