#include	<control.h>
#include	<testwork.h>
#include	<net_epoll.h>
#include	<model_mysql.h>
using namespace mynet;
Control::Control (){
	work = new testwork(this);	
	network = new net_epoll(this);
	database = new model_mysql();
}

void Control::dealData(int from,void * data, len_t len)
{
	itask * task = new testTask(from, data, len);

	work->addWork(task); 		
}

int Control::init()
{
	work->initWork();
	network->initNetwork();
	database->init();
}
void Control::run()
{
	// 
	printf("network  start running\n");
	network->dowork();
}


void Control::adduser(const char *uid, const char *user, const char *password) 
{
	database->adduser(uid, user,password);
}
void Control::uninstall()
{
	if (work != NULL)
	{
		delete work;
	}
	if (network != NULL)
	{
		delete network;
	}
}

