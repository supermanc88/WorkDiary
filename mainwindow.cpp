#include <QIcon>
#include <QEvent>
#include <QAction>
#include <QTextCodec>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "common.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    codec = QTextCodec::codecForName("GBK");

    this->setWindowTitle(WORKDIARY_WITH_VERSION);

    QIcon icon = QIcon("E:\\Windows\\QT\\WorkDiary\\icon.png");
    QIcon quit_icon = QIcon("E:\\Windows\\QT\\WorkDiary\\close.png");

    // 设置窗口图标
    this->setWindowIcon(icon);

    // 设置托盘图标
    tray_icon = new QSystemTrayIcon(this);
    tray_icon->setIcon(icon);
    tray_icon->setToolTip("显示提示");
    tray_icon->show();

    tray_menu = new QMenu(this);
    tray_menu_act_show_window = new QAction(this);
    tray_menu_act_show_window->setIcon(icon);
    tray_menu_act_show_window->setText("显示");
    tray_menu_act_quit = new QAction(this);
    tray_menu_act_quit->setIcon(quit_icon);
    tray_menu_act_quit->setText("退出");
    tray_menu->addAction(tray_menu_act_show_window);
    tray_menu->addAction(tray_menu_act_quit);
    tray_icon->setContextMenu(tray_menu);

    connect(tray_icon, &QSystemTrayIcon::activated, this, &MainWindow::WorkDiaryTrayIconActivate);

    connect(tray_menu_act_quit, &QAction::triggered, this, &MainWindow::TrayMenuActQuit);
    connect(tray_menu_act_show_window, &QAction::triggered, this, &MainWindow::TrayMenuActShow);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange) {
        // 修改最小化 --> 隐藏到托盘
        if (this->windowState() == Qt::WindowMinimized) {
            hide();
            tray_icon->showMessage("title", "to system tray");
        }
    }
}

void MainWindow::WorkDiaryTrayIconActivate(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        // 单击托盘显示主窗口
        if (this->isMinimized()) {
            this->showNormal();
        }
        this->show();
        this->activateWindow();
        break;
    case QSystemTrayIcon::DoubleClick:
        // 双击托盘关闭程序
        this->close();
        break;
    default:
        break;
    }
}

void MainWindow::TrayMenuActShow()
{
    // 单击托盘显示主窗口
    if (this->isMinimized()) {
        this->showNormal();
    }
    this->show();
    this->activateWindow();
}

void MainWindow::TrayMenuActQuit()
{
    this->close();
}
