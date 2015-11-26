/********************************************************************************
** Form generated from reading UI file 'deviceform.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEFORM_H
#define UI_DEVICEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeviceForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frqFrame;
    QVBoxLayout *verticalLayout;
    QDoubleSpinBox *freqSpinBox;
    QSlider *freqSlider;
    QSpacerItem *horizontalSpacer;
    QWidget *buttosWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *seekBackButton;
    QPushButton *playButton;
    QPushButton *seekForwardButton;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *rssiLabel;
    QLabel *snrLabel;
    QSpacerItem *horizontalSpacer_3;
    QFrame *stationsFrame;
    QHBoxLayout *horizontalLayout_4;
    QTableWidget *stationsTable;

    void setupUi(QWidget *DeviceForm)
    {
        if (DeviceForm->objectName().isEmpty())
            DeviceForm->setObjectName(QStringLiteral("DeviceForm"));
        DeviceForm->resize(483, 286);
        verticalLayout_2 = new QVBoxLayout(DeviceForm);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 9, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        frqFrame = new QFrame(DeviceForm);
        frqFrame->setObjectName(QStringLiteral("frqFrame"));
        frqFrame->setFrameShape(QFrame::StyledPanel);
        frqFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frqFrame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        freqSpinBox = new QDoubleSpinBox(frqFrame);
        freqSpinBox->setObjectName(QStringLiteral("freqSpinBox"));
        QFont font;
        font.setPointSize(16);
        freqSpinBox->setFont(font);
        freqSpinBox->setAlignment(Qt::AlignCenter);
        freqSpinBox->setMinimum(76);
        freqSpinBox->setMaximum(108);
        freqSpinBox->setSingleStep(0.05);
        freqSpinBox->setValue(93.7);

        verticalLayout->addWidget(freqSpinBox);

        freqSlider = new QSlider(frqFrame);
        freqSlider->setObjectName(QStringLiteral("freqSlider"));
        freqSlider->setMinimum(760);
        freqSlider->setMaximum(1080);
        freqSlider->setValue(937);
        freqSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(freqSlider);


        horizontalLayout_2->addWidget(frqFrame);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        buttosWidget = new QWidget(DeviceForm);
        buttosWidget->setObjectName(QStringLiteral("buttosWidget"));
        horizontalLayout = new QHBoxLayout(buttosWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 4, -1, -1);
        seekBackButton = new QPushButton(buttosWidget);
        seekBackButton->setObjectName(QStringLiteral("seekBackButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(seekBackButton->sizePolicy().hasHeightForWidth());
        seekBackButton->setSizePolicy(sizePolicy);
        seekBackButton->setMinimumSize(QSize(60, 60));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/icons/media-seek-backward.svg"), QSize(), QIcon::Normal, QIcon::Off);
        seekBackButton->setIcon(icon);
        seekBackButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(seekBackButton);

        playButton = new QPushButton(buttosWidget);
        playButton->setObjectName(QStringLiteral("playButton"));
        sizePolicy.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy);
        playButton->setMinimumSize(QSize(60, 60));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/icons/media-playback-start.svg"), QSize(), QIcon::Normal, QIcon::Off);
        playButton->setIcon(icon1);
        playButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(playButton);

        seekForwardButton = new QPushButton(buttosWidget);
        seekForwardButton->setObjectName(QStringLiteral("seekForwardButton"));
        sizePolicy.setHeightForWidth(seekForwardButton->sizePolicy().hasHeightForWidth());
        seekForwardButton->setSizePolicy(sizePolicy);
        seekForwardButton->setMinimumSize(QSize(60, 60));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/buttons/icons/media-seek-forward.svg"), QSize(), QIcon::Normal, QIcon::Off);
        seekForwardButton->setIcon(icon2);
        seekForwardButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(seekForwardButton);


        horizontalLayout_2->addWidget(buttosWidget);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        rssiLabel = new QLabel(DeviceForm);
        rssiLabel->setObjectName(QStringLiteral("rssiLabel"));

        horizontalLayout_3->addWidget(rssiLabel);

        snrLabel = new QLabel(DeviceForm);
        snrLabel->setObjectName(QStringLiteral("snrLabel"));

        horizontalLayout_3->addWidget(snrLabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_3);

        stationsFrame = new QFrame(DeviceForm);
        stationsFrame->setObjectName(QStringLiteral("stationsFrame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stationsFrame->sizePolicy().hasHeightForWidth());
        stationsFrame->setSizePolicy(sizePolicy1);
        stationsFrame->setFrameShape(QFrame::StyledPanel);
        stationsFrame->setFrameShadow(QFrame::Raised);
        stationsFrame->setLineWidth(2);
        stationsFrame->setMidLineWidth(1);
        horizontalLayout_4 = new QHBoxLayout(stationsFrame);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        stationsTable = new QTableWidget(stationsFrame);
        if (stationsTable->columnCount() < 3)
            stationsTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        stationsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        stationsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        stationsTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        stationsTable->setObjectName(QStringLiteral("stationsTable"));
        stationsTable->setColumnCount(3);

        horizontalLayout_4->addWidget(stationsTable);


        verticalLayout_2->addWidget(stationsFrame);


        retranslateUi(DeviceForm);
        QObject::connect(seekBackButton, SIGNAL(clicked()), DeviceForm, SLOT(seek_back_A()));
        QObject::connect(seekForwardButton, SIGNAL(clicked()), DeviceForm, SLOT(seek_forward_A()));
        QObject::connect(freqSpinBox, SIGNAL(valueChanged(double)), DeviceForm, SLOT(tune_A(double)));
        QObject::connect(freqSpinBox, SIGNAL(valueChanged(double)), DeviceForm, SLOT(freq_changed(double)));
        QObject::connect(freqSlider, SIGNAL(valueChanged(int)), DeviceForm, SLOT(slider_moved(int)));

        QMetaObject::connectSlotsByName(DeviceForm);
    } // setupUi

    void retranslateUi(QWidget *DeviceForm)
    {
        DeviceForm->setWindowTitle(QApplication::translate("DeviceForm", "Form", 0));
        freqSpinBox->setSuffix(QApplication::translate("DeviceForm", "MHz", 0));
        seekBackButton->setText(QString());
        playButton->setText(QString());
        seekForwardButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        rssiLabel->setToolTip(QApplication::translate("DeviceForm", "Received signal strength indicator, higher is better.", 0));
#endif // QT_NO_TOOLTIP
        rssiLabel->setText(QApplication::translate("DeviceForm", "RSSI: ?dB\316\274V", 0));
#ifndef QT_NO_TOOLTIP
        snrLabel->setToolTip(QApplication::translate("DeviceForm", "Signal to noise ration, higher is better.", 0));
#endif // QT_NO_TOOLTIP
        snrLabel->setText(QApplication::translate("DeviceForm", "SNR: ?dB", 0));
        QTableWidgetItem *___qtablewidgetitem = stationsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DeviceForm", "Frequency", 0));
        QTableWidgetItem *___qtablewidgetitem1 = stationsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DeviceForm", "RSSI", 0));
        QTableWidgetItem *___qtablewidgetitem2 = stationsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("DeviceForm", "SNR", 0));
    } // retranslateUi

};

namespace Ui {
    class DeviceForm: public Ui_DeviceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEFORM_H
