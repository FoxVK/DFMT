#include "device.h"

#include "libdfmt.h"

Device::Device(QObject *parent) :
    QObject(parent)
{
}

QList<Device*> Device::open_all()
{
    QList<Device*> devs;

    return devs;
}

void Device::close_all(QList<Device*>)
{

}

void Device::tune(unsigned freq)
{
    (void)freq;
}

void Device::close()
{

}
