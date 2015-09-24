#ifndef DEVICEFORM_H
#define DEVICEFORM_H

#include <QWidget>
#include "device.h"

namespace Ui {
class DeviceForm;
}

class DeviceForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceForm(Device *dev ,QWidget *parent = 0);
    ~DeviceForm();

private:
    Ui::DeviceForm *ui;
    Device *dev;

private slots:
    void tune_A(double freq);
    void seek_forward_A();
    void seek_back_A();
};

#endif // DEVICEFORM_H
