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

#include <QtGui/QApplication>
#include <QProcess>
#include <QMessageBox>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("Policonnect");
    QCoreApplication::setApplicationVersion("0.1.0");
    QCoreApplication::setOrganizationDomain("www.asi.polimi.it");
    QCoreApplication::setOrganizationName("Area sistemi informatici Politecnico di Milano");
    QApplication::setWindowIcon(QIcon(":/Icons/icons/polimi.png"));

    // Startup checks...
    if (QProcess::execute("which wicd") != 0 && QProcess::execute("which wicd-client") != 0) {
        QMessageBox::warning(0, "Errore", QString::fromUtf8("Sembra che tu non abbia installato wicd. "
                                          "Policonnect è un'applicazione che genera template di connessione "
                                          "per wicd, di conseguenza è necessario installarlo per poter "
                                          "utilizzare Policonnect. Installa wicd e riavvia questa applicazione"));
        QCoreApplication::exit(1);
    }

    if (QProcess::execute("which openssl") != 0) {
        QMessageBox::warning(0, "Errore", QString::fromUtf8("Sembra che tu non abbia installato openssl. "
                                          "Openssl è necessario per generare il tuo certificato. "
                                          "Se possiedi già un file asi.cer, puoi ignorare questo messaggio, "
                                          "in caso contrario, installa openssl e riavvia Policonnect."));
    }

    MainWindow w;
    w.show();
    return a.exec();
}
