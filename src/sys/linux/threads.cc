// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#include "sys/common.h"

// -----------------------------------------------------------------------------
class SignalImpl : public Signal
{
public:
         SignalImpl();
        ~SignalImpl();
  void   Notify();
  void   Wait();

private:
  pthread_mutex_t mutex;
  pthread_cond_t  cond;
  unsigned long   count;
};

// -----------------------------------------------------------------------------
// This class keeps track of all the threads in the engine
// -----------------------------------------------------------------------------
class ThreadMngrImpl : public ThreadMngr
{
public:
  void    Init();
  void    Destroy();
  void    Spawn(Thread* thread);
  Signal *CreateSignal();
  void    DestroySignal(Signal *signal);
  void    Start();
  void    Stop();

private:
  struct ThreadImpl
  {
    pthread_t  handle;
    Thread    *thread;
  };

  std::set<Signal*>       signals;
  std::vector<ThreadImpl> pool;

  friend void* ThreadStarter(void *data);
};

// -----------------------------------------------------------------------------
static ThreadMngrImpl threadMngrImpl;
ThreadMngr *threadMngr = &threadMngrImpl;

// -----------------------------------------------------------------------------
SignalImpl::SignalImpl()
  : count(1)
{
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);
}

// -----------------------------------------------------------------------------
SignalImpl::~SignalImpl()
{
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  threadMngrImpl.DestroySignal(this);
}

// -----------------------------------------------------------------------------
void SignalImpl::Notify()
{
  pthread_mutex_lock(&mutex);
  ++count;
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
}

// -----------------------------------------------------------------------------
void SignalImpl::Wait()
{
  while (!count)
  {
    pthread_cond_wait(&cond, &mutex);
  }

  --count;
  pthread_mutex_unlock(&mutex);
}

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
  std::set<Signal*>::iterator it;
  struct timespec ts;
  ts.tv_sec = 2;
  ts.tv_nsec = 0;

  for (it = signals.begin(); it != signals.end(); ++it)
  {
    (*it)->Notify();
  }

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
        pthread_cancel(pool[i].handle);
      }
    }
  }
}

// -----------------------------------------------------------------------------
Signal *ThreadMngrImpl::CreateSignal()
{
  return *signals.insert(new SignalImpl()).first;
}

// -----------------------------------------------------------------------------
void ThreadMngrImpl::DestroySignal(Signal *signal)
{
  std::set<Signal*>::iterator iter;
  if ((iter = signals.find(signal)) != signals.end())
  {
    signals.erase(iter);
  }
}