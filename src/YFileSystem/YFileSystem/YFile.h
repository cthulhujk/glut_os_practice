#ifndef _Y_FILE_HEADER
#define _Y_FILE_HEADER

#include <stdint.h>
#include <chrono>
#include <mutex>
#include <vector>

using namespace std::chrono;

enum class FileType {
    BINARY,TEXT
};
enum class AccessFlag {
    READ_WRITE, READ_ONLY
};

class Node{
public:
    explicit Node(const char * name) :createTime(system_clock::now()) { strncmp(name, Node::name, 125); }
    explicit Node(const char * name, AccessFlag flag) :createTime(system_clock::now()) { strncmp(name, Node::name, 125); }
    virtual ~Node() = 0;

    inline void setFlag(AccessFlag flag) { this->flag = flag; }
    inline void lock() { fmutex.lock(); }
    inline void unlock() { fmutex.unlock(); }

private:
    char name[125];
    const system_clock::time_point createTime;
    AccessFlag flag;
    std::mutex fmutex;
};

#define YNODE_BASE :public Node

class Directory YNODE_BASE {
public:
    explicit Directory(Directory* parent, const char *name) :Node(name, AccessFlag::READ_WRITE), parent(parent) {}
    ~Directory();

private:
    inline void addNode(Node * n) { sibling.push_back(n); }
    Directory* parent;
    std::vector<Node*> sibling;
};

class File YNODE_BASE {
public:
    explicit File(Directory* parent, const char *name) :Node(name, AccessFlag::READ_WRITE), parent(parent) {}
    ~File() { parent = nullptr; data.clear(); }
public:


private:
    Directory * parent;
    int64_t size;
    std::vector<int8_t> data; 
};
#endif

