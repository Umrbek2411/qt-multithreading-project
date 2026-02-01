#include "mainwindow.h"
#include <QDebug>
#include <QThread>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), synchronizer(nullptr), totalTasks(0), completedTasks(0)
{
    setupUI();
}

MainWindow::~MainWindow()
{
    if (synchronizer) delete synchronizer;
}

void MainWindow::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    QLabel *titleLabel = new QLabel("🚀 Qt Multithreading", this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);
    
    QHBoxLayout *threadLayout = new QHBoxLayout();
    threadLayout->addWidget(new QLabel("Threadlar:"));
    spinBoxThreads = new QSpinBox(this);
    spinBoxThreads->setRange(1, 20);
    spinBoxThreads->setValue(5);
    threadLayout->addWidget(spinBoxThreads);
    threadLayout->addStretch();
    
    btnStart = new QPushButton("▶ BOSHLASH", this);
    btnStart->setMinimumHeight(50);
    btnStart->setStyleSheet("background-color: #27ae60; color: white; font-size: 16px;");
    
    labelStatus = new QLabel("Tayyor", this);
    labelStatus->setStyleSheet("padding: 10px; background-color: #ecf0f1;");
    labelStatus->setAlignment(Qt::AlignCenter);
    
    progressBar = new QProgressBar(this);
    progressBar->setMinimumHeight(30);
    
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(threadLayout);
    mainLayout->addWidget(btnStart);
    mainLayout->addWidget(labelStatus);
    mainLayout->addWidget(progressBar);
    mainLayout->addStretch();
    
    connect(btnStart, &QPushButton::clicked, this, &MainWindow::onStartClicked);
}

void MainWindow::onStartClicked()
{
    btnStart->setEnabled(false);
    spinBoxThreads->setEnabled(false);
    
    totalTasks = spinBoxThreads->value();
    completedTasks = 0;
    progressBar->setMaximum(totalTasks);
    progressBar->setValue(0);
    
    labelStatus->setText(QString("⏳ Ishlamoqda... (0/%1)").arg(totalTasks));
    
    synchronizer = new QFutureSynchronizer<void>();
    
    for (int i = 1; i <= totalTasks; i++) {
        QFuture<void> future = QtConcurrent::run(this, &MainWindow::executeTask, i);
        synchronizer->addFuture(future);
    }
    
    QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
    connect(watcher, &QFutureWatcher<void>::finished, this, &MainWindow::onAllFinished);
    watcher->setFuture(synchronizer->future());
}

void MainWindow::executeTask(int taskId)
{
    qDebug() << "Task" << taskId << "boshlandi";
    
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec() + taskId * 1000);
    int sleepTime = (rand() % 5) + 1;
    
    QThread::sleep(sleepTime);
    qDebug() << "Task" << taskId << "tugadi";
    
    QMetaObject::invokeMethod(this, "onTaskFinished", Qt::QueuedConnection);
}

void MainWindow::onTaskFinished()
{
    completedTasks++;
    progressBar->setValue(completedTasks);
    labelStatus->setText(QString("⏳ Ishlamoqda... (%1/%2)").arg(completedTasks).arg(totalTasks));
}

void MainWindow::onAllFinished()
{
    labelStatus->setText("✅ Barcha tasklar tugadi!");
    labelStatus->setStyleSheet("padding: 10px; background-color: #d5f4e6; color: #27ae60;");
    
    btnStart->setEnabled(true);
    spinBoxThreads->setEnabled(false);
    
    delete synchronizer;
    synchronizer = nullptr;
}
