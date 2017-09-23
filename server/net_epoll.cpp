#include	<net_epoll.h>
#include	<sys_net.h>
#include	<control.h>
using namespace mynet;
int net_epoll::initNetwork()
{
	this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);		
	if (listen_fd < 0)
		perror("socket error");
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons( SERVER_PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(listen_fd, (const struct sockaddr*) &addr, sizeof(addr)) < 0)
		perror("bind error");
	if ( listen(listen_fd, 4) < 0)
		perror("listen error");	
	this->epoll_fd = epoll_create(1);
	addfd(listen_fd);
}

void net_epoll::addfd(int new_fd)  //默认边缘触发 非阻塞
{
	struct epoll_event event;
	event.events = EPOLLIN | EPOLLET;
	event.data.fd = new_fd;
	int mask = fcntl( new_fd, F_GETFL);
	fcntl( new_fd, F_SETFL, mask | O_NONBLOCK);
	epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, new_fd, &event);
}

void net_epoll::dowork()
{
	struct epoll_event event[MAX_EVENT];
	char readbuf[BUF_SIZE];
	printf("test\n");
	for(;;)
	{
		int ret = epoll_wait( this->epoll_fd, event, MAX_EVENT, -1);
		if (ret < 0)
		{
			writelog("%s :%s ", "epoll_wait error", strerror(errno));
			break;
		}else
		{
			for (int i = 0; i < ret; i++)
			{

				int fd = event[i].data.fd;
				if ( fd == listen_fd)
				{
					printf("new connect\n");
					int new_fd = accept(fd, NULL, NULL);
				//	writelog("new connct");
					addfd(new_fd);
				}else if(event[i].events & EPOLLIN)
				{
					//read length	
					bool wrong = false;
					int rlen = 0;//已读长度
					int typelen = sizeof(len_t); // 
					len_t length ;	
					while (rlen < typelen)
					{
						int len = read(fd, readbuf + rlen, typelen - rlen);
						if (len <= 0)
						{
							wrong = true;
							::close(fd); //异常直接关闭连接
							break;
						}else
						{
							rlen += len;
						}
					}
					length = * (len_t *) readbuf;
					if (length > BUF_SIZE)  //数据包过大  
					{
						::close(fd);
						wrong = true;
					}
					while(rlen < length) //读取具体数据
					{
						int len = read(fd, readbuf + rlen, length - rlen);
						if (len < 0)
						{
							if ( errno == EAGAIN)
								break;
							::close(fd); //异常
							wrong = true;
							break;
						}else if (len == 0)
						{
							wrong = true;
							::close(fd); //连接已关闭
							break;
						}else 
						{
							rlen += len;
						}
					}
					//提交数据
					if ( !wrong)
					{
						this->control->dealData( 0 , NULL, 0);
					}
					//readbuf[rlen] = 0;
					//pk_register *reg = reinterpret_cast<pk_register *> (readbuf);
					//printf("%s \n%s \n ", reg->username, reg->password);
					//printf("%s \nlen:%d\n", readbuf, rlen);
				}

			}
		}
	}
}

void net_epoll::close()
{
	::close(listen_fd);
}
