// Copyright (C) 2014  by Achrouf Abdeour <achroufabdenour@gmail.com>
// Auteur Achrouf Abdenour

// This File is part of SmartCode

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program. If not, see http://www.gnu.org/licenses/.

#include <QString>

#include <core_constants.h>

#include "message.h"


Message::Message()
{
  type = Unknown;
  info= QString();
  file= QString();
  line= 0;
  icon = QIcon();
}

Message::Message(const Message::MessageType &_type, QString _info
                 , QString _file, int _line)
{
  type = _type;
  info=_info;
  file=_file;
  line=_line;
  icon = messageIcon(type);
}

QIcon Message::messageIcon(Message::MessageType type)
{
  switch(type)
    {
    case Message::Error:
      return QIcon(Core::Icon::COMPILE_ERROR);
    case  Message::Warning:
      return QIcon(Core::Icon::COMPILE_WARNING);
    }

  return QIcon();
}
