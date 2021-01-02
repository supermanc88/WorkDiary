#ifndef SETWIDGET_H
#define SETWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class SetWidget; }
QT_END_NAMESPACE

class SetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SetWidget(QWidget *parent = nullptr);
    ~SetWidget();

public slots:
    void AutoStartSlots();

signals:

private:
    Ui::SetWidget *ui;

};

#endif // SETWIDGET_H
