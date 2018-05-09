#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <future>
#include <chrono>
#include <vector>

volatile std::atomic_bool writing;
std::mutex rMutex;
std::mutex wMutex;

using namespace std::chrono_literals;

void concurrentRW(std::fstream & fs){
    std::vector<std::future<void>> futures;

    auto writeFuture{
        std::async(std::launch::async,[&]{
            while(!fs.eof()){
                rMutex.lock();
                writing=true;
                std::cout<<"----------------------------------------\n";
                writing=false;
                rMutex.unlock();
            }
        })
    };
    futures.push_back(std::move(writeFuture));

    for(int i=0;i<std::thread::hardware_concurrency();i++) {
        std::future<void> res{std::async(std::launch::async, [&] {
            while (!fs.eof()) {
                if(!writing){
                    char buf[1024];
                    fs.getline(buf, sizeof(buf));
                    std::cout<<"+\n";
                }
            }
        })};
        futures.push_back(std::move(res));
    }
}


int main() {
    std::atomic_init(&writing,false);
    std::fstream fs("data.txt",std::ios::in|std::ios::out);
    concurrentRW(fs);
    std::cout<<"done\n";
    return 0;
}