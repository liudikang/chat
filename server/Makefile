TARGET=app
GCC=g++ -I./include -pthread -std=c++11
MYSQL=  `mysql_config --cflags --libs`
.PHONY: clean
OBJECT=main.o testwork.o net_epoll.o control.o 
%.o:%.cpp
	$(GCC) -c $<

$(TARGET):${OBJECT}
	$(GCC) $^ -o $@ 

sqlcon: model_mysql.cpp testmysql.cpp
	${GCC} $^ -o $@ ${MYSQL}
clean: 
	-rm ${OBJECT} 
