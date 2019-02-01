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
    void run_start_service();
    void run_stop_service();
    void run_enable_service();
    void run_disable_service();

signals:
    // status indicates whether the service is running or not
    void service_status_received(bool status);
    // status indicates whether the start/stop attempt was successful
    void service_start(bool status);
    void service_stop(bool status);
    void service_enable(bool status);
    void service_disable(bool status);
    void finished();

private:
    bool status;
    bool get_systemd_status();
    bool get_homebrew_status();
    bool get_windows_status();
    bool start_systemd_service();
    bool start_homebrew_service();
    bool start_windows_service();
    bool stop_systemd_service();
    bool stop_homebrew_service();
    bool stop_windows_service();
    bool enable_systemd_service();
    bool enable_homebrew_service();
    bool enable_windows_service();
    bool disable_systemd_service();
    bool disable_homebrew_service();
    bool disable_windows_service();
};

#endif
