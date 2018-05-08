#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Process scheduling @racaljk");

    // Initialize 10 processes
    for (int i = 0; i < PROCESS_NUM; i++) {
        processes[i].name = "p"+i;
        processes[i].priority = rand() % 10 + 1;
        processes[i].status = PROCESS_STATUS_READY;
        processes[i].usedCPUCount = 0;

        processes[i].relatedLabel = new QLabel();
        processes[i].relatedLabel->setText(QString("Process #%1").arg(i));
        processes[i].relatedProgressBar = new QProgressBar();
        processes[i].relatedProgressBar->setValue(0);
        processes[i].relatedProgressBar->setRange(0,100);
        processes[i].relatedCPUTickLCD = new QLCDNumber();
        processes[i].relatedPriorityLCD = new QLCDNumber();

        ui->layout_procname->addWidget(processes[i].relatedLabel);
        ui->layout_progress->addWidget(processes[i].relatedProgressBar);
        ui->layout_cpuused->addWidget(processes[i].relatedCPUTickLCD);
        ui->layout_priority->addWidget(processes[i].relatedPriorityLCD);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    std::priority_queue<Process*, std::vector<Process*>, Compare> readyQueue;
    for (int i = 0; i < PROCESS_NUM; i++) {
        if (processes[i].status == PROCESS_STATUS_READY) {
            readyQueue.push(&processes[i]);
        }
    }

    while (!readyQueue.empty()) {
        Process * p = readyQueue.top();
        readyQueue.pop();

        QElapsedTimer t;
        t.start();
        while(t.elapsed()<10)
            QCoreApplication::processEvents();

        p->relatedProgressBar->setStyleSheet("QProgressBar::chunk { background-color: rgb(0, 255, 0) }");
        p->relatedProgressBar->setValue(p->usedCPUCount);
        p->relatedProgressBar->setStyleSheet("QProgressBar::chunk { background-color: rgb(111, 111, 111) }");

        if ((p->relatedProgressBar->maximum()<p->usedCPUCount)) {
            p->status = PROCESS_STATUS_EXIT;
        }
        else {
            p->status = PROCESS_STATUS_READY;
            p->priority = p->priority > 0 ? p->priority : 0;
            p->usedCPUCount++;
            readyQueue.push(p);

            p->relatedCPUTickLCD->display((double)p->usedCPUCount);
            p->relatedPriorityLCD->display((double)p->priority);
        }
    }
}

void MainWindow::on_pushButton_3_clicked(){
    std::queue<Process*> readyQueue;
    for (int i = 0; i < PROCESS_NUM; i++) {
        if (processes[i].status == PROCESS_STATUS_READY) {
            time_t now = time(NULL);
            processes[i].startTime = now;
            processes[i].expectTime = now+200;
            readyQueue.push(&processes[i]);
        }
    }

    while (!readyQueue.empty()) {
        Process * p = readyQueue.front();
        readyQueue.pop();


        QElapsedTimer t;
        t.start();
        while(t.elapsed()<20)
            QCoreApplication::processEvents();

        p->relatedProgressBar->setStyleSheet("QProgressBar::chunk { background-color: rgb(0, 255, 0) }");
        p->relatedProgressBar->setValue(p->usedCPUCount);
        p->relatedProgressBar->setStyleSheet("QProgressBar::chunk { background-color: rgb(111, 111, 111) }");

        if ((p->relatedProgressBar->maximum()<p->usedCPUCount)) {
            p->status = PROCESS_STATUS_EXIT;
        }
        else {
            p->status = PROCESS_STATUS_READY;
            p->priority = p->priority > 0 ? p->priority : 0;
            p->usedCPUCount++;
            readyQueue.push(p);

             p->relatedCPUTickLCD->display((double)p->usedCPUCount);
            p->relatedPriorityLCD->display((double)p->priority);
        }
    }
}

void MainWindow::on_pushButton_2_clicked(){
    for(int i=0;i<PROCESS_NUM;i++){
        processes[i].priority = rand() % 10 + 1;
        processes[i].status = PROCESS_STATUS_READY;
        processes[i].usedCPUCount = 0;
        processes[i].relatedProgressBar->setValue(0);
        processes[i].relatedCPUTickLCD->display(0);
        processes[i].relatedPriorityLCD->display(0);
    }

}
