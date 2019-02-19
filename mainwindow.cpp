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

    for(int i=0;i<eventLog->EventList.length();i++)
    {
        ui->comboBox->addItem(eventLog->EventList[i]);
    }
    ui->pushButton->setFocus();//设置默认焦点
    ui->pushButton->setShortcut(QKeySequence::InsertParagraphSeparator);//设置快捷键为键盘的“回车”键
    ui->pushButton->setShortcut(Qt::Key_Enter);//设置快捷键为enter键
    ui->pushButton->setShortcut(Qt::Key_Return);//设置快捷为小键盘上的enter键
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
    eventLog->Events.append(ui->comboBox->currentText());
    int i=eventLog->Dates.length()-1;
    ui->tableWidget->insertRow(i);
    ui->tableWidget->setItem(i,0,new QTableWidgetItem(eventLog->Dates[i]));
    ui->tableWidget->setItem(i,1,new QTableWidgetItem(eventLog->Events[i]));
    if(eventLog->EventList.indexOf(eventLog->Events[i])<0)
    {
        eventLog->EventList.append(eventLog->Events[i]);
        ui->comboBox->addItem(eventLog->Events[i]);
    }
}
