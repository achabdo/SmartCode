#ifndef MESSAGE_H
#define MESSAGE_H

#include <QIcon>
#include <QString>

class Message
{
public:

    enum MessageType
    {
      Unknown,
      Error,
      Warning
    };

    Message();
    Message(const MessageType &_type,QString _info,QString _file = QString(),int _line = -1);

    MessageType type;
    QString info;
    QString file;
    int line;
    QIcon icon;

    QIcon messageIcon(MessageType type);
};

#endif // MESSAGE_H
