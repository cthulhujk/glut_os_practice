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
    printf("������\t\t״̬\t���ȼ�\tCPU����\t��ʼʱ��\t�ڴ�����ʱ��\n");
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
    //�����н��̶��Ž��ȴ����У���Ϊ���̳�ʼ״̬����READY��
    std::queue<Process*> readyQueue;
    for (int i = 0; i < PROCESS_NUM; i++) {
        if (processes[i].status == PROCESS_STATUS_READY) {
            readyQueue.push(&processes[i]);
        }
    }

    //���������л��н��̾�һֱѭ��
    while (!readyQueue.empty()) {
        //��ȡ�ȴ����е�һ������
        Process * p = readyQueue.front();
        readyQueue.pop();

        //��װ����������һ��ʱ��Ƭ��������0.5��
        p->status = PROCESS_STATUS_RUNNING;
        Sleep(500);
        dump(processes, processNum);

        if (difftime(time(NULL), p->expectTime) > 0.0) {
            //�������ʱ�䳬��������������ʱ���ǾͰѽ�������ΪEXIT
            p->status = PROCESS_STATUS_EXIT;
        }
        else {
            //����������ʹ��CPUʱ���һ�����ȼ���һ,�������������β
            p->status = PROCESS_STATUS_READY;
            p->priority = p->priority > 0 ? p->priority : 0;
            p->usedCPUCount++;
            readyQueue.push(p);
        }

        //ÿ�ε��ȶ������ǰ���н�����Ϣ
        dump(processes, processNum);
    }
}
