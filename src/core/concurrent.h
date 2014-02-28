// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __CORE_COMPILER_H__
#define __CORE_COMPILER_H__

#if   defined(R_LINUX)
# define Yield()                    sched_yield()
# define BranchPredict(a, b)        __builtin_expect(a, b)
# define AtomicIncrement(ptr)       __sync_fetch_and_add(ptr, 1)

// -----------------------------------------------------------------------------
class Mutex
{
public:
  Mutex()
  {
    pthread_mutex_init(&mutex, NULL);
  }

  ~Mutex()
  {
    pthread_mutex_destroy(&mutex);
  }

  void Lock()
  {
    pthread_mutex_lock(&mutex);
  }

  void Unlock()
  {
    pthread_mutex_unlock(&mutex);
  }

private:
  pthread_mutex_t mutex;
};

#elif defined(R_WINDOWS)
# define Yield()
# define BranchPredict(a, b)        (a)
# define AtomicIncrement(ptr)       (InterlockedIncrement(ptr) - 1)
#else
# error "Unimplemented"
#endif

#endif
