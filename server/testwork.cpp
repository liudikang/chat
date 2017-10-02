#include	<iwork.h>
#include	<sys_net.h>
#include	<testwork.h>
#include	<control.h>
#include 	<sys/signal.h>
testTask::testTask(int id, void * data, len_t len)
{
	printf("new task size:%d\n", len);
	this->data = (package *)new char[len];
	memcpy(this->data, data, len);
}
void testTask::run (Control * control) 
{
	printf("run\n");
	switch (this->data->type)
	{
	case t_reg:
		{
			pk_register *temp = (pk_register *)this->data;
			control->adduser(temp->uid, temp->username, temp->password);
		}
		break;
	case t_login:
		break;
	case t_msg:
		break;
	case t_logout:
		break;
	case t_life:
		break;
	default:
		break;
	}

}
testTask::~testTask()
{
	delete []this->data;
}

int testwork::addWork(itask *newtask)
{
	while (task_wait)
		sleep(1);
	qu_task.push(newtask);	
	sem_post(&this->sem);
}

int testwork::initWork()
{
	sem_init( &this->sem, 0, 0);
	pthread_mutex_init(&mutex_lst, NULL);
	has_n = 0;
	run_n = 0;
	task_wait = false;
	pthread_create( &man_tid, NULL, thread_manage, (void *)this);
	pthread_detach(man_tid);


	this->addNewThread();

}
void free_Thread(short n)
{
//	task_wait = true;	



	//pthread_cancel(tid);
//	task_wait = false;	
}
void testwork::addNewThread()
{
	pthread_t tid;
	pthread_create( &tid, NULL, thread_callback, (void *)this);
	pthread_detach(tid);
	this->lst_pthread.push_back(tid);
	has_n++;
}

void *testwork::thread_manage(void * arg)
{
	testwork * pThis = (testwork *)arg;
	for (;;)
	{
	/*	cout << "run:" << pThis->run_n << ",  has:" << pThis->has_n << endl;*/
		usleep(1000000); //1s
	}
	return NULL;
}
void *testwork::thread_callback(void * arg) //增加信号量
{
	testwork * pThis = (testwork *)arg;
	for (;;)
	{
		sem_wait( &pThis->sem);
		pThis->run_n++;
		if ( !pThis->qu_task.empty())
		{
			itask * temp = pThis->qu_task.front();
			pThis->qu_task.pop();
			temp->run(pThis->control);
			delete temp;
		}
		pThis->run_n--;
		//usleep(1000000); //1s
		cout << "woqu\n" << endl;
		usleep(1000000); 
	}
	return NULL;
}

void testwork::doWork()
{

}


