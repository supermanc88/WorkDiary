#ifndef GETWINDOWTHREAD_H
#define GETWINDOWTHREAD_H

#include <QThread>

class GetWindowThread : public QThread
{
public:
    GetWindowThread(QObject *parent);
    void CloseThread();
protected:
    void run();
private:
    int is_close;
};

#endif // GETWINDOWTHREAD_H
