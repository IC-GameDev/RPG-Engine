// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// -----------------------------------------------------------------------------
// This class keeps track of all the threads in the engine
// -----------------------------------------------------------------------------
class ThreadMngrImpl : public ThreadMngr
{
public:
  void Init();
  void Destroy();
  void Spawn(Thread* thread);
  void Start();
  void Stop();
  bool IsRunning();

private:
  struct ThreadImpl
  {
    pthread_t  handle;
    Thread    *thread;
  };

  std::vector<ThreadImpl> pool;
  volatile bool running;
  pthread_attr_t attr;

  friend void* ThreadStarter(void *data);
};

// -----------------------------------------------------------------------------
static ThreadMngrImpl threadMngrImpl;
ThreadMngr *threadMngr = &threadMngrImpl;

// -----------------------------------------------------------------------------
void* ThreadStarter(void *data)
{
  ThreadMngrImpl::ThreadImpl *thread;
  const char *name;

  try
  {
    if (!(thread = (ThreadMngrImpl::ThreadImpl*)data))
    {
      EXCEPT << "Invalid thread descriptor";
    }

    if (!(name = thread->thread->GetThreadName()))
    {
      EXCEPT << "Unidentified thread";
    }

    thread->thread->Run();
    return NULL;
  }
  catch (std::exception& e)
  {
    std::cerr << "[" << name << "]" << e.what() << std::endl;
    engine->Quit();
    return NULL;
  }
}

// -----------------------------------------------------------------------------
void ThreadMngrImpl::Init()
{
}

// -----------------------------------------------------------------------------
void ThreadMngrImpl::Destroy()
{
  pthread_exit(NULL);
}

// -----------------------------------------------------------------------------
void ThreadMngrImpl::Spawn(Thread* thread)
{
  pool.resize(pool.size() + 1);
  pool.rbegin()->thread = thread;
}

// -----------------------------------------------------------------------------
void ThreadMngrImpl::Start()
{
  running = true;
  for (size_t i = 0; i < pool.size(); ++i)
  {
    if (pthread_create(&pool[i].handle, NULL, ThreadStarter, &pool[i]))
    {
      EXCEPT << "Cannot spawn [" << pool[i].thread->GetThreadName() << "]";
    }
  }
}

// -----------------------------------------------------------------------------
void ThreadMngrImpl::Stop()
{
  struct timespec ts;
  ts.tv_sec = 2;
  ts.tv_nsec = 0;

  running = false;
  if (clock_gettime(CLOCK_REALTIME, &ts))
  {
    for (size_t i = 0; i < pool.size(); ++i)
    {
      pthread_join(pool[i].handle, NULL);
      pthread_detach(pool[i].handle);
    }
  }
  else
  {
    ts.tv_sec += 1;
    for (size_t i = 0; i < pool.size(); ++i)
    {
      if (pthread_timedjoin_np(pool[i].handle, NULL, &ts) != 0)
      {
        std::cerr << "Timeout [" << pool[i].thread->GetThreadName()
                  << "]" << std::endl;
      }
    }
  }
}

// -----------------------------------------------------------------------------
bool ThreadMngrImpl::IsRunning()
{
  return running;
}
