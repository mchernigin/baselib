#include <baselib/logger/prelude.h>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    auto loggerManager = base::logger::LoggerManager::globalInstance();

    loggerManager->addLogger<base::logger::ConsoleLogger>(QtDebugMsg);
    loggerManager->addLogger<base::logger::FileLogger>(QtWarningMsg, "appname", "appname.log");
    loggerManager->addLogger<base::logger::SyslogLogger>(LOG_LEVEL_DISABLED, "appname");

    qDebug() << "Hello?";
    qInfo() << "Hello?";
    qWarning() << "Hello?";
    qCritical() << "Hello?";

    return 0;
}
