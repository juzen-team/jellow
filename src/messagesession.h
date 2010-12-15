/****************************************************************************
 *  messagesession.h
 *
 *  Copyright (c) 2009 by Nigmatullin Ruslan <euroelessar@gmail.com>
 *
 ***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************
*****************************************************************************/

#ifndef MESSAGESESSION_H
#define MESSAGESESSION_H

#include "message.h"
#include <QPointer>
#include <QHash>
#include <QVector>
#include <QMap>

namespace jreen
{

class MessageSession;
class MessageSessionManager;
class Client;

#define J_MESSAGE_FILTER \
	public: \
		static const jreen::MessageFilterMeta &meta() \
		{ \
			static jreen::MessageFilterMeta staticFilterMeta; \
			return staticFilterMeta; \
		} \
		virtual int filterType() const { return meta().type; } \
	private:

struct MessageFilterMeta
{
	MessageFilterMeta();
	const int type;
};

class JREEN_EXPORT MessageFilter
{
public:
	MessageFilter(MessageSession *session);
	virtual ~MessageFilter() {}
	virtual void filter(Message &message) = 0;
	virtual void decorate(Message &message) = 0;
	virtual void reset() = 0;
	virtual int filterType() const = 0;
protected:
	void send(const Message &message);
private:
	Q_DISABLE_COPY(MessageFilter)
	MessageSession *m_session;
};

class JREEN_EXPORT MessageSession : public QObject
{
	Q_OBJECT
	friend class MessageFilter;
public:
	MessageSession(MessageSessionManager *manager, const JID &jid, bool ignore_thread = true, const QString &thread = QString());
	virtual ~MessageSession();
	const QString &thread() { return m_thread; }
	const JID &jid() { return m_jid; }
	bool ignoreThread() { return m_ignore_thread; }
	void resetResource();
	void registerMessageFilter(MessageFilter *filter);
	template< typename T >
	Q_INLINE_TEMPLATE T messageFilter()
	{
		return static_cast<T>(m_filters.value(static_cast<T>(0).meta().type, 0));
	}
	void sendMessage(const QString &body, const QString &subject = QString());
	void sendMessage(const Message &message);
	virtual void handleMessage(const Message &message);
signals:
	void newMessage(const Message &message);
	void jidChanged(const JID &from, const JID &to);
protected:
	virtual void send(const Message &message);
	void filter(Message &message);
	void decorate(Message &message);
	void setJid(const JID &jid);
	QString m_thread;
	MessageSessionManager *m_manager;
	bool m_ignore_thread;
	bool m_want_upgrade;
private:
	JID m_jid;
	QMap<int, MessageFilter *> m_filters;
};

class MessageSessionHandler
{
public:
	virtual ~MessageSessionHandler() {}
	virtual void handleMessageSession(MessageSession *session) = 0;
};

class JREEN_EXPORT MessageSessionManager : public QObject
{
	Q_OBJECT
public:
	MessageSessionManager(Client *client);
	virtual ~MessageSessionManager() {}
	void send(const Message &message);
	void registerMessageSession(MessageSession *session);
	void registerMessageSessionHandler(MessageSessionHandler *handler, QList<Message::Type> types);//WTF? O_o
	void removeMessageSessionHandler(MessageSessionHandler *handler);
	MessageSession *session(const JID &jid, Message::Type type, bool create = true);
public slots:
	virtual void handleMessage(const jreen::Message &message);
signals:
	void newMessage(const jreen::Message &message);
	void sessionCreated(jreen::MessageSession *session);
private:
	Client *m_client;
	QMultiHash<QString, QPointer<MessageSession> > m_full_sessions;
	QMultiHash<QString, QPointer<MessageSession> > m_bare_sessions;
	QVector<MessageSessionHandler *> m_session_handlers;
	friend class MessageSession;
};

}

#endif // MESSAGESESSION_H
