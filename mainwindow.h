#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

namespace Ui
{
    class MainWindow;
}

namespace PolkitQt
{
    class ActionButton;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void browseForAsi();
    void browseForP12();

private:
    Ui::MainWindow *ui;
    PolkitQt::ActionButton *m_actionButton;
};

#endif // MAINWINDOW_H
