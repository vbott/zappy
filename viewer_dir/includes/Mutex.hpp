#ifndef		_MUTEX_
#define		_MUTEX_

#include	<pthread.h>
#include	<time.h>
#include	<stdlib.h>

typedef pthread_mutex_t mutex_t;
typedef pthread_mutexattr_t mutexattr_t;

class		Mutex
{
 public:
  Mutex(mutexattr_t *attr = NULL);
  virtual ~Mutex();
  virtual bool	lock(void);
  virtual bool	unlock(void);
  virtual bool	tryLock(void);
  virtual bool	timedLock(int sec, int nano = 0);

 protected:
  mutex_t	mutex;
};

class		ScopedLock
{
  public:
	ScopedLock(Mutex &mutex) : _mutex(mutex)
	{
	 _mutex.lock();
	}
	~ScopedLock()
	{
	 _mutex.unlock();
	}

  private:
	Mutex	&_mutex;
};

#endif		/* _MUTEX_ */
