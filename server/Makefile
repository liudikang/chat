TARGET=app
GCC=gcc -I./include
.PHONY: clean
OBJECT=main.o 
%.o:%.cpp
	$(GCC) -c $<

$(TARGET):${OBJECT}
	$(GCC) $^ -o $@ 

clean: 
	-rm ${OBJECT} 
