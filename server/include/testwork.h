#ifndef _TESTWORK_H_
#define _TESTWORK_H_
#include 	<sys_net.h>
#include	<queue>
#include	<list>
#include	<sys_head.h>
#include	<pthread.h>
using namespace mynet;
using namespace std;
class Control;
class testTask:public itask
{
public:
	testTask(int id, void * data, len_t len);
	virtual void run (Control *) ;
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
	static void * thread_manage(void *);
	void addNewThread();
	sem_t sem;

	atomic<bool> task_wait;

	short min_n;
	short max_n;
	atomic<short> run_n;
	atomic<short> has_n;
public:	
	pthread_mutex_t mutex_lst;

	pthread_t man_tid;
	queue<itask *> qu_task;
	list<pthread_t> lst_pthread;
	Control * control;
};

#endif
