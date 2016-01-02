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

    for (int i = 0; i < ui->Tabs->count(); i++)
    {
        DeviceForm *form = (DeviceForm*)ui->Tabs->widget(i);
        if(form)
        {
            ui->Tabs->removeTab(i);
            delete form;
        }
    }

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
    DeviceForm *form = new DeviceForm(dev, ui->Tabs);

    QString tab_name;
    tab_name.sprintf("Tuner");

    ui->Tabs->addTab(form, tab_name);

    /*if(!ui->centralWidget->layout())
    {
        ui->centralWidget->setLayout(new QVBoxLayout(this));
    }*/

    //this->setCentralWidget(form);
    //ui->centralWidget->layout()->addWidget(form);


    //form->show();
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
                //delete form;
            }
        }

    }
}
