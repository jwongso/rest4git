/// \file syscmd.h
/// \brief Static SysCmd class for rest4git.
/// \author Juniarto Saputra (jsaputra@riseup.net)
/// \version 1.0
/// \date Aug 2022
///
/// Currently there is no detailed description available.
/// \todo Add more detailed description!

#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <array>

const unsigned int MAX_CHAR = 262144;

namespace rest4git
{

class SysCmd
{
public:
  static std::string execute(const std::string& command)
  {
    std::array<char, MAX_CHAR> byte_array;
    std::string res;

    std::unique_ptr<FILE, decltype(&pclose)> fpipe(::popen(command.c_str(), "r"), pclose);
    if (!fpipe)
    {
      return "popen failed!";
    }

    while (::fgets(byte_array.data(), byte_array.size(), fpipe.get()) != nullptr)
    {
      res += byte_array.data();
    }

    return res;
  }

  static bool file_exists(const std::string& path)
  {
    std::string p = "[ -f " + path + " ] && echo '1' || echo '0'";
    std::string res = rest4git::SysCmd::execute(p);
    return (res == "1\n") ? true : false;
  }
};

}