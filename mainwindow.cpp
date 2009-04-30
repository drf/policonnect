/***************************************************************************
 *   Copyright (C) 2009 by Dario Freddi                                    *
 *   drf54321@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <PolicyKit/polkit-qt/ActionButton>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the button for polkitqt
    m_actionButton = new PolkitQt::ActionButton(ui->generateButton, "it.polimi.policonnect.GenerateConfiguration", this);
    m_actionButton->setText("Genera Configurazione");
    m_actionButton->setEnabled(true);
    connect(m_actionButton, SIGNAL(clicked(QAbstractButton*)), this, SLOT(checkFields()));
    connect(m_actionButton, SIGNAL(activated()), this, SLOT(generateConfiguration()));

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

void MainWindow::checkFields()
{
    // Check for empty fields
    if (ui->p12LocateEdit->text().isEmpty() ||
        (ui->locateAsiRadio->isChecked() && ui->locateAsiEdit->text().isEmpty()) ||
        (ui->generateAsiRadio->isChecked() && ui->p12PasswordEdit->text().isEmpty()) ||
        ui->matricolaEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Errore", "Devi inserire tutti i campi");
        return;
    }

    // Check for field properties
    if (ui->matricolaEdit->text().length() != 6 ||
        ui->matricolaEdit->text().toInt() == 0) {
        QMessageBox::warning(this, "Errore", "La tua matricola sembra essere non valida");
        return;
    }

    // Everything seems fine, let's hit it
    m_actionButton->activate();
}

void MainWindow::generateConfiguration()
{
    // Stream it through the bus
    QDBusInterface iface("it.polimi.policonnectworker",
                         "/Worker",
                         "it.polimi.policonnectworker",
                         QDBusConnection::systemBus());
    iface.asyncCall("generateConfiguration", ui->p12LocateEdit->text(), ui->locateAsiRadio->isChecked(),
                    ui->p12PasswordEdit->text(), ui->locateAsiEdit->text(), ui->matricolaEdit->text());
}
