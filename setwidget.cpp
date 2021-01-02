#include "setwidget.h"
#include "ui_setwidget.h"

#include <QPushButton>
#include <QSettings>
#include <QDir>
#include <QDebug>

SetWidget::SetWidget(QWidget *parent) : QWidget(parent),
    ui(new Ui::SetWidget())
{
    ui->setupUi(this);

    connect(ui->auto_start_button, &QPushButton::clicked, this, &SetWidget::AutoStartSlots);
}

SetWidget::~SetWidget()
{
    delete ui;
}

void SetWidget::AutoStartSlots()
{
    QSettings *reg = new QSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

    if (1) {
        QString strAppPath=QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
        //strAppPath.replace(QChar('/'),QChar('\\'),Qt::CaseInsensitive);
        qDebug()<< strAppPath << endl;
        reg->setValue("WorkDiary", strAppPath);
    } else {
        reg->setValue("WorkDiary", "");
    }
}
