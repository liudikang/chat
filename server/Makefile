TARGET=app
GCC=g++  -g -I./include -pthread  --std=gnu++11
MYSQL=  `mysql_config --cflags --libs`
.PHONY: clean
OBJECT=main.o testwork.o net_epoll.o control.o  model_mysql.o
%.o:%.cpp
	$(GCC) -c $<  ${MYSQL}

$(TARGET):${OBJECT}
	$(GCC) $^ -o $@ ${MYSQL} 

sqlcon: model_mysql.cpp testmysql.cpp
	${GCC} $^ -o $@ ${MYSQL}
clean: 
	-rm ${OBJECT} 
