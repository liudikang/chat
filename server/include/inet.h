#ifndef _INET_H_
#define _INET_H_

class inet
{
public:
	virtual int initNetwork() = 0;
	virtual void dowork() = 0;
	virtual void close() = 0;
};


#endif 
