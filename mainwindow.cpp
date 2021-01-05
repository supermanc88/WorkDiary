#include <QIcon>
#include <QEvent>
#include <QAction>
#include <QTextCodec>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>

#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "getwindowthread.h"
#include "mainwidget.h"
#include "datawidget.h"
#include "planwidget.h"
#include "setwidget.h"

#include "common.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    codec = QTextCodec::codecForName("GBK");

    this->setWindowTitle(WORKDIARY_WITH_VERSION);

    // 禁用窗口最大化和窗口大小改变
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    // 主程序图标
    QIcon icon = QIcon(":/icon/workdiary/icon.png");
    // 关闭图标
    QIcon quit_icon = QIcon(":/icon/workdiary/close.png");
    // 设置图标
    QIcon set_icon = QIcon(":/icon/workdiary/set.png");
    // 主页面图标
    QIcon main_icon = QIcon(":/icon/workdiary/all.png");
    // 数据图标
    QIcon data_icon = QIcon(":/icon/workdiary/data.png");
    // 计划图标
    QIcon plan_icon = QIcon(":/icon/workdiary/task-management.png");

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

    thread = new GetWindowThread(this);

    main_widget = new MainWidget();
    data_widget = new DataWidget();
    plan_widget = new PlanWidget();
    set_widget = new SetWidget();

    tab_widget = new QTabWidget(this);
    tab_widget->addTab(main_widget, main_icon, "主页");
    tab_widget->addTab(data_widget, data_icon, "数据");
    tab_widget->addTab(plan_widget, plan_icon, "计划");
    tab_widget->addTab(set_widget, set_icon, "设置");

    tab_widget->resize(this->size());

    QDateTime current_date_time = QDateTime::currentDateTime();
    current_table = current_date_time.toString("yyyy-MM-dd");

    qDebug() << "Current table name = " << current_table << endl;



    // 初始化数据库
    InitDataBase();


    connect(tray_icon, &QSystemTrayIcon::activated, this, &MainWindow::WorkDiaryTrayIconActivate);

    connect(tray_menu_act_quit, &QAction::triggered, this, &MainWindow::TrayMenuActQuit);
    connect(tray_menu_act_show_window, &QAction::triggered, this, &MainWindow::TrayMenuActShow);


    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitDataBase()
{
    // 初始化数据库并打开
    if (QSqlDatabase::contains()) {
        diary_database = QSqlDatabase::database();
    } else {
        diary_database = QSqlDatabase::addDatabase("QSQLITE");
        diary_database.setDatabaseName("WorkDiary.db");
    }

    if (!diary_database.open()) {
        qDebug() << "Error : Failed to connect database." << diary_database.lastError() << endl;;
    } else {
        qDebug() << "Success to connect database" << endl;

        // 检测是否存在当前日期的表
        QSqlQuery query;
        query.exec(QString("select count(*) from sqlite_master type='table' and name='%1'").arg(current_table));

//        if (query.next()) {
            if (query.value(0).toInt() == 0) {
                qDebug() << current_table << "table does no exist" << endl;
            } else {
                qDebug() << current_table << "table exist" << endl;
            }
//        }

    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    thread->CloseThread();
    thread->wait();

    // 关闭数据库
    diary_database.close();
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
