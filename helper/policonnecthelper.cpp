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

#include <PolkitQt1/Authority>

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

    PolkitQt1::Authority::Result result;
    PolkitQt1::SystemBusNameSubject *subject;

    subject = new PolkitQt1::SystemBusNameSubject(message().service());

    result = PolkitQt1::Authority::instance()->checkAuthorizationSync("it.polimi.policonnect.generateconfiguration",
                                                                      subject , PolkitQt1::Authority::AllowUserInteraction);

    if (result != PolkitQt1::Authority::Yes) {
        // We were not authorized. Let's quit out and stream the error
        qDebug() << "No auth";
        emit operationResult(false, (int)NotAuthorized);
        QCoreApplication::instance()->quit();
        return;
    }

    const QString path = "/usr/share/policonnect";

    // Let's start by creating our /usr/share/policonnect dir
    QDir().mkpath(path);

    QFile::remove(path + QString("/CertificatoASI%1.p12").arg(matricola));

    // Now copy over the certificate
    if (!QFile::copy(p12, path + QString("/CertificatoASI%1.p12").arg(matricola))) {
        // Generating ASI failed. Let's quit out and stream the error
        emit operationResult(false, (int)FileCopyFail);
        QCoreApplication::instance()->quit();
        return;
    }

    // Check it: do we need to generate asi.cer?
    if (generate) {
        QString cmd = QString("openssl pkcs12 -cacerts -in %1 -out %2/asi%3.cer -passin pass:%4 -passout pass:%4")
                             .arg(p12).arg(path).arg(matricola).arg(p12Pass);
        if (QProcess::execute(cmd) != 0) {
            // Generating ASI failed. Let's quit out and stream the error
            emit operationResult(false, (int)GenerateASIFail);
            QCoreApplication::instance()->quit();
            return;
        }
    } else {
        // Otherwise, copy over the given asi file
        if (!QFile::copy(asi, path + QString("/asi%1.cer").arg(matricola))) {
            // Generating ASI failed. Let's quit out and stream the error
            emit operationResult(false, (int)FileCopyFail);
            QCoreApplication::instance()->quit();
            return;
        }
    }

    // Ok, let's generate the real configuration file now
    QString conf = QString("name = Polimi-internet-%1\n"
                           "author = Dario Freddi\n"
                           "version = 1\n"
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
                           "ca_cert=\"%2/asi%1.cer\"\n"
                           "private_key=\"%2/CertificatoASI%1.p12\"\n"
                           "private_key_passwd=\"$_PASSWORD\"\n"
                           "phase2=\"auth=MSCHAPV2\"\n"
                           "}\n").arg(matricola).arg(path);

    // Ok, now let's save it
    QFile::remove(QString("/etc/wicd/encryption/templates/polimi-internet-%1").arg(matricola));
    QFile tmpl(QString("/etc/wicd/encryption/templates/polimi-internet-%1").arg(matricola));
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

    if (!QString(active.readAll()).contains(QString("polimi-internet-%1").arg(matricola))) {
        active.close();
        if (!active.open(QIODevice::Append | QIODevice::Text)) {
            // Generating ASI failed. Let's quit out and stream the error
            emit operationResult(false, (int)ModifyActiveFail);
            QCoreApplication::instance()->quit();
            return;
        }
        QTextStream acout(&active);
        acout << QString("polimi-internet-%1").arg(matricola) << "\n";
        acout.flush();
    }

    active.close();

    // That's it!
    emit operationResult(true);
    QCoreApplication::instance()->quit();

}
