#ifndef TEXTFILE_H
#define TEXTFILE_H
#include <iostream>
#include "User.h"
#include "AuxiliaryMethods.h"
#include "Markup.h"

using namespace std;

class TextFile {
    const string FILE_NAME;


public:
    TextFile(string fileName) : FILE_NAME(fileName) {
    }
    string getFileName();
    bool checkIfTheFileIsEmpty(fstream &textFile);

};

#endif // TEXTFILE


