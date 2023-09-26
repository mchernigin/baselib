/***********************************************************************************************************************
**
** Copyright (C) 2022 BaseALT Ltd. <org@basealt.ru>
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**
***********************************************************************************************************************/

#ifndef QBASE_LOGGER_MANAGER_H
#define QBASE_LOGGER_MANAGER_H

#include "../base.h"
#include "logger.h"

#include <memory>
#include <mutex>
#include <vector>

#include <QString>

namespace qbase
{
namespace logger
{
class LoggerManagerPrivate;

class QBASE_CORE_EXPORT LoggerManager
{
public:
    static LoggerManager *globalInstance();
    static void destroyInstance();

    LoggerManager();
    ~LoggerManager();

    void addLogger(std::shared_ptr<Logger> logger);
    void removeLogger(std::shared_ptr<Logger> logger);
    void clearLoggers();
    size_t getLoggerCount() const;

    void log(const QtMsgType &msgType,
             const std::string &message,
             const std::string &file,
             const std::string &function,
             const uint32_t line);

    template <typename T, typename... Args>
    void addLogger(const QtMsgType &level, Args... args)
    {
        auto logger = std::make_shared<T>(args...);
        logger->setLogLevel(level);
        this->addLogger(logger);
    }

public:
    LoggerManager(const LoggerManager &) = delete;            // copy ctor
    LoggerManager(LoggerManager &&)      = delete;            // move ctor
    LoggerManager &operator=(const LoggerManager &) = delete; // copy assignment
    LoggerManager &operator=(LoggerManager &&) = delete;      // move assignment

private:
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    static std::shared_ptr<LoggerManager> instance;
    LoggerManagerPrivate *d;
};
} // namespace logger
} // namespace qbase

#endif // QBASE_LOGGER_MANAGER_H
