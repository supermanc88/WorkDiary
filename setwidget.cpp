#include "setwidget.h"
#include "ui_setwidget.h"

SetWidget::SetWidget(QWidget *parent) : QWidget(parent),
    ui(new Ui::SetWidget())
{
    ui->setupUi(this);
}

SetWidget::~SetWidget()
{
    delete ui;
}
