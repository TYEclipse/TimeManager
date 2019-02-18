#ifndef EVENTLOG_H
#define EVENTLOG_H

#include <QObject>
#include <QFile>
#include <QList>

class EventLog
{

public:
    EventLog(const QString & logname);
    ~EventLog();

    void ReadLog();
    void WriteLog();

    QList<QString> Dates;
    QList<QString> Events;

private:
    QFile * logFile;

};

#endif // EVENTLOG_H
