#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "common.h"

#include <QIcon>
#include <QEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(WORKDIARY_WITH_VERSION);

    QIcon icon = QIcon("E:\\Windows\\QT\\WorkDiary\\icon.png");

    // 设置窗口图标
    this->setWindowIcon(icon);

    // 设置托盘图标
    tray_icon = new QSystemTrayIcon(this);
    tray_icon->setIcon(icon);
    tray_icon->setToolTip("提示文字");
    tray_icon->show();

    connect(tray_icon, &QSystemTrayIcon::activated, this, &MainWindow::WorkDiaryTrayIconActivate);
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
            tray_icon->showMessage("title", "隐藏窗口到托盘了");
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
