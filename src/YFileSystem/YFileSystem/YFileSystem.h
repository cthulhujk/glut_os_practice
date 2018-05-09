#ifndef _Y_FILE_SYSTEM_HEADER
#define _Y_FILE_SYSTEM_HEADER

#include "YFile.h"

class YFileSystem{
public:
    YFileSystem() : rootDir(new Directory(nullptr, "/")) {}
    ~YFileSystem() { delete rootDir; }

public:
    bool mkdir(const char * path);
    bool rmdir(const char * path);
    bool ls(const char * path);
    File* open(const char * path);
    bool read(File * f, char * buf, size_t byteNum);
    bool write(File* f, char * buf, size_t byteNum);


private:
    Directory * rootDir;
};

#endif
