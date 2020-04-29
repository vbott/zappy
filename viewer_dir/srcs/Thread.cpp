#include <iostream>
#include "Thread.hpp"

static void		*starter(void *arg)
{
  t_arg	*tmp = static_cast<t_arg*>(arg);
  void	*ret = tmp->thread->run(tmp->arg);
  delete tmp;
  return (ret);
}

Thread::Thread() : state(false)
{}

Thread::~Thread()
{
  if (state)
    this->cancel();
}

bool	Thread::operator==(const Thread &thread)
{
  return static_cast<bool>(pthread_equal(tid, thread.tid));
}

bool	Thread::start(void *arg)
 {
   if (this->state == false)
   {
     t_arg	*tmp = new t_arg;
     tmp->arg = arg;
     tmp->thread = this;
     bool ret = static_cast<bool>(!pthread_create(&tid,
			    NULL, starter,
			    static_cast<void*>(tmp)));
     if (ret)
	this->state = true;
     return (ret);
  }
  else
    return (false);
}

bool	Thread::cancel(void)
{
  bool	ret;

  if (state == true)
  {
    ret = static_cast<bool>(!pthread_cancel(tid));
    if (ret)
      state = false;
    return (ret);
  }
  else
    return (false);
}

bool		Thread::join(void **exit_value)
{
   bool		ret;

   if (state != false)
    {
      ret = static_cast<bool>(!pthread_join(tid, exit_value));
      state = false;
      return (ret);
    }
   else
      return false;
}

bool		Thread::tryjoin(void **exit_value)
{
   bool		ret;

    if (state != false)
     {
       ret = static_cast<bool>(!pthread_tryjoin_np(tid, exit_value));
       if (ret)
	 state = false;
       return (ret);
     }
   else
     return false;
}
