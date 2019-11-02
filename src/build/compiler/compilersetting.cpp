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

#include <bases.h>
#include <core_constants.h>

#include "compilersetting.h"
#include "compileroption.h"
#include "gcc.h"

CompilerSetting::CompilerSetting(const QString &name) :
  SettingsDocument(name)
{

}

bool CompilerSetting::isInEnvironmentPath()
{
 return false;
}

Compiler *CompilerSetting::compiler() const
{
  return _compiler;
}

bool CompilerSetting::load()
{
  SettingsDocument::load();

  QString compilerType = string("type");
  QString compilerPath = string("path");

  if(compilerType == "Gcc")
    _compiler = new Gcc(compilerPath);
  else if(compilerType == "Mingw")
    _compiler = new Mingw(compilerPath);
}

QList<Message *> CompilerSetting::messages() const
{
  return _messages;
}

//void CompilerSetting::readSettingManager(QDomElement &item)
//{
//  QString itemTagName = item.tagName();

//  if (itemTagName ==  Core::Project::PATH)
//    {
//      QDomElement category = item.firstChild().toElement();

//      Compiler compiler = new Compiler();
//    }
//}
