#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeEvent(QEvent *event);

public slots:
    void WorkDiaryTrayIconActivate(QSystemTrayIcon::ActivationReason reason);


private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *tray_icon;
};
#endif // MAINWINDOW_H
