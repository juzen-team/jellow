/****************************************************************************
**
** Jreen
**
** Copyright © 2011 Ruslan Nigmatullin <euroelessar@yandex.ru>
**
*****************************************************************************
**
** $JREEN_BEGIN_LICENSE$
** Jreen is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Jreen is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Jreen.  If not, see <http://www.gnu.org/licenses/>.
** $JREEN_END_LICENSE$
**
****************************************************************************/

#ifndef JREEN_TCPCONNECTION_H
#define JREEN_TCPCONNECTION_H

#include "directconnection.h"

namespace Jreen
{

class JREEN_EXPORT TcpConnection : public DirectConnection
{
	Q_OBJECT
public:
	TcpConnection(const QString &host_name, qint16 port = -1);
	TcpConnection(const QHostAddress &address, qint16 port);
};

}

#endif // JREEN_TCPCONNECTION_H
