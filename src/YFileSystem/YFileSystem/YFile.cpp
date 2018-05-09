#include "YFile.h"

Directory::~Directory(){
    for (size_t i = 0; i < sibling.size(); i++) {
        delete sibling[i];
    }
}
