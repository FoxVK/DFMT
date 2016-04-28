#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include "device.h"
#include "devices.h"
#include "deviceform.h"
#include "nodeviceform.h"

namespace Ui {
class MainWin;
}

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = 0);
    ~MainWin();

public slots:

private:
    Ui::MainWin *ui;
    Devices devices;

    QTabWidget * tabs;
    NoDeviceForm * noDev;


    int tuner_no;
    QList<DeviceForm*> device_forms;


private slots:
    void dev_connected(Device *dev);
    void dev_removed(Device *dev);
    void update_central_widget();
};

#endif // MAINWIN_H
