#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// 防止出现中文乱码的问题

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

#include "getwindowthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

#pragma execution_character_set("utf-8")

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

    void closeEvent(QCloseEvent *event);

    void changeEvent(QEvent *event);

public slots:
    void WorkDiaryTrayIconActivate(QSystemTrayIcon::ActivationReason reason);
    void TrayMenuActShow();
    void TrayMenuActQuit();


private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *tray_icon;
    QMenu *tray_menu;
    QAction *tray_menu_act_show_window;
    QAction *tray_menu_act_quit;
//    QTextCodec *codec;
    GetWindowThread *thread;
};
#endif // MAINWINDOW_H
