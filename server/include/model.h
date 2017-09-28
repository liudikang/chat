#ifndef _MODEL_H_
#define _MODEL_H_
#include	<sys_head.h>
#include	<mysql.h>

class model
{
public:
	virtual	int init() = 0;		
	virtual int execSql(const char *sql) = 0;
	virtual void uninstall() = 0;	
	virtual ~model(){};

	virtual int adduser(const char *uid, const char * user, const char * password) = 0;
	virtual bool checkuser(const char *user, const char *password) = 0;
protected:
	MYSQL con;
};

#endif
