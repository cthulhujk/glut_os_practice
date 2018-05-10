#ifndef _Y_FILE_HEADER
#define _Y_FILE_HEADER

#include <stdint.h>
#include <string>
#include <chrono>
#include <mutex>
#include <vector>
#include <fstream>

using namespace std::chrono;

enum class FileType {
    BINARY,TEXT
};
enum class AccessFlag {
    READ_WRITE, READ_ONLY
};

class Node{
public:
    explicit Node(const std::string &n) :createTime(system_clock::now()),name(n) {}
    explicit Node(const std::string &n, AccessFlag flag) :createTime(system_clock::now()),name(n) {}
    virtual ~Node() {}

    inline void setFlag(AccessFlag flag) { this->flag = flag; }
    inline void lock() { fmutex.lock(); }
    inline void unlock() { fmutex.unlock(); }
    AccessFlag getFlag() { return flag; }

public:
    std::string name;

private:
    const system_clock::time_point createTime;
    AccessFlag flag;
    std::mutex fmutex;
};

#define YNODE_BASE :public Node

class Directory YNODE_BASE {
public:
    explicit Directory(Directory* parent, const std::string &n) :Node(n, AccessFlag::READ_WRITE), parent(parent) {}
    ~Directory();

    inline void addNode(Node * n) { sibling.push_back(n); }
    inline void setParent(Directory * dir);
    inline std::vector<Node*> getSubNode() { return sibling; }

private:
    Directory* parent;
    std::vector<Node*> sibling;
};

class File YNODE_BASE {
public:
    explicit File(Directory* parent, const std::string &n) :Node(n, AccessFlag::READ_WRITE), parent(parent) {}
    ~File() { parent = nullptr; }

public:
    File & open();
    void read(char * buf, size_t size) { fs.read(buf, size); }
    void write(char * buf, size_t size) { fs.write(buf, size); size = strlen(buf); }
    void close() { fs.close(); }

    inline auto getSize() { return size; }

private:
    std::fstream fs;
    Directory * parent;
    int64_t size;
};
#endif

