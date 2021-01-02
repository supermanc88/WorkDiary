#include "planwidget.h"
#include "ui_planwidget.h"

PlanWidget::PlanWidget(QWidget *parent) : QWidget(parent),
    ui(new Ui::PlanWidget())
{
    ui->setupUi(this);
}

PlanWidget::~PlanWidget()
{
    delete ui;
}
