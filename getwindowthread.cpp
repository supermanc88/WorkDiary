#include "getwindowthread.h"

#include <QDebug>
#include <QApplication>
#include <QWidget>
#include <windows.h>
#include <wchar.h>

GetWindowThread::GetWindowThread(QObject *parent) : QThread(parent)
{
    is_close = 0;
}

void GetWindowThread::CloseThread()
{
    is_close = 1;
}

void GetWindowThread::run()
{
    while(true) {
        if (is_close)
            return;

        HWND whandle = GetForegroundWindow();
        char c_window_title[256] = {0};
        GetWindowTextA(whandle, c_window_title, 256);
        QString window_title = QString::fromLocal8Bit(c_window_title);
        qDebug() << "window tilte :" << window_title << endl;

        sleep(1);
    }

}
