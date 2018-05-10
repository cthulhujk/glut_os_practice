#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <deque>
#include <algorithm>

constexpr int INSTRUCTION_NUM = 320;
constexpr int PAGE_NUM = 32;

class PageReplacement {
public:
    PageReplacement();

    void FIFO();
    void LRU();

private:
    void dbgPrintInstructionRelatedPages();
    void dumpPageFaultRatio();

private:
    /// The result virtual page id of specific instruction should be in [0,PAGE_NUM-1];
    inline int getVirtualPageID(int instruction) { return instruction / 10; }
    inline bool hasPageAddr(int pageNum) { return  std::find(pageAddr.begin(), pageAddr.end(), pageNum) != std::end(pageAddr); }

private:
    int instruction[INSTRUCTION_NUM]{ 0 };
    int pages[PAGE_NUM]{ 0 };
    
    std::deque<int> pageAddr;

    std::default_random_engine e{ time(0) };
    unsigned pageFaultCnt = 0;

    enum class Policy {
        FIFO, LRU
    };
    Policy currentPolicy;
};