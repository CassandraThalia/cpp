//
// Created by cassa on 2022-01-31.
//
#include <string>
#ifndef ASSIGNMENT1_LINKEDLISTNODE_H
#define ASSIGNMENT1_LINKEDLISTNODE_H

using namespace std;

class LinkedListNode {
public:
    string m_data;     //the data
    LinkedListNode* m_next;     //pointer to the address in memory of the next line of text
    LinkedListNode();
};


#endif //ASSIGNMENT1_LINKEDLISTNODE_H
