#ifndef DEVICES_H
#define DEVICES_H

#include <QObject>
#include <QTimer>
#include <QList>
#include <QMap>

#include "libdfmt.h"

class Device;
typedef struct Libdfmt_device Libdfmt_device;

class Devices : public QObject
{
    Q_OBJECT
public:
    explicit Devices(QObject *parent = 0);
    ~Devices();




    QList<Device*> get_connected();

signals:
    void device_connected(Device *dev);
    void device_disconnected(Device *dev);


public slots:
    void scan_devs();
    void set_scan_interval(int seconds = 1);

private:
    QTimer timer;
    static Devices *devs_instance;
    static QMap<Libdfmt_device*, Device *> lib2dev;

    static void connected_cb(Libdfmt_device * lib_dev);
    static void removed_cb(Libdfmt_device *lib_dev);

    void emit_dev(Device *dev, bool connected);

};

#endif // DEVICES_H
