# ifndef	_OOPTHREAD_H
#  define	_OOPTHREAD_H

#include	<pthread.h>
#include	<stdlib.h>

class		Thread
{
public:
  Thread();
  virtual 	~Thread();
  virtual void	*run(void *) = 0;
  bool           start(void * arg = NULL);
  bool		cancel(void);
  bool		join(void **exit_value = NULL);
  bool		tryjoin(void **exit_value = NULL);
  bool		operator==(const Thread &thread);

private:
  bool		state;
  pthread_t	tid;
};

struct		t_arg
{
  void		*arg;
  Thread	*thread;
};

#endif
