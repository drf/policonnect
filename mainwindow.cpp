#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <PolicyKit/polkit-qt/ActionButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the button for polkitqt
    m_actionButton = new PolkitQt::ActionButton(ui->generateButton, "it.polimi.policonnect.GenerateConfiguration", this);

    connect(ui->browseAsiButton, SIGNAL(clicked()), this, SLOT(browseForAsi()));
    connect(ui->browseAsiButton, SIGNAL(clicked()), this, SLOT(browseForP12()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::browseForAsi()
{
    QString fname = QFileDialog::getOpenFileName(this, "Seleziona asi.cer", QString(),
                                                 "Certificato OpenSSL (asi.cer)");
    if (!fname.isEmpty()) {
        ui->locateAsiEdit->setText(fname);
    }
}

void MainWindow::browseForP12()
{
    QString fname = QFileDialog::getOpenFileName(this, "Seleziona CertificatoASI.p12", QString(),
                                                 "Certificato ASI (CertificatoASI.p12)");
    if (!fname.isEmpty()) {
        ui->p12LocateEdit->setText(fname);
    }
}
