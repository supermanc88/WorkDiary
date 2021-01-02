#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class DataWidget;
}
QT_END_NAMESPACE

class DataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DataWidget(QWidget *parent = nullptr);
    ~DataWidget();

signals:

private:
    Ui::DataWidget *ui;

};

#endif // DATAWIDGET_H
