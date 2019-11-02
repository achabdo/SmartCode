#include "disassembly.h"

Disassembly::Disassembly(QWidget *parent) : DebuggerClient(parent)
{
  setHeaderHidden(true);
}

Disassembly::~Disassembly()
{

}

QString Disassembly::cmd() const
{
  return "disassemble";
}

QString Disassembly::outputFormat() const
{
  return "([^\\r\\n]+)";
}

int Disassembly::linesToBeRemoved() const
{
  return  TakeFirstLine|TakeEndLine;
}

