#include <QDebug>
#include <QMessageBox>
#include "mainwin.h"
#include "ui_mainwin.h"

MainWin::MainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWin)
{
    connect(&devices, SIGNAL(dev_connected(Device*)), this, SLOT(dev_connected(Device*)));
    connect(&devices, SIGNAL(dev_diconnected(Device*)), this, SLOT(dev_removed(Device*)));
    ui->setupUi(this);

    this->noDev = new NoDeviceForm(this);
    this->noDev->setVisible(false);
    this->tabs = new QTabWidget(this);
    this->tabs->setVisible(false);

    tuner_no = 0;

    update_central_widget();

    devices.set_scan_interval();
    devices.scan();
}

MainWin::~MainWin()
{
    disconnect(&devices, SIGNAL(dev_connected(Device*)), this, SLOT(dev_connected(Device*)));
    disconnect(&devices, SIGNAL(dev_diconnected(Device*)), this, SLOT(dev_removed(Device*)));

    delete ui;
}



void MainWin::dev_connected(Device *dev)
{

    DeviceForm *form;



    if(dev->open())
    {
        form = new DeviceForm(dev, tabs);
        form->no = ++tuner_no;
        device_forms.append(form);

    }
    else
    {
        QMessageBox mbox;
        mbox.setIcon(QMessageBox::Warning);
        mbox.setText("Can not open connected tuner.");
        mbox.setInformativeText("This is usually caused by another runing instance of this application or by missing driver.");
        mbox.setStandardButtons(QMessageBox::Ok);
        mbox.setDetailedText(
                    QString("lidfmt returned error code %1 (%2)")
                    .arg( dev->get_last_lib_error())
                    .arg(Device::lib_error_to_text(dev->get_last_lib_error()))
                    );
        mbox.exec();
    }

    update_central_widget();
}

void MainWin::dev_removed(Device *dev)
{
    for (int i = 0; i < device_forms.count(); i++)
    {
        DeviceForm *form = device_forms.at(i);
        if(form->get_dev() == dev)
        {
            device_forms.removeAt(i);
            form->deleteLater();
        }
    }

    update_central_widget();
}

void MainWin::update_central_widget()
{
    QWidget * current = NULL;
    for(int i=0; i<ui->layout->count(); i++)
    {
        QLayoutItem * item = ui->layout->itemAt(i);

        if(item)
        {
            ui->layout->removeItem(item);
            if(!item->widget())
                delete item;
            else
            {
                current = item->widget();
                current->setVisible(false);
            }
        }
    }

    switch(device_forms.count())
    {
    case 0:
        ui->layout->addWidget(static_cast<QWidget*>(this->noDev));
        break;
    case 1:
        ui->layout->addWidget(device_forms.at(0));
        break;
    default:
    {
         ui->layout->addWidget(static_cast<QWidget*>(this->tabs));

         tabs->clear();
         for(int i=0; i<device_forms.count(); i++)
         {
             QString tab_name;
             if(device_forms.at(i)->no <= 1)
                 tab_name.sprintf("Tuner");
             else
                 tab_name.sprintf("Tuner #%d", device_forms.at(i)->no);

             tabs->addTab(device_forms.at(i), tab_name);
         }
    }
    }//switch

    ui->layout->itemAt(0)->widget()->setVisible(true);
}
