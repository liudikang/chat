#ifndef _NET_EPOLL_H_
#define _NET_EPOLL_H_
#include	<inet.h>
#include	<sys_head.h>
class Control;
class net_epoll:public inet
{
public:
	net_epoll(Control *p){
		control = p;
	}
	virtual int initNetwork() override;
	virtual void dowork() override;
	virtual void close() override;
private:
	void addfd(int);
private:
	int epoll_fd;
	int listen_fd;
	Control * control;
};

#endif
