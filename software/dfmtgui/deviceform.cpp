#include "deviceform.h"
#include "ui_deviceform.h"
#include <QFile>

DeviceForm::DeviceForm(Device *dev, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceForm)
{
    sound_on = false;

    ui->setupUi(this);
    this->dev = dev;
    dev->open();

    connect(dev, SIGNAL(freq_tunA_changed(double)), this, SLOT(freq_changed(double)));

    connect(dev, SIGNAL(tunA_metrics(uint,uint,uint,bool,int,uint)), this, SLOT(metrics_changed(uint,uint,uint,bool,int,uint)));
    connect(&task[0].tmr, SIGNAL(timeout()), this, SLOT(task_A()));
    task[0].tmr.start(1000);

    connect(&freq_change_tmr, SIGNAL(timeout()), this, SLOT(freq_chg_tmr_fired()));
    freq_change_tmr.setSingleShot(true);
    freq_change_tmr.setInterval(10);
}

DeviceForm::~DeviceForm()
{
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
    task[0].seek = Task::SEEK_DOWN;
}

void DeviceForm::seek_forward_A()
{
    task[0].seek = Task::SEEK_UP;
}

void DeviceForm::sound(bool on)
{
    if(on == sound_on)
        return;

   /* if(!sound_on)
    {
        QString path;
        path.sprintf("")
        QFile()
    }*/
}

void DeviceForm::freq_chk_trm_fired()
{
    dev->check_metrics();
}

void DeviceForm::freq_chg_tmr_fired()
{
    task[0].tune = true;
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
    static int metrics_tmr = 0;
    int time = 100;
    Task *t = &task[0];
    Device::Tuner tuner = Device::TUNER_A;

    switch(t->state)
    {
        case Task::S_TUNE:
            dev->tune(tuner, ui->freqSpinBox->value());
            t->state = Task::S_TUNING;
            t->tune = false;
            break;

        case Task::S_TUNING:
            if(dev->tunning_done(tuner))
                t->state = Task::S_METRICS;
            break;

        case Task::S_SEEK:
            dev->seek(tuner, (t->seek==Task::SEEK_UP));
            t->seek = Task::SEEK_NO;
            t->state = Task::S_SEEKING;
            time = 900;
            break;

        case Task::S_SEEKING:
            if(dev->tunning_done(tuner))
                t->state = Task::S_CHECK_FREQ;
            break;

        case Task::S_CHECK_FREQ:
            dev->check_freq(tuner);
            t->state = Task::S_METRICS;
            break;

        case Task::S_METRICS:
            if(t->tune)
            {
                t->state = Task::S_TUNE;
            }
            else if(t->seek)
            {
                t->state = Task::S_SEEK;
            }
            else
            {
                metrics_tmr++;
                if(metrics_tmr>=7)
                {
                    dev->check_metrics(tuner);
                    metrics_tmr = 0;
                }
            }
            break;

    }

    t->tmr.start(time);
}

void DeviceForm::task_B()
{
    int time = 200;
    Task *t = &task[1];
    Device::Tuner tuner = Device::TUNER_B;

    switch(t->state)
    {
        case Task::S_TUNE:
            dev->tune(tuner, ui->freqSpinBox->value());
            t->state = Task::S_TUNING;
            t->tune = false;
            break;

        case Task::S_TUNING:
            if(dev->tunning_done(tuner))
                t->state = Task::S_METRICS;
            break;

        case Task::S_SEEK:
            dev->seek(tuner, (t->seek==Task::SEEK_UP));
            t->seek = Task::SEEK_NO;
            t->state = Task::S_SEEKING;
            time = 900;
            break;

        case Task::S_SEEKING:
            if(dev->tunning_done(tuner))
                t->state = Task::S_CHECK_FREQ;
            break;

        case Task::S_CHECK_FREQ:
            dev->check_freq(tuner);
            t->state = Task::S_METRICS;
            break;

        case Task::S_METRICS:
            if(t->tune)
            {
                t->state = Task::S_TUNE;
            }
            else if(t->seek)
            {
                t->state = Task::S_SEEK;
            }
            else
            {
                dev->check_metrics(tuner);
                time = 400;
            }
            break;

    }


    t->tmr.start(time);
}
