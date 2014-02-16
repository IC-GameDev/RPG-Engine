// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __ENGINE_EXCEPTION_H__
#define __ENGINE_EXCEPTION_H__

#include "engine/common.h"

/**
 * Extended exception class
 *
 * Tracks the origin of the expression & allows 
 * std::stringstream-like formatting
 */
class Exception : public std::exception
{
public:
  /**
   * Creates a new exception without a message
   */
  Exception();

  /**
   * Creates a new, including source file info
   * @param file File name (__FILE__)
   * @param func Function name (__FUNCTION__, if supported)
   * @param line Line number (__LINE)
   */
  Exception(const char * file, const char * func, int line);

  /**
   * Cleanup after the exception
   */
  virtual ~Exception() throw () { }

  /**
   * Appends a string to the message
   * @param msg Message to be added
   */
  Exception& operator << (const char * msg);

  /**
   * Appends an integer to the message
   * @param i Integer to be added
   */
  Exception& operator << (int i);

  /**
   * Returns the formatted message
   * @return Formatted message
   */
  const char * what() const throw();

private:

  std::string file;
  std::string func;
  int line;
  std::string msg;
};

#define EXCEPT throw Exception(__FILE__, __FUNCTION__, __LINE__)

#endif /*__ENGINE_EXCEPTION_H__*/
