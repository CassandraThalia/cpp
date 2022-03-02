//
// Created by cassa on 2022-01-31.
//

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <fstream>

#include "LineBuilder.h"
#include "LinkedList.h"

using namespace std;


LineBuilder::LineBuilder() {m_exit = false, line_to_edit = 1;}

LineBuilder::~LineBuilder() {}


void LineBuilder::create_file(string file) {

    open_file(file);
    line_to_edit = list.get_size() + 1;

    while (!m_exit){
        string input;
        string command;

        cout << line_to_edit << ">";
        getline(cin, input);

        //Set up stringstream
        stringstream ss;
        ss << input;
        //Get first word as command
        ss >> command;

        //If first word is longer than 1 character, can assume it is a not a command -- add it as a new line
        if (command.length() > 1){
            new_line(input);
        }
        else {
            int start = -1;
            //ss now contains second "word" -- this checks if that word is a number
            ss >> start;
            if (ss.fail()) {
                ss.clear();
                ss >> command;
                if (ss.fail()) {
                    ss.clear();
                    get_command(command);
                } else {
                    new_line(input);
                }
            } else {
                int end = -1;
                ss >> end;
                if (ss.fail()) {
                    ss.clear();
                    get_command(command, start);
                }
                else {
                    get_command(command, start, end);
                }
            }
        }
    }
    save_file(file);
}

void LineBuilder::new_line(string data) {
    if (line_to_edit - 1 == list.get_size()){
        list.add_node(data);
    }
    else {
        list.insert_node(data, line_to_edit);
    }
    line_to_edit++;
}

void LineBuilder::get_command(string command) {
    char cmd = command[0];
    if (toupper(cmd) == 'L'){
        cout << list.output_list(1, list.get_size());
        line_to_edit = list.get_size() + 1;
    }
    else if (toupper(cmd) == 'I'){
        line_to_edit --;
        if (line_to_edit <= 0){
            line_to_edit = 1;
        }
    }
    else if (toupper(cmd) == 'D'){
        list.delete_node(line_to_edit - 1);
        line_to_edit = list.get_size() + 1;
    }
    else if (toupper(cmd) == 'E'){
        m_exit = true;
    }
    else {
        new_line(command);
    }
}

void LineBuilder::get_command(string command, int index) {
    char cmd = command[0];
    if (toupper(cmd) == 'L') {
        if (index > 0 && index <= list.get_size()){
            cout << list.
                    output_list(index, index);
            line_to_edit = list.get_size() + 1;
        }
        else {
            cout << "Index out of range" << endl;
        }
    }
    else if (toupper(cmd) == 'I') {
        if (index > 0 && index <= list.get_size()) {
            line_to_edit = index;
        }
        else {
            cout << "Index out of range" << endl;
        }
    }
    else if (toupper(cmd) == 'D') {
        if (index > 0 && index <= list.get_size()) {
            list.delete_node(index);
        }
        else {
            cout << "Index out of range" << endl;
        }
    }
    else if (toupper(cmd) == 'E'){
        m_exit = true;
    }
    else {
        new_line(command);
    }
}

void LineBuilder::get_command(string command, int start_index, int end_index){
    char cmd = command[0];
    if (toupper(cmd) == 'L') {
        if (start_index > 0 && end_index <= list.get_size()) {
            cout << list.output_list(start_index, end_index);
            line_to_edit = list.get_size() + 1;
        }
        else {
            cout << "Index out of range" << endl;
        }
    }
    else if (toupper(cmd) == 'D') {
        if (start_index > 0 && end_index <= list.get_size()) {
            for (int i = end_index; i >= start_index; i--) {
                list.delete_node(i);
            }
        }
        else {
            cout << "Index out of range" << endl;
        }
    }
    else if (toupper(cmd) == 'E'){
        m_exit = true;
    }
    else {
        new_line(command);
    }
}

void LineBuilder::open_file(string file_name) {
    ifstream inFile;
    inFile.open(file_name + ".txt");

    if (!inFile.fail()){
        string line;
        while (getline(inFile, line)){
            list.add_node(line);
        }
        inFile.close();
        cout << list.output_list(1, list.get_size());
    }
    else {
        cout << "No file found, a new one will be created upon exiting." << endl;
    }
}

void LineBuilder::save_file(string file_name) {
    ofstream outFile;
    outFile.open(file_name + ".txt", ios::app);
    if (!outFile.fail()){
        outFile << list.output_all_node_data();
    }
    else {
        cout << "File save error" << endl;
    }
    outFile.close();
}



//https://www.geeksforgeeks.org/write-a-function-to-get-nth-node-in-a-linked-list/
//https://www.cplusplus.com/reference/string/string/find/