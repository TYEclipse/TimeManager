#include "eventlog.h"
#include <QTextStream>
#include <QDebug>
EventLog::EventLog(const QString & logname)
{
    logFile = new QFile(logname);
}

EventLog::~EventLog()
{
    delete logFile;
}

void EventLog::ReadLog()
{
    logFile->open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(logFile);
    QString line = in.readLine();
    int indexSpace;
    while (!line.isNull()) {
        indexSpace = line.indexOf(" ");
        QString date = line.left(indexSpace);
        QString event = line.right(line.length()-indexSpace-1);
        Dates.append(date);
        Events.append(event);
        line = in.readLine();
    }
    logFile->close();
}

void EventLog::WriteLog()
{
    if (!logFile->open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(logFile);
    for (int i=0;i<Dates.length();i++) {
        out <<Dates[i]<<" "<<Events[i]<< "\n";
    }

    logFile->close();
}
