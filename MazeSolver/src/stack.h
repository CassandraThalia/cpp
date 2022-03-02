//Header File for Stack Class
#ifndef ASSIGNMENT_2_STACK_H
#define ASSIGNMENT_2_STACK_H

#include <iostream>
#include <vector>
#include "cursor.h"

class Node {
public:
    Cursor m_data;
    Node *m_next{nullptr};
};

class Stack {
private:
    Node* m_last {nullptr};

public:
    Stack() = default;
    virtual ~Stack();

    void push(Cursor position);
    Cursor peek();
    void pop();
};

#endif //ASSIGNMENT_2_STACK_H