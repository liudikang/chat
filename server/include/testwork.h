#ifndef _TESTWORK_H_
#define _TESTWORK_H_
#include 	<sys_net.h>
#include	<queue>
#include	<sys_head.h>
#include	<pthread.h>
using namespace std;
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
	package *data;
};


class testwork:public iwork
{
public:
	testwork(Control * p){
		control = p;
	}
	virtual int addWork(itask *) override;
	virtual int  initWork();
	virtual void doWork();
private:
	static void * thread_callback(void *);
	queue<itask *> qu_task;
	Control * control;
};

#endif
