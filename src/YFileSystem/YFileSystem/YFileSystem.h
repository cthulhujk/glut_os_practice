#ifndef _Y_FILE_SYSTEM_HEADER
#define _Y_FILE_SYSTEM_HEADER

#include "YFile.h"
#include <list>
#include <string>
#include <iostream>

class YFileSystem{
public:
    YFileSystem() : rootDir(new Directory(nullptr, "/")) {}
    ~YFileSystem() { delete rootDir; }

public:
    void mkdir(const char * path);
    void rmdir(const char * path);
    void ls();
    File* open(const char * path) { return nullptr; }
    void read(File * f, char * buf, size_t byteNum) {}
    void write(File* f, char * buf, size_t byteNum) {}


private:
    void lsImpl(Directory * root);
    Node* traverseToEndian(const std::string & path);

    std::vector<std::string> parsePathList(const char * path);
    Directory * rootDir;
};

#endif
