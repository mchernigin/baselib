#include <qbase/logger/prelude.h>
#include <QCoreApplication>
#include <QDebug>

int main()
{
    auto loggerManager = qbase::logger::LoggerManager::globalInstance();

    loggerManager->addLogger<qbase::logger::ConsoleLogger>(QtDebugMsg);
    loggerManager->addLogger<qbase::logger::FileLogger>(QtWarningMsg, "appname", "appname.log");
    loggerManager->addLogger<qbase::logger::SyslogLogger>(LOG_LEVEL_DISABLED, "appname");

    qDebug() << "Hello?";
    qInfo() << "Hello?";
    qWarning() << "Hello?";
    qCritical() << "Hello?";

    return 0;
}
