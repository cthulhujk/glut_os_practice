#ifndef _Y_FILE_HEADER
#define _Y_FILE_HEADER

#include <stdint.h>
#include <ctime>
#include <mutex>
#include <vector>

enum class FileType {
    BINARY,TEXT
};
enum class AccessFlag {
    READ_WRITE, READ_ONLY
};

struct YFile{
    char name[125];
    time_t createTime;
    time_t modifyTime;
    int64_t size;
    AccessFlag fag;
    std::mutex fmutex;
};

#define YFILE_BASE :public YFile

class Directory YFILE_BASE {
    Directory* parent;
    std::vector<YFile*> sibling;
};

class RawFile YFILE_BASE {
    Directory* parent;
};
#endif

