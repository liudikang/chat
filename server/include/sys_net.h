#ifndef _SYS_NET_H
#define _SYS_NET_H
#include 	<sys/types.h>

namespace mynet{
enum pk_type{ register_t, login_t, msg_t, logout_t, life_t};  //消息类型


struct package 
{
	int32_t length; //防止粘包
	int32_t type;
};
typedef int32_t len_t;
struct pk_register :public package
{
	char uid[32]
	char username[64];
	char password[128];
	pk_register(){
		type = register_t;
		username[0] = 0;
		password[0] = 0;
	}
};


struct pk_login :public package
{
	char username[128];
	char password[128];
	pk_login(){
		type = register_t;
		username[0] = 0;
		password[0] = 0;
	}
};



struct pk_msg : public package
{
	int32_t msgtype;
	pk_msg(){
		type = register_t;
		msgtype = -1;
	}
};
}
#endif
