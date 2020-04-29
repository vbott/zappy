#include "Mutex.hpp"

bool	Mutex::lock(void)
{
  return static_cast<bool>(!pthread_mutex_lock(&mutex));
}

bool	Mutex::unlock(void)
{
  return static_cast<bool>(!pthread_mutex_unlock(&mutex));
}

bool	Mutex::tryLock(void)
{
  return static_cast<bool>(!pthread_mutex_trylock(&mutex));
}

bool	Mutex::timedLock(int sec, int nano)
{
  struct timespec ts;

  ts.tv_sec = sec;
  ts.tv_nsec = nano;
  return static_cast<bool>(!pthread_mutex_timedlock(&mutex, &ts));
}

Mutex::Mutex(mutexattr_t *attr)
{
  pthread_mutex_init(&mutex, attr);
}

Mutex::~Mutex()
{
  pthread_mutex_destroy(&mutex);
}
