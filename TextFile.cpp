#include "TextFile.h"
#include <fstream>

using namespace std;

bool TextFile::checkIfTheFileIsEmpty(fstream &textFile) {
    textFile.seekg(0, ios::end);
    if (textFile.tellg() == 0)
        return true;
    else
        return false;
}

string TextFile::getFileName() {
    return FILE_NAME;
}




