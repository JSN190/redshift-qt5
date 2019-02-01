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
    // status indicates whether the service is runn
    void service_status_received_startstop(bool status);
    void service_status_received_enabledisable(bool status);
    // status indicates whether the start/stop attempt was successful
    void service_start_feedback(bool status);
    void service_stop_feedback(bool status);
    void service_enable_feedback(bool status);
    void service_disable_feedback(bool status);

    void on_buttonServiceEnableDisable_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
