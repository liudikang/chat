#include	<control.h>
#include	<testwork.h>
#include	<net_epoll.h>


Control::Control (){
	work = new testwork(this);	
	network = new net_epoll(this);
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
}
void Control::run()
{
	network->dowork();
}

void Control::uninstall()
{

}

