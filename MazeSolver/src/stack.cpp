//C++ File for Stack Class
#include "stack.h"

using namespace std;

Stack::~Stack() {
    while(peek() != Cursor(-1, -1)){
        pop();
    }
}

//Function to add a node to the stack
void Stack::push(Cursor cursor) {
    auto new_node = new Node();
    new_node->m_data = cursor;
    //If no nodes in stack yet
    if (m_last == nullptr) {
        m_last = new_node;
    }
    else {
        new_node->m_next = m_last;
        m_last = new_node;
    }
}

//Function to peek at data of last node in stack
Cursor Stack::peek() {
    if (m_last != nullptr) {
        return m_last->m_data;
    }
    else {
        return {-1, -1};
    }
}

//Function to pop last node off the stack
void Stack::pop() {
    if (m_last != nullptr) {
        auto node = m_last;
        m_last = node->m_next;
        delete node;
    }
}