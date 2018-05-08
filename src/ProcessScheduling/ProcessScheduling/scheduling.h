#pragma once
#include <stdio.h>
#include <time.h>
#include <queue>
#include <stdlib.h>
#include <Windows.h>

#define PROCESS_NUM 10
#define PROCESS_STATUS_READY 1
#define PROCESS_STATUS_RUNNING 2
#define PROCESS_STATUS_EXIT 3

struct ProcessControlBlock {
    char name[125];
    int priority;
    time_t startTime;
    time_t expectTime;
    long usedCPUCount;
    int status;
};

typedef struct ProcessControlBlock Process;

void dump(Process processes[], int processNum) {
    printf("进程名\t\t状态\t优先级\tCPU计数\t开始时间\t期待运行时间\n");
    for (int i = 0; i < processNum; i++) {
        printf("%s\t%s\t%d\t%d\t%lld\t%lld\n",
            processes[i].name,
            (processes[i].status == PROCESS_STATUS_READY) ? ("READY") : ((processes[i].status == PROCESS_STATUS_RUNNING) ? ("RUNNING"):("EXIT")),
            processes[i].priority,
            processes[i].usedCPUCount,
            processes[i].startTime,
            processes[i].expectTime);
    }
}

void maxPriorityScheduling(Process processes[], int processNum) {
    //将所有进程都放进等待队列（因为进程初始状态都是READY）
    std::queue<Process*> readyQueue;
    for (int i = 0; i < PROCESS_NUM; i++) {
        if (processes[i].status == PROCESS_STATUS_READY) {
            readyQueue.push(&processes[i]);
        }
    }

    //当就绪队列还有进程就一直循环
    while (!readyQueue.empty()) {
        //获取等待队列第一个进程
        Process * p = readyQueue.front();
        readyQueue.pop();

        //假装进程运行了一个时间片，这里是0.5秒
        p->status = PROCESS_STATUS_RUNNING;
        Sleep(500);
        dump(processes, processNum);

        if (difftime(time(NULL), p->expectTime) > 0.0) {
            //如果现在时间超出进程允许运行时间那就把进程设置为EXIT
            p->status = PROCESS_STATUS_EXIT;
        }
        else {
            //否则它的已使用CPU时间加一，优先级减一,并放入就绪队列尾
            p->status = PROCESS_STATUS_READY;
            p->priority = p->priority > 0 ? p->priority : 0;
            p->usedCPUCount++;
            readyQueue.push(p);
        }

        //每次调度都输出当前所有进程信息
        dump(processes, processNum);
    }
}
