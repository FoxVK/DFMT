#include "deviceform.h"
#include "ui_deviceform.h"
#include <QFile>

DeviceForm::DeviceForm(Device *dev, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceForm)
{
    sound_on = false;

    ui->setupUi(this);
    this->dev = dev;
    dev->open();

    //connect(dev, SIGNAL(freq_tunA_changed(double)), ui->freqSpinBox, SLOT(setValue(double)));
    //freq_check_tmr.start(500);
}

DeviceForm::~DeviceForm()
{
    delete ui;
    //dev->close(); close will be performed by devices
}

Device* DeviceForm::get_dev()
{
    return dev;
}

void DeviceForm::tune_A(double freq)
{
    this->dev->tune(Device::TUNER_A, freq);
}

void DeviceForm::seek_back_A()
{
    this->dev->seek(Device::TUNER_A, false);
}

void DeviceForm::seek_forward_A()
{
    this->dev->seek(Device::TUNER_A, true);
}

void DeviceForm::sound(bool on)
{
    if(on == sound_on)
        return;

   /* if(!sound_on)
    {
        QString path;
        path.sprintf("")
        QFile()
    }*/
}

void DeviceForm::slider_moved(int value)
{
    ui->freqSpinBox->setValue(((double)value)/10);
}

void DeviceForm::freq_changed(double value)
{
    ui->freqSlider->setValue(value*10);
}
