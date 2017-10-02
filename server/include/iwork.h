#ifndef _IWORK_H_
#define _IWORK_H_

class Control;
class itask
{
public:
	virtual void run(Control *) = 0;
};

class iwork
{
public:
	virtual int initWork() = 0;
	virtual int addWork(itask * ) = 0;
	virtual void doWork() = 0;

};

#endif
