#include <iostream>
#include <sstream>
#include <algorithm>

#include "LineBuilder.h"
#include "LinkedList.h"
using namespace std;

int main(int argc, char** argv) {

    LineBuilder lineBuilder;

    if (argc == 3 && string(argv[1]) == "EDIT")
    {
        lineBuilder.create_file(string(argv[2]));
    }
    else
    {
        cout << "Invalid command, must begin with EDIT followed by file name." << endl;
    }

    return 0;
}

//First word in string: https://stackoverflow.com/questions/41992747/how-to-only-print-the-first-word-of-a-string-in-c/41992882
//Remove whitesapces: https://www.techiedelight.com/remove-whitespaces-string-cpp/