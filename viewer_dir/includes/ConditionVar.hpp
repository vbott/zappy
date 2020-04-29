#ifndef _CONDITIONVAR_
#define _CONDITIONVAR_

#include <pthread.h>
#include "Mutex.hpp"

class ConditionVar : public Mutex
{
public:
	ConditionVar(const pthread_condattr_t  *attr = NULL);
	~ConditionVar();
	bool	signal();
	bool	broadcast();
	bool	uniqueWait();
	bool	uniqueTimedWait(int ms);
	bool	wait();
	bool	timedWait(int ms);

private:
	pthread_cond_t 	_cond;
};


#endif /* _CONDITIONVAR_ */
