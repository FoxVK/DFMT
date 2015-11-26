#include "device.h"
#include "libdfmt.h"

#include <QDebug>

Device::Device(Libdfmt_device * dev, Devices *parrent) :
    QObject((QObject*)parrent)
{
    this->dev = dev;
    this->parrent = parrent;
    this->opened = false;

    this->freq[0] = this->freq[1] = -1;
    this->tun_done[0] = this->tun_done[1] = true;
}

Device::~Device()
{
    this->close();
}



bool Device::open()
{
    if(this->opened)
        return true;

    Libdfmt_error err = libdfmt_dev_open(this->dev);
    if(err != LIBDFMT_OK)
    {
        this->opened = false;
        qFatal("libdfmt_dev_open returned %d.", err);
    }
    else
    {
        this->opened = true;
        libdfmt_get_tuners(this->dev, &this->tuner[0], &this->tuner[1]);
    }

    return this->opened;
}

void Device::close()
{
    libdfmt_dev_close(this->dev);
}



Libdfmt_tuner * Device::get_tuner(Tuner tuner)
{
    return (tuner == Device::TUNER_B) ? this->tuner[1] : this->tuner[0];
}


void Device::tune(Tuner tuner, double freq_mhz)
{
    int t = (tuner==Device::TUNER_A?1:0);

    if(freq_mhz==this->freq[t])
    {
        this->tun_done[t] = true;
        return;
    }
    this->tun_done[t] = false;
    qDebug() << Q_FUNC_INFO << "=" << libdfmt_tune(get_tuner(tuner), freq_mhz);
    freq_changed(tuner, (double)freq_mhz);
}

void Device::seek(Tuner tuner, bool up)
{
    qDebug() << Q_FUNC_INFO << "=" << libdfmt_seek(get_tuner(tuner), (up)?1:0);
}

void Device::check_freq(Tuner tuner)
{
    double *f = &freq[(tuner==Device::TUNER_A)?1:0];
    if(libdfmt_get_freq(get_tuner(tuner),f, NULL, NULL, NULL, NULL)==LIBDFMT_OK)
    {
        if(tuner==Device::TUNER_A)
            emit freq_tunA_changed(*f);
        else
            emit freq_tunB_changed(*f);
    }
}

void Device::check_metrics(Tuner tuner)
{
    unsigned rssi, snr, multipath, stereo;
    int is_valid, freq_offset;

    libdfmt_get_metrics(get_tuner(tuner), &rssi, &snr, &multipath, &is_valid, &freq_offset, &stereo);

    if(tuner == Device::TUNER_A)
        emit tunA_metrics(rssi, snr, multipath, is_valid, freq_offset, stereo);
    else
        emit tunB_metrics(rssi, snr, multipath, is_valid, freq_offset, stereo);

}

bool Device::tunning_done(Tuner tuner)
{

    int done = tun_done[tuner==Device::TUNER_A?0:1];
    if(done) return done;

    qDebug() << Q_FUNC_INFO << "=" << libdfmt_tunning_done(get_tuner(tuner), &done);
    return done;
}

void Device::freq_changed(Tuner tuner, double freq)
{
    if(tuner == Device::TUNER_A)
        emit(freq_tunA_changed(freq));
    else
        emit(freq_tunB_changed(freq));
}


