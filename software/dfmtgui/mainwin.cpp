#include <QDebug>
#include "mainwin.h"
#include "ui_mainwin.h"

#include "libdfmt.h"


MainWin::MainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::test()
{
    qDebug() << Q_FUNC_INFO;

    libdfmt_init(2);
    libdfmt_scan_devs();
    Libdfmt_device *devs = libdfmt_get_all_devs();

    while(devs)
    {
        qDebug("Found tuner %d", libdfmt_get_dev_address(devs));
        devs = libdfmt_next(devs);
    }

    libdfmt_exit();


    qDebug() << Q_FUNC_INFO << "Done...";
}
