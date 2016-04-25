#ifndef DEVICEFORM_H
#define DEVICEFORM_H

#include <QWidget>
#include <QTimer>
#include <QList>
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

    struct TaskA{
        TaskA(){state=S_METRICS; tmr.setSingleShot(true); tune=false; seek=SEEK_NO; st_tout=0;  metrics_tmr = 0;}

        enum{S_TUNE, S_TUNING, S_SEEK, S_SEEKING, S_CHECK_FREQ, S_METRICS, S_RDS_ON, S_RDS_RCV}state;
        bool tune;
        enum{SEEK_NO=0, SEEK_UP=1, SEEK_DOWN=2}seek;
        QTimer tmr;
        int st_tout;
       int metrics_tmr;

    }taskA;

    struct TaskB{
        TaskB()
        {
            super_state = SS_SEEK;
            ss_seek = SS_S_INIT;
            ss_update = SS_U_INIT;
            tmr.setSingleShot(true);
            table_ptr = metrics_table_ptr = 0;
            super_state_tmr.setSingleShot(true);
            switch_ss = false;
            st_tout = 0;
        }

        enum{SS_SEEK, SS_UPDATE}super_state;
        enum{SS_S_INIT, SS_S_SEEK, SS_S_SEEKING, SS_S_CHECK_FREQ} ss_seek;
        enum{SS_U_INIT, SS_U_TUNE, SS_U_TUNING, SS_U_METRICS}ss_update;
        QTimer tmr, super_state_tmr;
        QList<double> freq;
        int table_ptr, metrics_table_ptr;
        bool switch_ss;
        int st_tout;

    }taskB;


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
    void freq_cangedB(double freq, unsigned rssi, unsigned snr, bool valid);
    void metrics_changed(unsigned rssi, unsigned snr, unsigned multipath, bool is_valid, int freq_offset, unsigned stereo);
    void metrics_changedB(unsigned rssi, unsigned snr, unsigned multipath, bool is_valid, int freq_offset, unsigned stereo);

    void task_A();
    void task_B();

    void taskB_switch_ss_tmr() {
        taskB.switch_ss = true;
    }
};

#endif // DEVICEFORM_H
