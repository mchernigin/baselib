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

#include "loggermessage.h"

#include <iomanip>

namespace base
{
namespace logger
{
LoggerMessage::LoggerMessage(const QtMsgType &msgType_,
                             std::string message_,
                             std::string filePath_,
                             std::string functionName_,
                             const uint32_t line_,
                             const std::tm &time_,
                             const std::thread::id &threadId_)
    : msgType(msgType_)
    , message(std::move(message_))
    , filePath(std::move(filePath_))
    , functionName(std::move(functionName_))
    , line(line_)
    , time(time_)
    , threadId(threadId_)
{}

std::string LoggerMessage::getTimeFormatted(const char *format) const
{
    std::stringstream buffer;
    buffer << std::put_time(&this->time, format);

    return buffer.str();
}
} // namespace logger
} // namespace base

