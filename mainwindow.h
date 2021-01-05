#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// 防止出现中文乱码的问题

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QTabWidget>

#include <QSqlDatabase>

#include "getwindowthread.h"
#include "mainwidget.h"
#include "datawidget.h"
#include "planwidget.h"
#include "setwidget.h"

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


    void InitDataBase();

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

    QTabWidget *tab_widget;
    MainWidget *main_widget;
    DataWidget *data_widget;
    PlanWidget *plan_widget;
    SetWidget *set_widget;

    QSqlDatabase diary_database;
    QString current_table;
};
#endif // MAINWINDOW_H
