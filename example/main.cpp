#include <baselib/logger/prelude.h>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    auto loggerManager = base::logger::LoggerManager::globalInstance();

    loggerManager->addLogger<base::logger::ConsoleLogger>(QtDebugMsg);
    loggerManager->addLogger<base::logger::FileLogger>(QtWarningMsg);
    loggerManager->addLogger<base::logger::SyslogLogger>(LOG_LEVEL_DISABLED);

    qWarning() << "Hello?";

    return 0;
}
