#include	<sys_head.h>
#include	<inet.h>
#include	<net_epoll.h>
int log_fd ;
int getDate(char * _buf)
{
	time_t now;
	struct tm* s_now;
	const char * week[] = {"天", "一", "二", "三", "四", "五", "六" };
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

void writelog(const char * format, ...) //写日志
{
	va_list argv;
	va_start(argv, format);	
	char _buf[BUF_SIZE];
	int offset = getDate(_buf);
	int msglen = vsnprintf(_buf + offset, BUF_SIZE - offset - 1,format, argv);
	_buf[offset + msglen] = '\n';
	_buf[offset + msglen + 1] = 0;
	write(log_fd, _buf, offset + msglen + 1);
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

	inet * network = new net_epoll;
	network->initNetwork();
	network->dowork();
	close(log_fd);
	return 0;
}
