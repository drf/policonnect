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

#include "policonnecthelper.h"

#include "policonnecthelperadaptor.h"

#include <PolicyKit/polkit-qt/Auth>

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <QProcess>
#include <QDir>
#include <QFile>

PoliconnectHelper::PoliconnectHelper(QObject *parent)
        : QObject(parent)
{
    qDebug() << "Creating Helper";
    (void) new PoliconnecthelperAdaptor(this);
    if (!QDBusConnection::systemBus().registerService("it.polimi.policonnecthelper")) {
        qDebug() << "another helper is already running";
        QTimer::singleShot(0, QCoreApplication::instance(), SLOT(quit()));
        return;
    }

    if (!QDBusConnection::systemBus().registerObject("/Helper", this)) {
        qDebug() << "unable to register service interface to dbus";
        QTimer::singleShot(0, QCoreApplication::instance(), SLOT(quit()));
        return;
    }

    QTimer::singleShot(60000, QCoreApplication::instance(), SLOT(quit()));
}

PoliconnectHelper::~PoliconnectHelper()
{
}

void PoliconnectHelper::generateConfiguration(const QString &p12, bool generate, const QString &p12Pass,
                                              const QString &asi, int matricola)
{
    qDebug() << "Generating conf";

    PolkitQt::Auth::Result result;
    result = PolkitQt::Auth::isCallerAuthorized("it.polimi.policonnect.generateconfiguration",
                                                message().service(),
                                                true);
    if (result != PolkitQt::Auth::Yes) {
        // We were not authorized. Let's quit out and stream the error
        qDebug() << "No auth";
        emit operationResult(false, (int)NotAuthorized);
        QCoreApplication::instance()->quit();
        return;
    }

    const QString path = "/usr/share/policonnect";

    // Let's start by creating our /usr/share/policonnect dir
    QDir().mkpath(path);

    qDebug() << p12 << path + "/CertificatoASI.p12";
    QFile::remove(path + "/CertificatoASI.p12");

    // Now copy over the certificate
    if (!QFile::copy(p12, path + "/CertificatoASI.p12")) {
        // Generating ASI failed. Let's quit out and stream the error
        emit operationResult(false, (int)FileCopyFail);
        QCoreApplication::instance()->quit();
        return;
    }

    qDebug() << generate;

    // Check it: do we need to generate asi.cer?
    if (generate) {
        QString cmd = QString("openssl pkcs12 -cacerts -in %1 -out %2/asi.cer -passin pass:%3 -passout pass:%3")
                             .arg(p12).arg(path).arg(p12Pass);
        if (QProcess::execute(cmd) != 0) {
            // Generating ASI failed. Let's quit out and stream the error
            emit operationResult(false, (int)GenerateASIFail);
            QCoreApplication::instance()->quit();
            return;
        }
    } else {
        // Otherwise, copy over the given asi file
        if (!QFile::copy(asi, path + "/asi.cer")) {
            // Generating ASI failed. Let's quit out and stream the error
            emit operationResult(false, (int)FileCopyFail);
            QCoreApplication::instance()->quit();
            return;
        }
    }

    // Ok, let's generate the real configuration file now
    QString conf = QString("name = Polimi-internet\n"
                           "author = Sante Gennaro Rotondi - Dario Freddi\n"
                           "version = 2\n"
                           "require password *Password_del_certificato\n"
                           "----\n"
                           "ctrl_interface=/var/run/wpa_supplicant\n"
                           "ctrl_interface_group=0\n"
                           "network={\n"
                           "ssid=\"internet\"\n"
                           "proto=WPA\n"
                           "key_mgmt=WPA-EAP\n"
                           "auth_alg=OPEN\n"
                           "pairwise=TKIP\n"
                           "eap=TLS\n"
                           "anonymous_identity=\"S%1\"\n"
                           "ca_cert=\"%2/asi.cer\"\n"
                           "private_key=\"%2/CertificatoASI.p12\"\n"
                           "private_key_passwd=\"%3\"\n"
                           "phase2=\"auth=MSCHAPV2\"\n"
                           "}\n").arg(matricola).arg(path).arg(p12Pass);

    // Ok, now let's save it
    QFile::remove("/etc/wicd/encryption/templates/polimi-internet");
    QFile tmpl("/etc/wicd/encryption/templates/polimi-internet");
    if (!tmpl.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Generating ASI failed. Let's quit out and stream the error
        emit operationResult(false, (int)GenerateTemplateFail);
        QCoreApplication::instance()->quit();
        return;
    }

    QTextStream tmplout(&tmpl);
    tmplout << conf;
    tmplout.flush();
    tmpl.close();

    QFile active("/etc/wicd/encryption/templates/active");
    if (!active.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Generating ASI failed. Let's quit out and stream the error
        emit operationResult(false, (int)ModifyActiveFail);
        QCoreApplication::instance()->quit();
        return;
    }

    if (!active.readAll().contains("polimi-internet")) {
        active.close();
        if (!active.open(QIODevice::Append | QIODevice::Text)) {
            // Generating ASI failed. Let's quit out and stream the error
            emit operationResult(false, (int)ModifyActiveFail);
            QCoreApplication::instance()->quit();
            return;
        }
        QTextStream acout(&active);
        acout << "polimi-internet\n";
        acout.flush();
    }

    active.close();

    // That's it!
    emit operationResult(true);
    QCoreApplication::instance()->quit();

}
