#include "YFile.h"

Directory::~Directory(){
    for (size_t i = 0; i < sibling.size(); i++) {
        delete sibling[i];
    }
}

File & File::open(){
    std::string fname("yfs_");
    fname += name;

    fs.open(fname, std::ios::out | std::ios::app);
    return *this;
}
