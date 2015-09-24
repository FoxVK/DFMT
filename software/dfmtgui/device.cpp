#include "device.h"
#include "libdfmt.h"

#include <QDebug>

Device::Device(Libdfmt_device * dev, QObject *parent) :
    QObject(parent)
{
    this->dev = dev;
}



void Device::open()
{
    qDebug() << Q_FUNC_INFO << "=" << libdfmt_dev_open(this->dev);
}

void Device::close()
{
    libdfmt_dev_close(this->dev);
}


void Device::tune(Tuner tuner, double freq_mhz)
{
    unsigned int khz_tens = freq_mhz * 100;

    qDebug() << Q_FUNC_INFO << "=" << libdfmt_tune(dev, tuner, khz_tens);
}

void Device::was_removed()
{
    this->close();
}
