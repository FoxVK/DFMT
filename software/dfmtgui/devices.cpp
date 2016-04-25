#include "devices.h"
#include "device.h"
#include "libdfmt.h"

#include <QDebug>


Devices *Devices::instance = NULL;

void Devices::dap_cb(Libdfmt_device *ld)
{
    Devices *ds = Devices::get_instance();
    ds->dev_added(new Device(ld, ds));
}

void Devices::dda_cb(Libdfmt_device *ld)
{
    Devices *ds = Devices::get_instance();
    ds->dev_removed(ld);
}

void Devices::dev_added(Device *dev)
{

    lib2dev.insert(dev->dev, dev);
    emit this->dev_connected(dev);
}

void Devices::dev_removed(Libdfmt_device *ld)
{
    if(lib2dev.contains(ld))
    {
        Device *d = lib2dev[ld];
        dev_removed(d);
    }
}

void Devices::dev_removed(Device *dev)
{
    lib2dev.remove(dev->dev);
    emit this->dev_diconnected(dev);
    //delete dev;
}

Devices::Devices(QObject *parent) :
    QObject(parent)
{
    Devices::instance = this;

    libdfmt_init(0);

    libdfmt_new_dev_cb(dap_cb);
    libdfmt_removed_dev_cb(dda_cb);

    connect(&this->timer, SIGNAL(timeout()), this, SLOT(scan()));
}

Devices::~Devices()
{
    foreach(Device *d, lib2dev.values())
    {
        emit this->dev_diconnected(d);
        delete d;
    }

    libdfmt_exit();
}

Devices* Devices::get_instance()
{
    if(!instance)
        instance = new Devices;
    return instance;
}

void Devices::set_scan_interval(int msec)
{
    timer.setInterval(msec);
    if(msec>0)
        timer.start();
}


void Devices::scan()
{
    libdfmt_scan_devs();
}
