#ifndef DEVICES_H
#define DEVICES_H

#include <QObject>
#include <QTimer>
#include <QList>
#include <QMap>

#include "libdfmt.h" //TODO make forward declaration.

class Device;
typedef struct Libdfmt_device Libdfmt_device;

class Devices : public QObject
{
    Q_OBJECT
    friend class Device;
public:
    explicit Devices(QObject *parent = 0);
    ~Devices();

    static Devices* get_instance();

signals:
    void dev_connected(Device* dev);
    void dev_diconnected(Device*dev);

public slots:
    void scan();
    void set_scan_interval(int msec=1000);

private:
    void dev_removed(Device *dev);
    void dev_added(Device *dev);
    void dev_removed(Libdfmt_device *ld);

    static Devices *instance;
    QMap<Libdfmt_device*, Device*> lib2dev;

    QTimer timer;

    static void dap_cb(Libdfmt_device *ld);
    static void dda_cb(Libdfmt_device *ld);
};

#endif // DEVICES_H
