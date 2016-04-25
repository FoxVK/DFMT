#include <QDebug>
#include "mainwin.h"
#include "ui_mainwin.h"

MainWin::MainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWin)
{
    connect(&devices, SIGNAL(dev_connected(Device*)), this, SLOT(dev_connected(Device*)));
    connect(&devices, SIGNAL(dev_diconnected(Device*)), this, SLOT(dev_removed(Device*)));
    ui->setupUi(this);


    devices.set_scan_interval();
    devices.scan();
}

MainWin::~MainWin()
{
    disconnect(&devices, SIGNAL(dev_connected(Device*)), this, SLOT(dev_connected(Device*)));
    disconnect(&devices, SIGNAL(dev_diconnected(Device*)), this, SLOT(dev_removed(Device*)));

    for (int i = 0; i < ui->Tabs->count(); i++)
    {
        DeviceForm *form = (DeviceForm*)ui->Tabs->widget(i);
        if(form)
        {
            ui->Tabs->removeTab(i);
        }
    }

    delete ui;
}



void MainWin::dev_connected(Device *dev)
{
    qDebug("connected");
    DeviceForm *form = new DeviceForm(dev, ui->Tabs);

    QString tab_name;
    tab_name.sprintf("Tuner");

    ui->Tabs->addTab(form, tab_name);
}

void MainWin::dev_removed(Device *dev)
{
    for (int i = 0; i < ui->Tabs->count(); i++)
    {
        DeviceForm *form = (DeviceForm*)ui->Tabs->widget(i);
        if(form)
        {
            if(form->get_dev() == dev)
            {
                ui->Tabs->removeTab(i);
            }
        }
    }
}
