#include "scheduling.h"
#include <string.h>

int main() {
    //ѭ������10���߳�
    Process processes[PROCESS_NUM];
    for (int i = 0; i < PROCESS_NUM; i++) {
        char processName[124];
        sprintf(processName, "process-%d", i);
        strcpy(processes[i].name, processName);

        time_t now = time(NULL);
        processes[i].startTime = now;
        processes[i].expectTime = now + 10;

        processes[i].priority = rand() % 10 + 1;

        processes[i].status = PROCESS_STATUS_READY;
        processes[i].usedCPUCount = 0;
    }

    //ʹ��������ȼ��㷨���е���
    maxPriorityScheduling(processes, PROCESS_NUM);

    return 0;
}
