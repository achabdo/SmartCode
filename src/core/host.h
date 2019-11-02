#ifndef HOST_H
#define HOST_H


class Host
{
public:
  enum OS
  {
    Windows,
    Unix,
    Linux,
    Mac,
    Unknown
  };

  Host();

  static bool isWindowsHost() { return os() == Windows; }
  static bool isLinuxHost() { return os() == Linux; }
  static bool isMacHost() { return os() ==  Mac; }

  static  OS os();
};

#endif // HOST_H
