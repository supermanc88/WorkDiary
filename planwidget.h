#ifndef PLANWIDGET_H
#define PLANWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class PlanWidget;
}
QT_END_NAMESPACE

class PlanWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlanWidget(QWidget *parent = nullptr);
    ~PlanWidget();

signals:

private:
    Ui::PlanWidget *ui;

};

#endif // PLANWIDGET_H
