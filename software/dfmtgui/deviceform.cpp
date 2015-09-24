#include "deviceform.h"
#include "ui_deviceform.h"

DeviceForm::DeviceForm(Device *dev, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceForm)
{
    ui->setupUi(this);
    this->dev = dev;
    dev->open();
}

DeviceForm::~DeviceForm()
{
    delete ui;
    dev->close();
}

void DeviceForm::tune_A(double freq)
{
    this->dev->tune(A, freq);
}

void DeviceForm::seek_back_A()
{

}

void DeviceForm::seek_forward_A()
{

}
