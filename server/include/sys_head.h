#ifndef _SYS_HEAD_H_
#define _SYS_HEAD_H_


#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>



const int BUF_SIZE = 1024;
const int MAX_EVENT = 1024;
const int SERVER_PORT = 6001;

void writelog(const char * format, ...) ;//写日志

#endif
