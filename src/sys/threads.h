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
// Signals can be used by a thread when they need to be notified of a change
// by another thread
// -----------------------------------------------------------------------------
class Signal
{
public:
  virtual void Wait() = 0;
  virtual void Notify() = 0;
};

// -----------------------------------------------------------------------------
// This class keeps track of all the threads in the engine
// The workload is divided between multiple threads:
//  - [main]: the thread spawned by the OS and the rendering context is
//                 bound to it. Xlib/Win32 events are also polled from here
//  - [world]: this thread handles game logic, receives messages from
//                  other threads through a lockless queue
//  - [network]: listens for network messages, propagates messages
//                       that are sent to it from other threads
//  - [rsmngr]: NOT IMPLEMENTED - tracks resource usage
//  - [pool #n]: NOT IMPLEMENTED - additional cores run threads that process
//               small jobs
// -----------------------------------------------------------------------------
class ThreadMngr
{
public:
  virtual void    Init() = 0;
  virtual void    Destroy() = 0;
  virtual void    Spawn(Thread* thread) = 0;
  virtual Signal *CreateSignal() = 0;
  virtual void    Start() = 0;
  virtual void    Stop() = 0;
};

// -----------------------------------------------------------------------------
extern ThreadMngr *threadMngr;

#endif
