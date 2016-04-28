#ifndef NODEVICEFORM_H
#define NODEVICEFORM_H

#include <QWidget>

namespace Ui {
class NoDeviceForm;
}

class NoDeviceForm : public QWidget
{
    Q_OBJECT

public:
    explicit NoDeviceForm(QWidget *parent = 0);
    ~NoDeviceForm();

private:
    Ui::NoDeviceForm *ui;
};

#endif // NODEVICEFORM_H
