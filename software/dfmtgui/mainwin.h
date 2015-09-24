#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include "device.h"
#include "devices.h"
#include "deviceform.h"

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
    void test();

private:
    Ui::MainWin *ui;
    Devices devices;

private slots:
    void dev_connected(Device *dev);
    void dev_removed(Device *dev);
};

#endif // MAINWIN_H
