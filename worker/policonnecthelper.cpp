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

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

PoliconnectHelper::PoliconnectHelper(QObject *parent)
        : QObject(parent)
{
    qDebug() << "Creating Helper";
    (void) new PoliconnecthelperAdaptor(this);
    if (!QDBusConnection::systemBus().registerService("it.polimi.policonnecthelper")) {
        qDebug() << "another helper is already running";
        QTimer::singleShot(0, this, SLOT(quit()));
        return;
    }

    if (!QDBusConnection::systemBus().registerObject("/Helper", this)) {
        qDebug() << "unable to register service interface to dbus";
        QTimer::singleShot(0, this, SLOT(quit()));
        return;
    }
    // Normally you will set a timeout so your application can
    // free some resources of the poor client machine ;)
    QTimer::singleShot(60000, QCoreApplication::instance(), SLOT(quit()));
}

PoliconnectHelper::~PoliconnectHelper()
{
}

void PoliconnectHelper::generateConfiguration(const QString &p12, bool generate, const QString &p12Pass,
                                              const QString &asi, int matricola, const QString &password)
{
}
