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

#ifndef POLICONNECTHELPER_H
#define POLICONNECTHELPER_H

#include <QObject>
#include <QtDBus/QDBusContext>

class PoliconnectHelper : public QObject, protected QDBusContext
{
    Q_OBJECT

public:

    enum Error {
        NoError = 0,
        NotAuthorized = 1,
        GenerateASIFail = 2,
        FileCopyFail = 4,
        GenerateTemplateFail = 8,
        ModifyActiveFail = 16
    };

    PoliconnectHelper(QObject *parent = 0);
    virtual ~PoliconnectHelper();

public Q_SLOTS:
    void generateConfiguration(const QString &p12, bool generate, const QString &p12Pass,
                               const QString &asi, int matricola);

Q_SIGNALS:
    void operationResult(bool success, int error = 0);
};

#endif // POLICONNECTHELPER_H
