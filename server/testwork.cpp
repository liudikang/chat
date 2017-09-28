#include	<iwork.h>
#include	<sys_net.h>
#include	<testwork.h>

testTask::testTask(int id, void * data, len_t len)
{
	printf("new task size:%d\n", len);
	this->data = (package *)new char[len];
	memcpy(this->data, data, len);
}
void testTask::run () 
{
	pk_register *temp = (pk_register *)this->data;
	
}
testTask::~testTask()
{


}

int testwork::addWork(itask *newtask)
{
	qu_task.push(newtask);	
}

int testwork::initWork()
{
	printf("work start\n");
	pthread_t tid;
	pthread_create( &tid, NULL, thread_callback, (void *)this);
	pthread_detach(tid);

}

void *testwork::thread_callback(void * arg)
{
	testwork * pThis = (testwork *)arg;
	for (;;)
	{
		printf("queue size: %u\n", pThis->qu_task.size());
		if ( !pThis->qu_task.empty())
		{
			itask * temp = pThis->qu_task.front();
			pThis->qu_task.pop();
			temp->run();
			delete temp;
		}
		usleep(10000000);
	}
}

void testwork::doWork()
{

}


