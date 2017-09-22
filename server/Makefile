TARGET=app
GCC=g++ -I./include -std=c++11
.PHONY: clean
OBJECT=main.o testwork.o net_epoll.o
%.o:%.cpp
	$(GCC) -c $<

$(TARGET):${OBJECT}
	$(GCC) $^ -o $@ 

clean: 
	-rm ${OBJECT} 
