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

#include "host.h"

Host::Host()
{

}

Host::OS Host::os()
{
#if defined(Q_OS_WIN)
  return  Windows;
#elif defined (Q_OS_LINUX)
  return Linux;
#elif defined (Q_OS_MAC)
  return Mac;
#elif defined (Q_OS_UNIX)
  return Unix;
#else
  return Unknown;
#endif

}

