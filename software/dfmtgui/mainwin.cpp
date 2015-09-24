#include <QDebug>
#include "mainwin.h"
#include "ui_mainwin.h"

MainWin::MainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWin)
{
    connect(&devices, SIGNAL(device_connected(Device*)), this, SLOT(dev_connected(Device*)));
    connect(&devices, SIGNAL(device_disconnected(Device*)), this, SLOT(dev_removed(Device*)));
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


void MainWin::dev_connected(Device *dev)
{
    qDebug("connected");
    DeviceForm *form = new DeviceForm(dev, this);


    form->show();
}

void MainWin::dev_removed(Device *dev)
{

}
