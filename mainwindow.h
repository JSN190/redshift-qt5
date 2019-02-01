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
    // status indicates whether the service is running
    void service_status_received(bool status);
    // status indicates whether the start/stop attempt was successful
    void service_start_feedback(bool status);
    void service_stop_feedback(bool status);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
