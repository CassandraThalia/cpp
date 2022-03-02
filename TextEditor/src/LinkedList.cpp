//
// Created by cassa on 2022-01-31.
//
#include <iostream>
#include <sstream>
#include <algorithm>

#include "LinkedList.h"
#include "LinkedListNode.h"

LinkedList::LinkedList() : m_start(nullptr), m_size(0) {}

LinkedList::~LinkedList() {
    LinkedListNode *node = m_start;
    while (node != nullptr) {
        LinkedListNode *temp = node;
        node = node->m_next;
        delete temp;
    }
}

void LinkedList::add_node(string data) {
    //Create a new node (line of text)
    LinkedListNode* new_node = new LinkedListNode();
    new_node->m_data = data;

    //Add first node
    if (m_start == nullptr){
        m_start = new_node;
    }
        //Add node to end of existing chain
    else {
        LinkedListNode* node = m_start;
        LinkedListNode* prev = nullptr;

        //Look for the node with a null "next" pointer
        while (node != nullptr){
            prev = node;
            node = node->m_next;
        }

        //Attach new node to end of the chain
        if (prev != nullptr){
            prev->m_next = new_node;
        }
    }
    m_size++;
}

void LinkedList::insert_node(string data, int position) {

    // check to see at least one node to insert before
    if (position > m_size) {
        cout << "Node to insert before doesn't exist." << endl;
        return;
    }

    LinkedListNode* new_node = new LinkedListNode();
    if (new_node == nullptr) {
        cout << "Couldn't allocate memory for new nodes." << endl;
        return;
    }
    new_node->m_data = data;

    // find position
    LinkedListNode* node = m_start;
    LinkedListNode* prev = nullptr;
    int curr_pos = 1;

    while (node != nullptr) {

        // application specific - use position to find node
        if (curr_pos == position) {
            break;
        }
        curr_pos++;
        prev = node;
        node = node->m_next;
    }

    if (prev == nullptr) {
        // insert node at the start
        new_node->m_next = m_start;
        m_start = new_node;
    } else {
        // insert node in the middle
        new_node->m_next = prev->m_next;
        prev->m_next = new_node;
    }

    m_size++;
}

bool LinkedList::delete_node(int index) {
    LinkedListNode* node = m_start;
    LinkedListNode* prev = nullptr;

    string data = get_data_by_index(index);

    while (node != nullptr){
        //Logic ot find code
        if (node->m_data == data){
            break;
        }
        prev = node;
        node = node->m_next;
    }

    //If node was found, would have value, otherwise would reach end of chain
    if (node != nullptr){
        //Check if deleting first node
        if (prev == nullptr){
            m_start = node->m_next;
        }
        //Otherwise deleting any other node
        else {
            prev->m_next = node->m_next;
        }
        delete node;
        m_size--;
        return true;
    }
    return false;
}

ostream& operator<<(ostream& output, LinkedList& list){
    LinkedListNode* node = list.m_start;
    int lineCount = 0;
    //Output data from all the nodes in the chain
    while (node != nullptr){
        lineCount++;
        cout << lineCount << ">" << node->m_data << endl;
        node = node->m_next;
    }
    return output;
}

string LinkedList::get_data_by_index(int index) {
    LinkedListNode* node = m_start;
    int count = 1;
    while (node != nullptr){
        if (count == index){
            return node->m_data;
        }
        count++;
        node = node->m_next;
    }
    //return "Error -- Line non-existent";
}

int LinkedList::get_size() {
    return m_size;
}

string LinkedList::output_list(int start_index, int end_index) {
    stringstream output;
    for (int i = start_index; i <= end_index; i++){
        string data = get_data_by_index(i);
        output << i << ">" << data << endl;
    }
    return output.str();
}

string LinkedList::output_all_node_data() {
    stringstream output;
    for (int i = 1; i <= m_size; i++){
        string data = get_data_by_index(i);
        output << data << endl;
    }
    return output.str();
}
