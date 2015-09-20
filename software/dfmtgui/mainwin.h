#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include "device.h"

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
    QList<Device*> devices;
};

#endif // MAINWIN_H
