// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include <exception>
#include "engine/exception.h"


// -----------------------------------------------------------------------------
Exception::Exception()
  : file(""),
    func(""),
    line(1),
    msg("")
{
}

// -----------------------------------------------------------------------------
Exception::Exception(const char * file_, const char * func_, int line_)
  : file(file_),
    func(func_),
    line(line_)
{
  std::stringstream ss;
  ss << "[" << file << ":" << line << "] Exception in " << func << ": ";
  msg = ss.str();
}

// -----------------------------------------------------------------------------
Exception& Exception::operator << (const char * str)
{
  msg.append(str);
  return *this;
}

// -----------------------------------------------------------------------------
Exception& Exception::operator << (int i)
{
  std::stringstream ss;
  ss << msg << i;
  msg = ss.str();
  return *this;
}

// -----------------------------------------------------------------------------
const char * Exception::what() const throw()
{
  return msg.c_str();
}
