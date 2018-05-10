#include "YFileSystem.h"

void YFileSystem::mkdir(const char * path){
    std::vector<std::string>  plist = parsePathList(path);
    Directory* lastDir = rootDir;
    for (int i = 0; i < plist.size(); i++) {
        auto * n = new Directory(lastDir,plist[i]);
        lastDir->addNode(n);
        lastDir = n;
    }
}

void YFileSystem::ls(){
    lsImpl(rootDir);
}

void YFileSystem::lsImpl(Directory * root){
    std::vector<Node*> sub = root->getSubNode();
    for (int i = 0; i < sub.size(); i++) {
        if (typeid(*sub[i]) == typeid(File)) {
            File* f = dynamic_cast<File*>(sub[i]);
            std::cout << f->name << "\t" << f->getSize() << "bytes\t" << ((static_cast<int>(f->getFlag()) == 0) ? "READ_WRITE" : "READ_ONLY") << "\n";
        }
        else if (typeid(*sub[i]) == typeid(Directory)) {
            Directory* f = dynamic_cast<Directory*>(sub[i]);
            std::cout << "/" << f->name << "\t" << "-\t" << ((static_cast<int>(f->getFlag())==0)?"READ_WRITE":"READ_ONLY") << "\n";
            lsImpl(dynamic_cast<Directory*>(sub[i]));
        }
    }
}

std::vector<std::string> YFileSystem::parsePathList(const char * path){
    std::vector<std::string> plist;
    int i = 0;
    while (path[i] != '\0') {
        if (path[i] == '/') {
            std::string span;
            i++;
            while (path[i] != '\0' && path[i] != '/') {
                span += path[i];
                i++;
            }
            i--;
            plist.push_back(span);
        }
        i++;
    }
    return plist;
}
