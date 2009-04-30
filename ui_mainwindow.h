/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Thu Apr 30 23:24:38 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFormLayout *formLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *p12LocateEdit;
    QPushButton *p12BrowseButton;
    QRadioButton *generateAsiButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *p12PasswordEdit;
    QRadioButton *locateAsiRadio;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *locateAsiEdit;
    QPushButton *browseAsiButton;
    QLabel *label_3;
    QLineEdit *matricolaEdit;
    QLabel *label_4;
    QLineEdit *matrPasswordEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *bottomHorizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(494, 315);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setScaledContents(true);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        p12LocateEdit = new QLineEdit(centralWidget);
        p12LocateEdit->setObjectName(QString::fromUtf8("p12LocateEdit"));

        horizontalLayout->addWidget(p12LocateEdit);

        p12BrowseButton = new QPushButton(centralWidget);
        p12BrowseButton->setObjectName(QString::fromUtf8("p12BrowseButton"));

        horizontalLayout->addWidget(p12BrowseButton);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout);

        generateAsiButton = new QRadioButton(centralWidget);
        generateAsiButton->setObjectName(QString::fromUtf8("generateAsiButton"));
        generateAsiButton->setChecked(true);

        formLayout->setWidget(1, QFormLayout::LabelRole, generateAsiButton);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_5);

        p12PasswordEdit = new QLineEdit(centralWidget);
        p12PasswordEdit->setObjectName(QString::fromUtf8("p12PasswordEdit"));
        p12PasswordEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout_3->addWidget(p12PasswordEdit);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_3);

        locateAsiRadio = new QRadioButton(centralWidget);
        locateAsiRadio->setObjectName(QString::fromUtf8("locateAsiRadio"));

        formLayout->setWidget(2, QFormLayout::LabelRole, locateAsiRadio);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        locateAsiEdit = new QLineEdit(centralWidget);
        locateAsiEdit->setObjectName(QString::fromUtf8("locateAsiEdit"));
        locateAsiEdit->setEnabled(false);

        horizontalLayout_2->addWidget(locateAsiEdit);

        browseAsiButton = new QPushButton(centralWidget);
        browseAsiButton->setObjectName(QString::fromUtf8("browseAsiButton"));
        browseAsiButton->setEnabled(false);

        horizontalLayout_2->addWidget(browseAsiButton);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_2);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        matricolaEdit = new QLineEdit(centralWidget);
        matricolaEdit->setObjectName(QString::fromUtf8("matricolaEdit"));
        matricolaEdit->setMaximumSize(QSize(150, 16777215));
        matricolaEdit->setMaxLength(6);

        formLayout->setWidget(3, QFormLayout::FieldRole, matricolaEdit);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        matrPasswordEdit = new QLineEdit(centralWidget);
        matrPasswordEdit->setObjectName(QString::fromUtf8("matrPasswordEdit"));
        matrPasswordEdit->setMaximumSize(QSize(150, 16777215));
        matrPasswordEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(4, QFormLayout::FieldRole, matrPasswordEdit);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        bottomHorizontalLayout = new QHBoxLayout();
        bottomHorizontalLayout->setSpacing(6);
        bottomHorizontalLayout->setObjectName(QString::fromUtf8("bottomHorizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        bottomHorizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(bottomHorizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);
        QObject::connect(generateAsiButton, SIGNAL(toggled(bool)), label_5, SLOT(setEnabled(bool)));
        QObject::connect(generateAsiButton, SIGNAL(toggled(bool)), p12PasswordEdit, SLOT(setEnabled(bool)));
        QObject::connect(locateAsiRadio, SIGNAL(toggled(bool)), locateAsiEdit, SLOT(setEnabled(bool)));
        QObject::connect(locateAsiRadio, SIGNAL(toggled(bool)), browseAsiButton, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Liberation Sans'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Benvenuto. Questa applicazione ti consentir\303\240 di impostare Wicd per la connessione alla rete interna al politecnico. Se non hai wicd, installalo prima di proseguire.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Tutto quello di cui hai bisogno \303\250 del file CertificatoASI.p12, se non lo hai ancora, <a href=\"http"
                        "s://www.asi.polimi.it/rete/wifi/richiesta_certificato.html\"><span style=\" text-decoration: underline; color:#0000ff;\">clicca qui</span></a> per ottenerne uno</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "CertificatoASI.p12", 0, QApplication::UnicodeUTF8));
        p12BrowseButton->setText(QApplication::translate("MainWindow", "PushButton", 0, QApplication::UnicodeUTF8));
        generateAsiButton->setText(QApplication::translate("MainWindow", "Genera asi.cer", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Password certificato:", 0, QApplication::UnicodeUTF8));
        locateAsiRadio->setText(QApplication::translate("MainWindow", "asi.cer", 0, QApplication::UnicodeUTF8));
        browseAsiButton->setText(QApplication::translate("MainWindow", "PushButton", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Matricola", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Password", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
