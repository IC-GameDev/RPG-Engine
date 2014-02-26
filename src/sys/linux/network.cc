// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// -----------------------------------------------------------------------------
// Linux-specific implementation of the networking subsystem
// -----------------------------------------------------------------------------
class NetworkImpl : public Network
{
public:
  void          Init();
  void          Run();
  void          Destroy();
  const char   *GetThreadName() { return "network"; }
};


// -----------------------------------------------------------------------------
static NetworkImpl networkImpl;
Network *network = &networkImpl;

// -----------------------------------------------------------------------------
void NetworkImpl::Init()
{
}

// -----------------------------------------------------------------------------
void NetworkImpl::Run()
{
}

// -----------------------------------------------------------------------------
void NetworkImpl::Destroy()
{
}
