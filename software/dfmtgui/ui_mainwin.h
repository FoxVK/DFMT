/********************************************************************************
** Form generated from reading UI file 'mainwin.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIN_H
#define UI_MAINWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWin
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QTabWidget *Tabs;
    QMenuBar *menuBar;
    QMenu *menuAbout;

    void setupUi(QMainWindow *MainWin)
    {
        if (MainWin->objectName().isEmpty())
            MainWin->setObjectName(QStringLiteral("MainWin"));
        MainWin->resize(273, 129);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icons/radio.svg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWin->setWindowIcon(icon);
        centralWidget = new QWidget(MainWin);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        Tabs = new QTabWidget(centralWidget);
        Tabs->setObjectName(QStringLiteral("Tabs"));

        verticalLayout->addWidget(Tabs);

        MainWin->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWin);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 273, 27));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        MainWin->setMenuBar(menuBar);

        menuBar->addAction(menuAbout->menuAction());

        retranslateUi(MainWin);

        QMetaObject::connectSlotsByName(MainWin);
    } // setupUi

    void retranslateUi(QMainWindow *MainWin)
    {
        MainWin->setWindowTitle(QApplication::translate("MainWin", "Dual FM tuner", 0));
        menuAbout->setTitle(QApplication::translate("MainWin", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWin: public Ui_MainWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_H
