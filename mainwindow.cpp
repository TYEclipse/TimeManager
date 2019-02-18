#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDateTime>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString logName="EventLog.txt";
    eventLog = new EventLog(logName);

    eventLog->ReadLog();

    for(int i=0;i<eventLog->Dates.length();i++)
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(eventLog->Dates[i]));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(eventLog->Events[i]));
    }
}

MainWindow::~MainWindow()
{
    eventLog->WriteLog();
    delete ui;
    delete eventLog;
}


void MainWindow::on_pushButton_clicked()
{
    eventLog->Dates.append(QDateTime::currentDateTime().toString("yyyy/MM/dd_hh:mm:ss"));
    eventLog->Events.append(ui->lineEdit->text()+" ");
    int i=eventLog->Dates.length()-1;
    ui->tableWidget->insertRow(i);
    ui->tableWidget->setItem(i,0,new QTableWidgetItem(eventLog->Dates[i]));
    ui->tableWidget->setItem(i,1,new QTableWidgetItem(eventLog->Events[i]));
}
