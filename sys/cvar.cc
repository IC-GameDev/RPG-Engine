// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

CVar * CVar::root = NULL;


// -------------------------------------------------------------------------------------------------
void CVar::Init(const std::string& name, int flags,
                const std::string& val, float min, float max,
                const char ** pool, const std::string& desc)
{
  this->name = name;
  this->min = min;
  this->max = max;
  this->pool = pool;
  this->desc = desc;
  this->valueString = "";
  this->next = root;
  root = this;

  this->flags = flags & ~CVAR_READONLY;
  SetString(val);
  this->flags = flags & ~CVAR_MODIFIED;
}

// -------------------------------------------------------------------------------------------------
void CVar::SetBool(bool b)
{
  flags |= CVAR_MODIFIED;

  if (flags & CVAR_READONLY)
  {
    EXCEPT << "Attempting to set readonly cvar '" << name << "'";
  }

  valueBool = b;
  valueInt = b ? 1 : 0;
  valueFloat = b ? 1.0f : 0.0f;
  valueString = b ? "true" : "false";
  return;
}

// -------------------------------------------------------------------------------------------------
void CVar::SetInt(int i)
{
  flags |= CVAR_MODIFIED;

  if (flags & CVAR_READONLY)
  {
    EXCEPT << "Attempting to set readonly cvar '" << name << "'";
  }

  valueBool = i ? true : false;
  valueInt = i;
  valueFloat = (float)valueInt;

  if (flags & CVAR_BOOL)
  {
    valueString = valueBool ? "true" : "false";
  }
  else if (flags & CVAR_INT || flags & CVAR_STRING)
  {
    valueString.resize(20);
    sprintf(&valueString[0], "%d", valueInt);
  }
  else if (flags & CVAR_FLOAT)
  {
    valueString.resize(20);
    sprintf(&valueString[0], "%ff", valueFloat);
  }
}

// -------------------------------------------------------------------------------------------------
void CVar::SetFloat(float f)
{
  flags |= CVAR_MODIFIED;

  if (flags & CVAR_READONLY)
  {
    EXCEPT << "Attempting to set readonly cvar '" << name << "'";;
  }

  valueFloat = f;
  valueBool = abs(valueFloat) <= 1e-5 ? false : true;
  valueInt = (int)valueFloat;

  if (flags & CVAR_BOOL)
  {
    valueString = strdup(valueBool ? "true" : "false");
  }
  else if (flags & CVAR_INT)
  {
    valueString.resize(20);
    sprintf(&valueString[0], "%d", valueInt);
  }
  else if (flags & CVAR_FLOAT || flags & CVAR_STRING)
  {
    valueString.resize(20);
    sprintf(&valueString[0], "%ff", valueFloat);
  }
}

// -------------------------------------------------------------------------------------------------
void CVar::SetString(const std::string& str)
{
  flags |= CVAR_MODIFIED;

  if (flags & CVAR_READONLY)
  {
    EXCEPT << "Attempting to set readonly cvar '" << name << "'";
  }

  if (pool)
  {
    valueBool = false;
    valueInt = 0;
    valueFloat = 0.0f;
    valueString = "";

    for (int i = 0; pool[i]; ++i)
    {
      if (str == pool[i])
      {
        valueBool = true;
        valueInt = i;
        valueFloat = (float)i;
        valueString = str;
      }
    }

    return;
  }

  if (flags & CVAR_BOOL)
  {
    valueBool = str == "true";
    valueInt = valueBool ? 1 : 0;
    valueFloat = valueBool ? 1.0f : 0.0f;
    valueString = valueBool ? "true" : "false";
    return;
  }
  else if (flags & CVAR_INT)
  {
    valueInt = atoi(str.c_str());
    valueBool = valueInt ? true : false;
    valueFloat = (float)valueInt;
    valueString.resize(20);
    sprintf(&valueString[0], "%d", valueInt);
    return;
  }
  else if (flags & CVAR_FLOAT)
  {
    valueFloat = (float)atof(str.c_str());
    valueBool = abs(valueFloat) <= 1e-5 ? false : true;
    valueInt = (int)valueFloat;
    valueString.resize(20);
    sprintf(&valueString[0], "%ff", valueFloat);
    return;
  }
  else if (flags & CVAR_STRING)
  {
    valueBool = !str.empty();
    valueInt = !str.empty();
    valueFloat = str.empty() ? 0.0f : 1.0f;
    valueString = str;
    return;
  }
}
