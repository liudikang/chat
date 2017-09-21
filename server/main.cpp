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
const int SERVER_PORT = 60000;
int log_fd ;
int sock_fd ;
char _buf[1024];
int getDate()
{
	time_t now;
	struct tm* s_now;
	char * week[] = {"天", "一", "二", "三", "四", "五", "六" };
	time(&now);
	s_now = localtime(&now);	
	return sprintf( _buf, "%04d年%02d月%02d日 星期%s %02d:%02d:%02d  ", 1900 + s_now->tm_year, s_now->tm_mon + 1, s_now->tm_mday, week[s_now->tm_wday],s_now->tm_hour, s_now->tm_min, s_now->tm_sec);
}
int toDeamon()
{
    pid_t cpid;
    if ( (cpid = fork()) < 0)
    {
        return -1;
    }else if (cpid == 0)
    {
        int sid;
        if ((sid =setsid()) == -1)
            return -1;
        if (chdir("/") == -1)
            return -1;
        if (umask(0002) == -1)
            return -1;
        if (close(STDIN_FILENO) == -1)
            return -1;
        if (close(STDERR_FILENO) == -1)
            return -1;
        if (close(STDOUT_FILENO) == -1)
            return -1;
        return sid;
    }else
    {   // parent
        return 0;
    }
}

void writelog(char * format, ...) //写日志
{
	va_list argv;
	va_start(argv, format);	
	int offset = getDate();
	int msglen = vsnprintf(_buf + offset, BUF_SIZE - offset - 1,format, argv);
	_buf[offset + msglen] = '\n';
	_buf[offset + msglen + 1] = 0;
	write(log_fd, _buf, offset + msglen + 1);
}

void addfd(int epoll_fd, int new_fd)  //默认边缘触发
{
	struct epoll_event event;
	event.events = EPOLLIN | EPOLLET;
	event.data.fd = new_fd;
	int mask = fcntl( new_fd, F_GETFL);
	fcntl( new_fd, F_SETFL, mask | O_NONBLOCK);
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_fd, &event);
}

void doepoll(int epoll_fd)
{
	struct epoll_event event[MAX_EVENT];
	char readbuf[BUF_SIZE];
	for(;;)
	{
		int ret = epoll_wait( epoll_fd, event, MAX_EVENT, -1);
		if (ret < 0)
		{
			writelog("%s :%s ", "epoll_wait error", strerror(errno));
			break;
		}else
		{
			for (int i = 0; i < ret; i++)
			{

				int fd = event[i].data.fd;
				if ( fd == sock_fd)
				{
					int new_fd = accept(fd, NULL, NULL);
				//	writelog("new connct");
					addfd(epoll_fd, new_fd);
				}else if(event[i].events & EPOLLIN)
				{
					while(1)
					{
						int len = read(fd, readbuf, BUF_SIZE);// 对读到的数据不做任何处理
						if (len < 0)
						{
							if ( errno == EAGAIN)
								break;
							close(fd);
							break;
						}else if (len == 0)
						{
							close(fd);
							break;
						}else if ( strncmp("quit", readbuf, 4) == 0)
						{
							close(fd);
							break;
						}
					}
				}

			}
		}
	}
}

int main(int argc, char * argv[])
{
//	int id = toDeamon();
//	if (id == 0)
//		return 0;

	//脱离终端
	log_fd = open("/tmp/chaterror.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (log_fd < 0)
		perror("log open error");

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);		
	if (sock_fd < 0)
		perror("socket error");
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons( SERVER_PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock_fd, (const struct sockaddr*) &addr, sizeof(addr)) < 0)
		perror("bind error");
	if ( listen(sock_fd, 4) < 0)
		perror("listen error");	
	int epoll_fd = epoll_create(1);
	addfd(epoll_fd, sock_fd);
	//初始创建工作完成



	doepoll(epoll_fd);	

	close(sock_fd);
	close(log_fd);
	return 0;
}
