#ifndef DEVICEFORM_H
#define DEVICEFORM_H

#include <QWidget>
#include <QTimer>
#include "device.h"

namespace Ui {
class DeviceForm;
}

class DeviceForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceForm(Device *dev ,QWidget *parent = 0);
    ~DeviceForm();
    Device* get_dev();

private:
    Ui::DeviceForm *ui;
    Device *dev;
    bool sound_on;

    struct Task{
        Task(){state=S_METRICS; tmr.setSingleShot(true); tune=false; seek=SEEK_NO;}

        enum{S_TUNE, S_TUNING, S_SEEK, S_SEEKING, S_CHECK_FREQ, S_METRICS}state;
        bool tune;
        enum{SEEK_NO=0, SEEK_UP=1, SEEK_DOWN=2}seek;
        QTimer tmr;
    }task[2];

    QTimer freq_change_tmr;


private slots:
    void tune_A(double freq);
    void seek_forward_A();
    void seek_back_A();
    void sound(bool on=true);


    void freq_chk_trm_fired();
    void freq_chg_tmr_fired();
    void slider_moved(int value);

    void freq_changed(double value);
    void metrics_changed(unsigned rssi, unsigned snr, unsigned multipath, bool is_valid, int freq_offset, unsigned stereo);

    void task_A();
    void task_B();
};

#endif // DEVICEFORM_H
