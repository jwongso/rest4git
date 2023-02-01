/// \file utils.h
/// \brief Global common utilities for rest4git.
/// \author Juniarto Saputra (jsaputra@riseup.net)
/// \version 1.0
/// \date Dec 2022
///
/// Currently there is no detailed description available.
/// \todo Add more detailed description!

#pragma once
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <unistd.h>
#include <stdio.h>

#include "syscmd.h"

namespace rest4git
{

class Utils
{
  public:
    static std::string pwd()
    {
      char pwd[FILENAME_MAX];
      if (getcwd(pwd, sizeof(pwd)) != NULL)
      {
        return std::string(pwd);
      }

      return rest4git::SysCmd::execute("pwd");
    }

    static std::string::size_type find(
      const std::string& str, 
      const std::string& substr, 
      std::string::size_type start = 0)
    {
      if (substr.empty() || start > str.size())
      {
        return std::string::npos;
      }

      auto found = std::strstr(str.c_str() + start, substr.c_str());
      return (found == nullptr ? 
        std::string::npos : std::string::size_type(found - str.c_str()));
    }
};

}