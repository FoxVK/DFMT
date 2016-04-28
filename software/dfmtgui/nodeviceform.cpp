#include "nodeviceform.h"
#include "ui_nodeviceform.h"

NoDeviceForm::NoDeviceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoDeviceForm)
{
    ui->setupUi(this);
}

NoDeviceForm::~NoDeviceForm()
{
    delete ui;
}
