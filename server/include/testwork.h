#ifndef _TESTWORK_H_
#define _TESTWORK_H_
#include 	<sys_net.h>
#include	<sys_head.h>
using namespace mynet;
class Control;
class testTask:public itask
{
public:
	testTask(int id, void * data, len_t len);
	virtual void run () ;
	virtual ~testTask();

private:
	int id;
};


class testwork:public iwork
{
public:
	testwork(Control * p){
		control = p;
	}
	virtual int addWork(itask *);
	virtual int  initWork();
	virtual void doWork();
	Control * control;
};

#endif
