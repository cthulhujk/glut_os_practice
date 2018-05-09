#include "PageReplacement.h"

PageReplacement::PageReplacement() {
    /// For each 4 instructions, it follows the rule:
    /// SEQ SEQ BEFORE AFTER
    /// This generating rule causes 50% instructions executing consistently 
    /// and 25% instructions jump to advanced addresses and remain instructions
    /// jump to later.
    for (int i = 0; i < INSTRUCTION_NUM; i += 4) {
        std::uniform_int_distribution<unsigned> u(1, INSTRUCTION_NUM - 2);
        int rnum = u(e);
        std::uniform_int_distribution<unsigned> before(0, rnum);
        std::uniform_int_distribution<unsigned> after(rnum + 1, INSTRUCTION_NUM - 1);
        instruction[i + 0] = rnum;
        instruction[i + 1] = rnum + 1;
        instruction[i + 2] = before(e);
        instruction[i + 3] = after(e);
    }
}

void PageReplacement::dbgPrintInstructionRelatedPages() {
    std::cout << "Instruction" << "\t\t" << "Page\n";
    for (int i = 0; i < INSTRUCTION_NUM; i++) {
        std::cout << "#" << i << "\t" << getVirtualPageID(instruction[i]) << "\n";
    }
}

void PageReplacement::dumpPageFaultRatio(){
    if (currentPolicy == PageReplacement::Policy::FIFO) {
        std::cout << "FIFO";
    }
    else if (currentPolicy == PageReplacement::Policy::LRU) {
        std::cout << "LRU";
    }
    else {
        static_assert(true, "Unknow page replacement policy selected");
    }
    std::cout << " page fault :";
    std::cout << (1.0 - (pageFaultCnt / (INSTRUCTION_NUM*1.0)))* 100.0;
    std::cout << "%\n";
}

void PageReplacement::FIFO() {
    currentPolicy = PageReplacement::Policy::FIFO;
    for (int i = 0; i < INSTRUCTION_NUM; i++) {
        int insPage = getVirtualPageID(instruction[i]);
        
       
        if (pageAddr.size() == PAGE_NUM) {
            // Cause page fault;
            if (!hasPageAddr(insPage)) {
                pageFaultCnt++;
                dumpPageFaultRatio();
                pageAddr.pop_front();
                pageAddr.push_back(insPage);
            }
        }
        else {
            pageAddr.push_back(insPage);
        }
    }
}
