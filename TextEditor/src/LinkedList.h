//
// Created by cassa on 2022-01-31.
//
#include <string>

#ifndef ASSIGNMENT1_LINKEDLIST_H
#define ASSIGNMENT1_LINKEDLIST_H

using namespace std;

class LinkedListNode;

class LinkedList {
private:
    int m_size;     //size of the current list
    LinkedListNode* m_start;    //pointer to the start of the first node in the chain

public:
    LinkedList();
    virtual ~LinkedList();
    void add_node(string);
    void insert_node(string, int);
    bool delete_node(int);
    int get_size();
    string get_data_by_index(int);
    string output_list(int, int);
    string output_all_node_data();
    friend ostream& operator<<(ostream& output, LinkedList& list);
};



#endif //ASSIGNMENT1_LINKEDLIST_H
