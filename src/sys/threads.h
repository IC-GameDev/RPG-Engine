// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __SYS_THREADS_H__
#define __SYS_THREADS_H__

// -----------------------------------------------------------------------------
// Submodules which run in separate threads implement this class
// -----------------------------------------------------------------------------
class Thread
{
public:
  virtual void        Run() = 0;
  virtual const char *GetThreadName() = 0;
};

// -----------------------------------------------------------------------------
// This class keeps track of all the threads in the engine
// -----------------------------------------------------------------------------
class ThreadMngr
{
public:
  virtual void Init() = 0;
  virtual void Destroy() = 0;
  virtual void Spawn(Thread* thread) = 0;
  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual bool IsRunning() = 0;
};

extern ThreadMngr *threadMngr;

#endif
