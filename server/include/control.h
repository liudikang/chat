#ifndef _CONTROL_H_
#define _CONTROL_H_
#include	<sys_head.h>
#include	<sys_net.h>
#include 	<inet.h>
#include 	<iwork.h>
#include	<model.h>
using namespace mynet;
class Control
{
public:
	Control();
	void dealData(int from,void * data, len_t len);
	int init();
	void run();
	void uninstall();
	
	void adduser(const char *uid, const char *user, const char *password);

private:
	inet *network; //
	iwork *work;
	model *database;
};

#endif
