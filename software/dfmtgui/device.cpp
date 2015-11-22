#include "device.h"
#include "libdfmt.h"

#include <QDebug>

Device::Device(Libdfmt_device * dev, Devices *parrent) :
    QObject((QObject*)parrent)
{
    this->dev = dev;
    this->parrent = parrent;
    this->opened = false;
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
    //todo timer na spozdeni ladeni
    //todo udrzovat info o naladene frekvenci a pokud je naladena stejna neladit
    qDebug() << Q_FUNC_INFO << "=" << libdfmt_tune(get_tuner(tuner), freq_mhz);
    freq_changed(tuner, (float)freq_mhz);
}

void Device::seek(Tuner tuner, bool up)
{
    qDebug() << Q_FUNC_INFO << "=" << libdfmt_seek(get_tuner(tuner), (up)?1:0);
    //todo timer na testovani dokonceni ladeni
}

void Device::check_metrics(Tuner tuner)
{
    float freq = 0;
    unsigned rssi, snr, multipath;
    int is_valid;

    qDebug() << Q_FUNC_INFO << "=" << libdfmt_get_freq(get_tuner(tuner), &freq, &rssi, &snr, &multipath, &is_valid);
    if(freq != 0)
    {
        if(tuner == Device::TUNER_A)
            emit tunA_metrics((double)freq, rssi, snr, multipath, is_valid ? true : false);
        else
            emit tunB_metrics((double)freq, rssi, snr, multipath, is_valid ? true : false);
    }
}

bool Device::tunning_done(Tuner tuner)
{
    int done;
    qDebug() << Q_FUNC_INFO << "=" << libdfmt_tunning_done(get_tuner(tuner), &done);
    return done;
}

void Device::freq_changed(Tuner tuner, float freq)
{
    if(tuner == Device::TUNER_A)
        emit(freq_tunA_changed(freq));
    else
        emit(freq_tunB_changed(freq));
}


