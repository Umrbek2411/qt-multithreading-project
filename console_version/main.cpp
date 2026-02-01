#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <QtConcurrent>
#include <QFutureSynchronizer>
#include <QTime>

// Task funksiyasi
void taskFunction(int taskNumber) {
    qDebug() << "════════════════════════════════════";
    qDebug() << "Task" << taskNumber << "BOSHLANDI";
    qDebug() << "Thread ID:" << QThread::currentThreadId();
    
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec() + taskNumber);
    int sleepTime = (rand() % 5) + 1;
    
    qDebug() << "Task" << taskNumber << "→" << sleepTime << "soniya";
    QThread::sleep(sleepTime);
    
    qDebug() << "Task" << taskNumber << "✓ TUGADI";
    qDebug() << "════════════════════════════════════\n";
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    qDebug() << "\n╔════════════════════════════════════════╗";
    qDebug() << "║   QT MULTITHREADING DASTUR             ║";
    qDebug() << "╚════════════════════════════════════════╝\n";
    
    int threadCount = 5;
    qDebug() << "📊 Umumiy tasklar:" << threadCount;
    qDebug() << "🖥️  Max threadlar:" << QThreadPool::globalInstance()->maxThreadCount();
    qDebug() << "";
    
    QFutureSynchronizer<void> synchronizer;
    
    qDebug() << "🚀 Tasklar ishga tushdi...\n";
    for (int i = 1; i <= threadCount; i++) {
        QFuture<void> future = QtConcurrent::run(taskFunction, i);
        synchronizer.addFuture(future);
    }
    
    synchronizer.waitForFinished();
    
    qDebug() << "\n╔════════════════════════════════════════╗";
    qDebug() << "║     ✓ BARCHA TASKLAR TUGADI!          ║";
    qDebug() << "╚════════════════════════════════════════╝\n";
    
    return 0;
}
