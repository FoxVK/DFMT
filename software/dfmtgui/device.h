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
    void freq_tunB_changed(double freq, unsigned rssi, unsigned snr, bool valid);

    void tunA_metrics(unsigned rssi, unsigned snr, unsigned multipath, bool is_valid, int freq_offset, unsigned stereo);
    void tunB_metrics(unsigned rssi, unsigned snr, unsigned multipath, bool is_valid, int freq_offset, unsigned stereo);


public slots:
    void tune(Tuner tuner, double freq_mhz);
    void seek(Tuner tuner, bool up);
    void check_metrics(Tuner tuner=Device::TUNER_A);
    void check_freq(Tuner tuner=Device::TUNER_A);

private:
    Libdfmt_device * dev;
    Devices *parrent;
    bool opened;
    double freq[2];
    bool tun_done[2];
    void freq_changed(Tuner tuner, double freq);

    Libdfmt_tuner *tuner[2];

    Libdfmt_tuner *get_tuner(Tuner tuner);
};

#endif // DEVICE_H
