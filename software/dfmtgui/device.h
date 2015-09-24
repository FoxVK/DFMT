#ifndef DEVICE_H
#define DEVICE_H

#include <QList>
#include <QObject>

typedef struct Libdfmt_device Libdfmt_device;


typedef enum {A=0, B=1} Tuner;


class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device( Libdfmt_device * dev, QObject *parent = 0);

    void open();
    void close();

signals:

public slots:
    void was_removed();
    void tune(Tuner tuner, double freq_mhz);

private:
    Libdfmt_device * dev;
    bool connected;


};

#endif // DEVICE_H
