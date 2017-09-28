#include	<model_mysql.h>
#include	<string>
using namespace std;
model_mysql::~model_mysql()
{
	this->uninstall();
}
int model_mysql::init()
{
	if (mysql_library_init(0, NULL, NULL)) {
	    fprintf(stderr, "could not initialize MySQL library\n");
	    exit(1);
	}
	if ( !mysql_init(&con))
	{
	    fprintf(stderr, "could not initialize MySQL\n");
	    exit(1);
	}

	if ( !mysql_real_connect(&con, "localhost", "root", "liu2323q", "my_chat", 0, NULL, 0))
	{
	    fprintf(stderr, "could not connect MySQL\n");
		fprintf(stderr, "%s\n", mysql_error(&con));
	    exit(1);
	}
	autoRecon = 0;
	mysql_options(&con, MYSQL_OPT_RECONNECT, &autoRecon); //如果丢失连接   自动重连
	this->adduser("liu", "username", "pwd");
}

int model_mysql::execSql(const char *sql) 
{
//	printf("execSql\n");
	if ( mysql_query(&con ,sql))
	{
		 fprintf(stderr, "%s\n", mysql_error(&con));
		 return 0;
	}
	return 1;
}


void getKeyByCondition(const char *codition, char * buf)
{

}


/*
如果sql语句错误返回值会是0
*/
my_ulonglong model_mysql::getcount(const char *tablename, const char*condition = NULL) 
{
//	printf("getcount\n");
	string sql = "select  * from ";
	my_ulonglong ret = 0;
	sql = sql + tablename ;
	if (condition != NULL &&  strcmp(condition, "") != 0)
		sql = sql + " where " + condition;
//	printf("getcount end\n");		
	if ( this->execSql(sql.c_str()))
	{
		MYSQL_RES* result = mysql_store_result(&this->con);
		if ( result != NULL)
		{
			ret = mysql_num_rows(result);
			//printf("%lu\n", ret);
			mysql_free_result(result);
		}
	}
	return ret;
}

int model_mysql::adduser(const char *uid, const char * user, const char * password) 
{
	string sql = "insert into userinfo(uid, uname, pwd) values";
	sql = sql + "('" + uid + "', '" + user + "','" + password + "')";
	printf("adduser %s\n", sql.c_str());
	this->execSql(sql.c_str());	
}
bool model_mysql::checkuser(const char *uid, const char *password)
{
	//string condition = "
}
void model_mysql::uninstall() 
{
	mysql_close(&con);
	mysql_library_end();	
}
