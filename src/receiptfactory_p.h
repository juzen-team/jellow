/****************************************************************************
**
** Jreen
**
** Copyright © 2011 Aleksey Sidorov <gorthauer87@yandex.ru>
**
*****************************************************************************
**
** $JREEN_BEGIN_LICENSE$
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see http://www.gnu.org/licenses/.
** $JREEN_END_LICENSE$
**
****************************************************************************/
#ifndef JREEN_RECEIPTFACTORY_P_H
#define JREEN_RECEIPTFACTORY_P_H
#include "receipt.h"

namespace Jreen {

class JREEN_AUTOTEST_EXPORT ReceiptFactoryPrivate;
class JREEN_AUTOTEST_EXPORT ReceiptFactory : public PayloadFactory<Receipt>
{
	Q_DECLARE_PRIVATE(ReceiptFactory)
public:
	ReceiptFactory();
	virtual ~ReceiptFactory();
	QStringList features() const;
	bool canParse(const QStringRef &name, const QStringRef &uri, const QXmlStreamAttributes &attributes);
	void handleStartElement(const QStringRef &name, const QStringRef &uri, const QXmlStreamAttributes &attributes);
	void handleEndElement(const QStringRef &name, const QStringRef &uri);
	void handleCharacterData(const QStringRef &text);
	void serialize(Payload *extension, QXmlStreamWriter *writer);
	Payload::Ptr createPayload();
private:
	QScopedPointer<ReceiptFactoryPrivate> d_ptr;
};

} // namespace Jreen

#endif // JREEN_RECEIPTFACTORY_P_H
