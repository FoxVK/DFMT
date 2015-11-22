#ifndef DEVICE_H
#define DEVICE_H

#include <QList>
#include <QObject>

typedef struct Libdfmt_device Libdfmt_device;
typedef struct Libdfmt_tuner Libdfmt_tuner;


class Devices;

class Device : public QObject
{
    Q_OBJECT
    friend class Devices;
public:

    typedef enum {TUNER_A=0, TUNER_B=1} Tuner;

    explicit Device( Libdfmt_device * dev, Devices *parrent);
    ~Device();

    bool open();
    void close();

    bool tunning_done(Tuner tuner);

signals:
    void freq_tunA_changed(double freq);
    void freq_tunB_changed(double freq);

    void tunA_metrics(double freq, unsigned rssi, unsigned snr, unsigned multipath, bool is_valid);
    void tunB_metrics(double freq, unsigned rssi, unsigned snr, unsigned multipath, bool is_valid);


public slots:
    void tune(Tuner tuner, double freq_mhz);
    void seek(Tuner tuner, bool up);
    void check_metrics(Tuner tuner);

private:
    Libdfmt_device * dev;
    Devices *parrent;
    bool opened;
    void freq_changed(Tuner tuner, float freq);

    Libdfmt_tuner *tuner[2];

    Libdfmt_tuner *get_tuner(Tuner tuner);
};

#endif // DEVICE_H
