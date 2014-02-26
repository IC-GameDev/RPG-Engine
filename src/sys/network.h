// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __SYS_NETWORK_H__
#define __SYS_NETWORK_H__

// -----------------------------------------------------------------------------
// Networking
// -----------------------------------------------------------------------------
class Network : public Thread
{
public:
  virtual void Init() = 0;
  virtual void Destroy() = 0;
};

extern Network *network;

#endif
