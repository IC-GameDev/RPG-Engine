// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __SYS_CVAR_H__
#define __SYS_CVAR_H__

// -------------------------------------------------------------------------------------------------
typedef enum
{
  CVAR_BOOL       = (1 <<  0),
  CVAR_INT        = (1 <<  1),
  CVAR_FLOAT      = (1 <<  2),
  CVAR_STRING     = (1 <<  3),
  CVAR_MODIFIED   = (1 <<  4),    // variable was modified
  CVAR_READONLY   = (1 <<  5),    // cannot be modified
  CVAR_CONFIG     = (1 <<  6),    // read & write to config file
} cvarFlags_t;

// -------------------------------------------------------------------------------------------------
class CVar
{
public:
                     CVar(const std::string& name, int flags,
                          const std::string& val, const std::string& desc);
                     CVar(const std::string& name, int flags,
                          const std::string& val, float min, float max,
                          const std::string& desc = "");
                     CVar(const std::string& name, int flags,
                          const std::string& val, const char ** pool,
                          const std::string& desc = "");

  const std::string& GetName() { return name; }
  const std::string& GetDesc() { return desc; }
  int                GetFlags() { return flags; }

  bool               IsModified() { return (flags & CVAR_MODIFIED) != 0; }
  void               SetModified() { flags |= CVAR_MODIFIED; }
  void               ClearModified() { flags &= ~CVAR_MODIFIED; }

  void               SetBool(bool b);
  void               SetInt(int i);
  void               SetFloat(float f);
  void               SetString(const std::string& str);

  bool               GetBool() { return valueBool; }
  int                GetInt() { return valueInt; }
  float              GetFloat() { return valueFloat; }
  const std::string& GetString() { return valueString; }

private:
  void               Init(const std::string& name, int flags,
                          const std::string& val, float min, float max,
                          const char ** pool, const std::string& desc);

  std::string        name;
  std::string        desc;
  int                flags;
  const char **      pool;
  float              min;
  float              max;

  bool               valueBool;
  int                valueInt;
  float              valueFloat;
  std::string        valueString;

  CVar *             next;
  static CVar *      root;

  friend class       CVarSystem;
};

// -------------------------------------------------------------------------------------------------
inline CVar::CVar(const std::string& name, int flags, const std::string& val,
                  const std::string& desc)
{
  Init(name, flags, val, -FLT_MAX, FLT_MAX, NULL, desc);
}

// -------------------------------------------------------------------------------------------------
inline CVar::CVar(const std::string& name, int flags, const std::string& val,
                  float min, float max, const std::string& desc)
{
  Init(name, flags, val, min, max, NULL, desc);
}

// -------------------------------------------------------------------------------------------------
inline CVar::CVar(const std::string& name, int flags, const std::string& val,
                  const char ** pool, const std::string& desc)
{
  Init(name, flags, val, -FLT_MAX, FLT_MAX, pool, desc);
}

#endif /*__SYS_CVAR_H__*/