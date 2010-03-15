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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QPointer>

namespace Ui
{
    class MainWindow;
}

namespace PolkitQt1
{
namespace Gui {
    class ActionButton;
}
}

class QProgressDialog;

class MainWindow : public QMainWindow
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

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void browseForAsi();
    void browseForP12();
    void generateConfiguration();
    void checkFields();
    void operationResult(bool success, int err);

private:
    Ui::MainWindow *ui;
    PolkitQt1::Gui::ActionButton *m_actionButton;
    QPointer<QProgressDialog> m_progressDialog;
};

#endif // MAINWINDOW_H
