#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "get_service_status.h"
#include <QMessageBox>
#include <stdio.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonServiceStartStop_clicked()
{
    QThread* thread = new QThread();
    get_service_status* worker = new get_service_status();
    worker->moveToThread(thread);
    connect(worker, SIGNAL(service_status_received(bool)), this, SLOT(service_status_received(bool)));
    connect(thread, SIGNAL(started()), worker, SLOT(run_get_status()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
    ui->buttonServiceStartStop->setEnabled(false);
}

void MainWindow::service_status_received(bool running)
{
    QThread* thread = new QThread();
    get_service_status* worker = new get_service_status();
    worker->moveToThread(thread);
    if (running) {
        connect(worker, SIGNAL(service_stop(bool)), this, SLOT(service_stop_feedback(bool)));
        connect(thread, SIGNAL(started()), worker, SLOT(run_stop_service()));
    } else {
        connect(worker, SIGNAL(service_start(bool)), this, SLOT(service_start_feedback(bool)));
        connect(thread, SIGNAL(started()), worker, SLOT(run_start_service()));
    }
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void MainWindow::service_start_feedback(bool success) {
    if (success) {
        ui->buttonServiceStartStop->setText("Stop");
    }
    ui->buttonServiceStartStop->setEnabled(true);
}

void MainWindow::service_stop_feedback(bool success) {
    if (success) {
        ui->buttonServiceStartStop->setText("Start");
    }
    ui->buttonServiceStartStop->setEnabled(true);
}
