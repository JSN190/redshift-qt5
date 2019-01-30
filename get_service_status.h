#ifndef GET_SERVICE_STATUS_H
#define GET_SERVICE_STATUS_H
#include <QObject>
#include <QThread>

class get_service_status : public QObject
{
    Q_OBJECT

public:
    get_service_status();
    void run();

public slots:
    void run_get_status();
    //void run_start_service();
    //void run_stop_service();

signals:
    void service_status_received(bool status);
    void finished();

private:
    bool status;
    bool get_systemd_status();
    bool get_homebrew_status();
    bool get_windows_status();
};

#endif
