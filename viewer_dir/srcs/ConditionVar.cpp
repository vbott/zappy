#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include "ConditionVar.hpp"

ConditionVar::ConditionVar(const pthread_condattr_t *attr) : Mutex()
{
  pthread_cond_init(&_cond, attr);
}

ConditionVar::~ConditionVar()
{
  pthread_cond_destroy(&_cond);
}

bool    ConditionVar::signal()
{
  return (static_cast<bool>(!pthread_cond_signal(&_cond)));
}

bool    ConditionVar::broadcast()
{
  return (static_cast<bool>(!pthread_cond_broadcast(&_cond)));
}

bool	ConditionVar::wait()
{
  return (static_cast<bool>(!pthread_cond_wait(&_cond, &this->mutex)));
}

bool	ConditionVar::uniqueWait()
{
  bool	ret;

  this->lock();
  ret = this->wait();
  this->unlock();
  return (ret);
}

bool	ConditionVar::uniqueTimedWait(int ms)
{
  bool	ret;

  this->lock();
  ret = this->timedWait(ms);
  if (!ret)
    perror("condvar");
  this->unlock();
  return (ret);
}

bool		ConditionVar::timedWait(int ms)
{
  struct timespec ts;
  struct timeval now;

  ts.tv_sec = ms / 1000;
  ms -= ts.tv_sec * 1000;
  ts.tv_nsec = ms * 1000000;
  gettimeofday(&now, NULL);
  ts.tv_sec += now.tv_sec;
  ts.tv_nsec += now.tv_usec * 1000;
  return (static_cast<bool>(!pthread_cond_timedwait(&_cond,
				  &this->mutex, &ts)));
}

