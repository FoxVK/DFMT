#include "devices.h"
#include "device.h"
#include "libdfmt.h"

Devices* Devices::devs_instance = NULL;
QMap<Libdfmt_device*, Device *> Devices::lib2dev;

Devices::Devices(QObject *parent) :
    QObject(parent)
{
    static int instances = 0;

    if(instances != 0)
        qFatal("Do not create more tahn one instance of class Devices");
    instances++;

    devs_instance = this;

    libdfmt_init(0);

    libdfmt_new_dev_cb(connected_cb);
    libdfmt_removed_dev_cb(removed_cb);

    connect(&this->timer, SIGNAL(timeout()), this, SLOT(scan_devs()));

    timer.start(1000);
}

Devices::~Devices()
{
    libdfmt_exit();
}

void Devices::set_scan_interval(int seconds)
{
    timer.setInterval(seconds * 1000);
}

QList<Device*> Devices::get_connected()
{
    return lib2dev.values();
}

void Devices::emit_dev(Device *dev, bool connected)
{
    if(connected)
        emit device_connected(dev);
    else
        emit device_disconnected(dev);
}

void Devices::connected_cb(Libdfmt_device *lib_dev)
{
    Device * d = new Device(lib_dev);
    lib2dev.insert(lib_dev, d);
    devs_instance->emit_dev(d, true);
}

void Devices::removed_cb(Libdfmt_device *lib_dev)
{
    Device * d = Devices::lib2dev.value(lib_dev, NULL);
    devs_instance->emit_dev(d, false);
}

void Devices::scan_devs()
{
    libdfmt_scan_devs();
}
