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
    this->radio_text_ABflag = true;
}

Device::~Device()
{
    qDebug() << Q_FUNC_INFO;
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
    qDebug() << Q_FUNC_INFO;
    libdfmt_dev_close(this->dev);
    this->dev = NULL;
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

    if(libdfmt_tune(get_tuner(tuner), freq_mhz)!=LIBDFMT_OK)
        return;

    if(tuner == Device::TUNER_A)
    {
        freq_changed(tuner, (double)freq_mhz);
        radio_text = "";
        emit radioText(this->radio_text);
    }
}

void Device::seek(Tuner tuner, bool up)
{
    libdfmt_seek(get_tuner(tuner), (up)?1:0);

    if(tuner == Device::TUNER_A)
    {
        radio_text = "";
        emit radioText(this->radio_text);
    }
}

void Device::check_freq(Tuner tuner)
{
    unsigned rssi, snr;
    int valid;

    double *f = &freq[(tuner==Device::TUNER_A)?1:0];

    if(libdfmt_get_freq(get_tuner(tuner),f, &rssi, &snr, NULL, &valid)==LIBDFMT_OK)
    {
        if(tuner==Device::TUNER_A)
            emit freq_tunA_changed(*f);
        else
            emit freq_tunB_changed(*f, rssi, snr, valid);
    }
}

bool Device::receive_rds(bool receive, Tuner tuner)
{
    if(libdfmt_rds_receiving(get_tuner(tuner), receive) == LIBDFMT_OK)
        return true;
    return false;
}

void Device::check_rds(Tuner tuner)
{
    if(tuner == TUNER_A)
    {
        Libdfmt_rds_group g;
        int cnt;
        for(int i=0; i<10; i++)
        {
            cnt = 0;
            if(libdfmt_rds_read(get_tuner(tuner), &g, &cnt)!=LIBDFMT_OK)
                return;
            if(cnt == 0)
                return;

            if(!g.blockBvalid)
                continue;

            int grptype = g.blockB>>11;

            if(grptype != 4 && grptype != 5)
                continue;

            int segment = g.blockB & 0x000F;

            bool ab = (g.blockB & 1<<4) ? true : false;

            if( (!ab & radio_text_ABflag) || (ab && !radio_text_ABflag) )
                radio_text = "";

            radio_text_ABflag = ab;

            //if(segment == 0)
                //emit radioText(this->radio_text);

            int offset;
            QString piece;
            if(grptype == 4)
            {
                offset = segment*4;

                if(g.blockCvalid)
                {
                    piece.append( (QChar((g.blockC>>8) & 0x00ff)));
                    piece.append( (QChar((g.blockC   ) & 0x00ff)));
                }
                else
                {
                    piece.append("**");
                }
            }
            else
            {
                offset = segment * 2;
            }

            if(g.blockDvalid)
            {
                piece.append( (QChar((g.blockD>>8) & 0x00ff)));
                piece.append( (QChar((g.blockD   ) & 0x00ff)));
            }
            else
            {
                piece.append("**");
            }

            this->radio_text.remove(offset, piece.size());
            this->radio_text.insert(offset, piece);
            /*qDebug() <<g.blockA << ab << segment <<"|"
                    << (char)((g.blockC>>8) & 0x00ff)
                       << (char)((g.blockC) & 0x00ff)
                          << (char)((g.blockD>>8) & 0x00ff)
                             << (char)((g.blockD) & 0x00ff);
            */
            //qDebug("%x  %x %x %x %x  %c %c %c",g.blockA,   (char)((g.blockC>>8) & 0x00ff), (char)((g.blockC) & 0x00ff), (char)((g.blockD>>8) & 0x00ff), (char)((g.blockD) & 0x00ff),        (char)((g.blockC) & 0x00ff), (char)((g.blockD>>8) & 0x00ff), (char)((g.blockD) & 0x00ff));
            emit radioText(this->radio_text);

            if(cnt == 1)
                return;
        }
        qDebug() << "cnt =" << cnt;
    }
}

void Device::check_metrics(Tuner tuner)
{
    unsigned rssi, snr, multipath, stereo;
    int is_valid, freq_offset;

    if(libdfmt_get_metrics(get_tuner(tuner), &rssi, &snr, &multipath, &is_valid, &freq_offset, &stereo)!=LIBDFMT_OK)
        return;

    if(tuner == Device::TUNER_A)
        emit tunA_metrics(rssi, snr, multipath, is_valid, freq_offset, stereo);
    else
        emit tunB_metrics(rssi, snr, multipath, is_valid, freq_offset, stereo);

}

bool Device::tunning_done(Tuner tuner)
{

    int done = tun_done[tuner==Device::TUNER_A?0:1];
    if(done) return done;

    if(libdfmt_tunning_done(get_tuner(tuner), &done)!=LIBDFMT_OK)
        return true;
    else
        return done;
}

void Device::freq_changed(Tuner tuner, double freq)
{
    if(tuner == Device::TUNER_A)
        emit(freq_tunA_changed(freq));
}


