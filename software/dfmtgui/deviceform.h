#ifndef DEVICEFORM_H
#define DEVICEFORM_H

#include <QWidget>
#include <QTimer>
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
    Device* get_dev();

private:
    Ui::DeviceForm *ui;
    Device *dev;
    bool sound_on;

    QTimer freq_check_tmr;

private slots:
    void tune_A(double freq);
    void seek_forward_A();
    void seek_back_A();
    void sound(bool on=true);


    void slider_moved(int value);
    void freq_changed(double value);
};

#endif // DEVICEFORM_H
