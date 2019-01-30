#include "get_service_status.h"
#include <QDebug>

get_service_status::get_service_status()
{
}

void get_service_status::run_get_status()
{
#ifdef Q_OS_LINUX
    status = get_systemd_status();
#elif defined(Q_OS_DARWIN)
    status = get_homebrew_status();
#elif defined(Q_OS_MSDOS)
    status = get_windows_status();
#endif
    emit service_status_received(status);
    emit finished();
}

bool get_service_status::get_systemd_status() {
    std::string cmd = "systemctl --user status redshift";
    int exitCode = WEXITSTATUS(system(cmd.c_str()));
    return exitCode == 0;
}

bool get_service_status::get_homebrew_status() {
    return false;
}

bool get_service_status::get_windows_status() {
    return false;
}


