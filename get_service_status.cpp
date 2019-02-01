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

void get_service_status::run_start_service() {
#ifdef Q_OS_LINUX
    status = start_systemd_service();
#elif defined(Q_OS_DARWIN)
    status = start_homebrew_service();
#elif defined(Q_OS_MSDOS)
    status = start_windows_service();
#endif
    emit service_start(status);
    emit finished();
}

void get_service_status::run_stop_service() {
#ifdef Q_OS_LINUX
    status = stop_systemd_service();
#elif defined(Q_OS_DARWIN)
    status = stop_homebrew_service();
#elif defined(Q_OS_MSDOS)
    status = stop_windows_service();
#endif
    emit service_stop(status);
    emit finished();
}

bool get_service_status::get_systemd_status() {
    std::string cmd = "systemctl --user status redshift";
    int cmdExec = system(cmd.c_str());
    int exitCode = WEXITSTATUS(cmdExec);
    return exitCode == 0;
}

bool get_service_status::get_homebrew_status() {
    std::string cmd = "/usr/local/bin/brew services list | "
                      "grep 'redshift       started'";
    int cmdExec = system(cmd.c_str());
    int exitCode = WEXITSTATUS(cmdExec);
    return exitCode == 0;
}

bool get_service_status::get_windows_status() {
    return false;
}

bool get_service_status::start_systemd_service() {
    return false;
}

bool get_service_status::start_homebrew_service() {
    std::string cmd = "/usr/local/bin/brew services run redshift | "
                      "grep '==> Successfully ran `redshift` (label: homebrew.mxcl.redshift)'";
    int cmdExec = system(cmd.c_str());
    int exitCode = WEXITSTATUS(cmdExec);
    return exitCode == 0;
}

bool get_service_status::start_windows_service() {
    return false;
}

bool get_service_status::stop_homebrew_service() {
    std::string cmd = "/usr/local/bin/brew services stop redshift | "
                      "grep 'Stopping `redshift`... (might take a while)'";
    int cmdExec = system(cmd.c_str());
    int exitCode = WEXITSTATUS(cmdExec);
    return exitCode == 0;
}


