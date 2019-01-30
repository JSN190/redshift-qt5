#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonServiceStartStop_clicked();
    void service_status_received(bool status);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
