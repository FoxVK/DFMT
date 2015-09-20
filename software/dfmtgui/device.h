#ifndef DEVICE_H
#define DEVICE_H

#include <QList>
#include <QObject>


class Device : public QObject
{
    Q_OBJECT
public:

    static QList<Device*> open_all();
    static void close_all(QList<Device*>);

    explicit Device(QObject *parent = 0);



signals:
    void closed(Device *dev);

public slots:
    void tune(unsigned freq);
    void close();

private:
    static QList<Device*> opened_devs;


};

#endif // DEVICE_H
