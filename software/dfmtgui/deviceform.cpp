#include "deviceform.h"
#include "ui_deviceform.h"
#include <QFile>
#include <QDebug>

#define FREQ_HIGH 107
#define FREQ_LOW 80
#define TUNE_TOUT_B 600     //[ms]
#define SEEK_TOUT_B 1500    //[ms]
#define TUNE_TOUT_A 600     //[ms]
#define SEEK_TOUT_A 1500    //[ms]

DeviceForm::DeviceForm(Device *dev, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceForm)
{
    sound_on = false;

    ui->setupUi(this);
    this->dev = dev;

    connect(dev, SIGNAL(radioText(QString)), this->ui->rtLabel, SLOT(setText(QString)));

    connect(dev, SIGNAL(freq_tunA_changed(double)), this, SLOT(freq_changed(double)));

    connect(dev, SIGNAL(tunA_metrics(uint,uint,uint,bool,int,uint)), this, SLOT(metrics_changed(uint,uint,uint,bool,int,uint)));
    connect(&taskA.tmr, SIGNAL(timeout()), this, SLOT(task_A()));

    connect(dev, SIGNAL(tunB_metrics(uint,uint,uint,bool,int,uint)), this, SLOT(metrics_changedB(uint,uint,uint,bool,int,uint)));
    connect(dev, SIGNAL(freq_tunB_changed(double,uint,uint,bool)), this, SLOT(freq_cangedB(double,uint,uint,bool)));
    connect(&taskB.tmr, SIGNAL(timeout()), this, SLOT(task_B()));

    connect(&this->taskB.super_state_tmr, SIGNAL(timeout()), this, SLOT(taskB_switch_ss_tmr()));


    connect(&freq_change_tmr, SIGNAL(timeout()), this, SLOT(freq_chg_tmr_fired()));
    freq_change_tmr.setSingleShot(true);
    freq_change_tmr.setInterval(10);

    taskA.tmr.start(1000);
    taskB.tmr.start(900);
}

DeviceForm::~DeviceForm()
{
    //qDebug() << Q_FUNC_INFO;
    taskA.tmr.stop();
    taskB.tmr.stop();
    delete ui;
    //dev->close(); close will be performed by devices
}

Device* DeviceForm::get_dev()
{
    return dev;
}

void DeviceForm::tune_A(double freq)
{
    (void) freq;
    freq_change_tmr.start();
}

void DeviceForm::seek_back_A()
{
    taskA.seek = TaskA::SEEK_DOWN;
}

void DeviceForm::seek_forward_A()
{
    taskA.seek = TaskA::SEEK_UP;
}

void DeviceForm::sound(bool on)
{
    if(on == sound_on)
        return;
}

void DeviceForm::freq_chk_trm_fired()
{
    dev->check_metrics();
}

void DeviceForm::freq_chg_tmr_fired()
{
    taskA.tune = true;
}

void DeviceForm::slider_moved(int value)
{
    ui->freqSpinBox->setValue(((double)value)/10);
}

void DeviceForm::freq_changed(double value)
{
    ui->freqSlider->setValue(value*10);
}

void DeviceForm::metrics_changed(unsigned rssi, unsigned snr, unsigned multipath, bool is_valid, int freq_offset, unsigned stereo)
{
    (void)freq_offset;
    (void)stereo;

    QString snr_str, rssi_str;
    snr_str.sprintf("SNR: %ddB", snr);
    rssi_str.sprintf("RSSI: %ddBμV", rssi);

    (void) multipath;
    (void) is_valid;

    ui->rssiLabel->setText(rssi_str);
    ui->snrLabel->setText(snr_str);
}

void DeviceForm::task_A()
{
    int time = 100;
    TaskA *t = &taskA;
    Device::Tuner tuner = Device::TUNER_A;

    switch(t->state)
    {
        case TaskA::S_TUNE:
            dev->tune(tuner, ui->freqSpinBox->value());
            t->state = TaskA::S_TUNING;
            t->tune = false;
            t->st_tout = 0;
            break;

        case TaskA::S_TUNING:
            if(dev->tunning_done(tuner))
                t->state = TaskA::S_METRICS;

            t->st_tout+=t->tmr.interval();
            if(t->st_tout>TUNE_TOUT_A)
                t->state = TaskA::S_TUNE;

            break;

        case TaskA::S_SEEK:
            dev->seek(tuner, (t->seek==TaskA::SEEK_UP));
            t->seek = TaskA::SEEK_NO;
            t->state = TaskA::S_SEEKING;
            time = 900;
            t->st_tout = 0;
            break;

        case TaskA::S_SEEKING:
            if(dev->tunning_done(tuner))
                t->state = TaskA::S_CHECK_FREQ;

            t->st_tout+=t->tmr.interval();
            if(t->st_tout>SEEK_TOUT_A)
                t->state = TaskA::S_TUNE;

            break;

        case TaskA::S_CHECK_FREQ:
            dev->check_freq(tuner);
            t->state = TaskA::S_METRICS;
            break;

        case TaskA::S_METRICS:
            if(t->tune)
            {
                t->state = TaskA::S_TUNE;
            }
            else if(t->seek)
            {
                t->state = TaskA::S_SEEK;
            }
            else
            {
                t->metrics_tmr++;
                if(t->metrics_tmr>=7)
                {
                   dev->check_metrics(tuner);
                   t-> metrics_tmr = 0;
                   t->state = TaskA::S_RDS_ON;
                }
            }
            break;

        case TaskA::S_RDS_ON:
            if(t->tune)
            {
                t->state = TaskA::S_TUNE;
            }
            else if(t->seek)
            {
                t->state = TaskA::S_SEEK;
            }
            else
            {
                if(dev->receive_rds(true))
                    t->state = TaskA::S_RDS_RCV;
            }
            break;



        case TaskA::S_RDS_RCV:
            if(t->tune)
            {
                t->state = TaskA::S_TUNE;
            }
            else if(t->seek)
            {
                t->state = TaskA::S_SEEK;
            }
            else
            {
                dev->check_rds();
            }
            break;

    }

    t->tmr.start(time);
}

void DeviceForm::task_B()
{
    int time = 200;
    TaskB *t = &taskB;
    Device::Tuner tuner = Device::TUNER_B;

    switch(t->super_state)
    {
        case TaskB::SS_SEEK:
            switch(t->ss_seek)
            {
                case TaskB::SS_S_INIT:
                    dev->tune(tuner, FREQ_LOW);
                    t->ss_seek = TaskB::SS_S_SEEKING;
                    t->super_state_tmr.start(5000);
                    break;
                \
                case TaskB::SS_S_SEEK:
                    if(t->switch_ss)
                    {
                        t->switch_ss = false;
                        t->ss_seek = TaskB::SS_S_INIT;
                        t->ss_update = TaskB::SS_U_INIT;
                        t->super_state = TaskB::SS_UPDATE;
                    }
                    else
                    {
                        dev->seek(tuner, true);
                        t->ss_seek = TaskB::SS_S_SEEKING;
                        t->st_tout = 0;
                    }
                    break;

                case TaskB::SS_S_SEEKING:
                    t->st_tout+= t->tmr.interval();
                    if(t->st_tout>SEEK_TOUT_B)
                        t->ss_seek = TaskB::SS_S_SEEK;

                    if(dev->tunning_done(tuner))
                        t->ss_seek = TaskB::SS_S_CHECK_FREQ;

                    break;

                case TaskB::SS_S_CHECK_FREQ:
                    dev->check_freq(tuner);
                    t->ss_seek = TaskB::SS_S_SEEK;
                    break;
            }
            break;

        case TaskB::SS_UPDATE:
            switch(t->ss_update)
            {
                case TaskB::SS_U_INIT:
                    t->table_ptr = 0;
                    t->ss_update = TaskB::SS_U_TUNE;
                    t->super_state_tmr.start(7000);

                case TaskB::SS_U_TUNE:
                    if(t->switch_ss || t->freq.size()==0)
                    {
                        t->switch_ss = false;
                        t->super_state = TaskB::SS_SEEK;
                        t->ss_update = TaskB::SS_U_INIT;
                    }
                    else
                    {
                        dev->tune(tuner, t->freq.at(t->table_ptr));
                        t->ss_update = TaskB::SS_U_TUNING;
                    }
                    break;

                case TaskB::SS_U_TUNING:
                    if(dev->tunning_done(tuner))
                        t->ss_update = TaskB::SS_U_METRICS;

                    t->st_tout+= t->tmr.interval();
                    if(t->st_tout>SEEK_TOUT_B)
                        t->ss_update = TaskB::SS_U_TUNE;

                    break;

                case TaskB::SS_U_METRICS:
                    t->metrics_table_ptr = t->table_ptr;
                    dev->check_metrics(tuner);
                    t->ss_update = TaskB::SS_U_TUNE;

                    break;
            }
            break;
    }

    t->tmr.start(time);
}


void DeviceForm::freq_cangedB(double freq, unsigned rssi, unsigned snr, bool valid)
{
    //qDebug("%s f=%f snr=%d valid=%d rssi=%d", Q_FUNC_INFO, freq, snr, valid, rssi);

    int i;
    QTableWidget *t = ui->stationsTable;

    QString freqS, rssiS, snrS;
    freqS.sprintf("%.2fMHz", freq);
    rssiS.sprintf("%ddBμV", rssi);
    snrS.sprintf("%ddB", snr);

    for(i=0; i<taskB.freq.size(); i++)
    {
        if(taskB.freq[i]==freq)
        {   if(valid)
            {//update
                QTableWidgetItem *itm;

                itm = t->item(i, 0);
                if(itm) itm->setText(freqS);
                else qCritical() << Q_FUNC_INFO << "table item freq not found";

                itm = t->item(i, 1);
                if(itm) itm->setText(rssiS);
                else qCritical() << Q_FUNC_INFO << "table item rssi not found";

                itm = t->item(i, 2);
                if(itm) itm->setText(snrS);
                else qCritical() << Q_FUNC_INFO << "table item snr not found";
            }
            else
            { //delete
                //qDebug("delete");
                taskB.freq.removeAt(i);
                t->removeRow(i);
            }
            return;
        }
        else if(taskB.freq[i]>freq)
        {   //insert one back
            //i--;
            break;
        }
    }

    //insert
    if(valid)
    {
        //qDebug("insert");
        taskB.freq.insert(i, freq);
        t->insertRow(i);
        t->setItem(i, 0, new QTableWidgetItem(freqS));
        t->setItem(i, 1, new QTableWidgetItem(rssiS));
        t->setItem(i, 2, new QTableWidgetItem(snrS));
    }
}

void DeviceForm::metrics_changedB(unsigned rssi, unsigned snr, unsigned multipath, bool is_valid, int freq_offset, unsigned stereo)
{
    //qDebug("%s snr=%d valid=%d", Q_FUNC_INFO, snr, is_valid);
    (void) multipath; (void)stereo; (void)freq_offset;
    freq_cangedB(taskB.freq.at(taskB.metrics_table_ptr), rssi, snr, is_valid);
}
