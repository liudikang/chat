#ifndef _MODEL_MYSQL_H_
#define _MODEL_MYSQL_H_
#include	<model.h>
class model_mysql:public model
{
public:
	model_mysql(){}
	virtual	int init() override;		
	virtual int execSql(const char *sql) override;
	virtual void uninstall() override;	
	virtual ~model_mysql();

	virtual int adduser(const char *uid, const char * user, const char * password) override;
	virtual bool checkuser(const char *user, const char *password) override;
private:
	my_ulonglong getcount(const char *tablename, const char*condition);
	void getKeyByCondition(const char *codition, char * buf);
private:
	bool autoRecon;
};

#endif
