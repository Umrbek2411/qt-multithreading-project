#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QtConcurrent>
#include <QFutureSynchronizer>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartClicked();
    void onTaskFinished();
    void onAllFinished();

private:
    QSpinBox *spinBoxThreads;
    QPushButton *btnStart;
    QLabel *labelStatus;
    QProgressBar *progressBar;
    
    QFutureSynchronizer<void> *synchronizer;
    int totalTasks;
    int completedTasks;
    
    void executeTask(int taskId);
    void setupUI();
};

#endif
