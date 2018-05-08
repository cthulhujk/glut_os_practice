#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <qlabel.h>
#include <qprogressbar.h>
#include <qlcdnumber.h>
#include <queue>
#include <qelapsedtimer.h>

#define PROCESS_NUM 10
#define PROCESS_STATUS_READY 1
#define PROCESS_STATUS_RUNNING 2
#define PROCESS_STATUS_EXIT 3

struct ProcessControlBlock {
    QString name;
    int priority;
    time_t startTime;
    time_t expectTime;
    long usedCPUCount;
    int status;

    QLabel * relatedLabel;
    QProgressBar * relatedProgressBar;
    QLCDNumber * relatedPriorityLCD;
    QLCDNumber * relatedCPUTickLCD;
};

typedef struct ProcessControlBlock Process;

struct Compare {
    bool operator()(ProcessControlBlock* left, ProcessControlBlock* right) const {
        return left->priority < right->priority;

    }
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Process processes[10];
};

#endif // MAINWINDOW_H
